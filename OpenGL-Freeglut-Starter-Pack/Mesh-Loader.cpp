#include "Mesh-Loader.h"

#include "KeyValue.h"

static void CustomLoadVertices(ifstream& content, Mesh& mesh) {
    content >> mesh.vertexCount;
    
    if (mesh.vertexCount > 0) { // check
        mesh.vertices = new Vertex[mesh.vertexCount]; // reserve space
        
        for (int i = 0; i < mesh.vertexCount; i++) {
            content >> mesh.vertices[i].x;
            content >> mesh.vertices[i].y;
            content >> mesh.vertices[i].z;
        }
        
    }
}

static void CustomLoadTexture(ifstream& content, Mesh& mesh) {
    content >> mesh.texCoordCount;
    
    mesh.texCoords = new TextureCoordinates[mesh.texCoordCount];
    for (int i = 0; i < mesh.texCoordCount; i++) {
        content >> mesh.texCoords[i].u;
        content >> mesh.texCoords[i].v;
    }
}

static void CustomLoadNormals(ifstream& content, Mesh& mesh) {
    content >> mesh.normalCount;
    
    mesh.normals = new Vec3[mesh.normalCount];
    for (int i = 0; i < mesh.normalCount; i++) {
        content >> mesh.normals[i].x;
        content >> mesh.normals[i].y;
        content >> mesh.normals[i].z;
    }
}

static void TriangulateFace(const CArray<GLushort>& faceIndices, CArray<GLushort>& outIndices) {
    if (faceIndices.Size() < 3) return;
    
    for (int i = 1; i < faceIndices.Size() - 1; ++i) {
        outIndices.Append(faceIndices[0]);
        outIndices.Append(faceIndices[i]);
        outIndices.Append(faceIndices[i + 1]);
    }
}


static void LoadIndices(ifstream& content, Mesh& mesh) {
    int faceCount;
    content >> faceCount;
    
    CArray<GLushort> triangulatedIndices;
    
    for (int i = 0; i < faceCount; i++) {
        int verticesInFace;
        content >> verticesInFace; 
        
        CArray<GLushort> faceIndices;
        for (int j = 0; j < verticesInFace; j++) {
            GLushort index;
            content >> index;
            faceIndices.Append(index);
        }
        
        TriangulateFace(faceIndices, triangulatedIndices);
    }
    
    mesh.indexCount = triangulatedIndices.Size();
    mesh.indices = new GLushort[mesh.indexCount];
    for (int i = 0; i < mesh.indexCount; i++) {
        mesh.indices[i] = triangulatedIndices[i];
    }
}

Mesh* CMeshLoader::LoadMesh(const string& filename) {
    Mesh* mesh = new Mesh();
    
    ifstream content = std::move(CFileLoader::FileContent(filename.c_str()));
    
    CustomLoadVertices(content, *mesh);
    CustomLoadTexture(content, *mesh);
    CustomLoadNormals(content, *mesh);
    LoadIndices(content, *mesh);
    
    if (mesh->indexCount == 0 || mesh->vertexCount == 0 || mesh->texCoordCount == 0 || mesh->normalCount == 0) {
        LOG_WARNING("File is empty.")
        return nullptr;
    }
    
    LOG_DEBUG("Mesh loaded successfully.")
    
    content.close();
    
    return mesh;
}

struct FaceVertex {
    int vertex_index = -1;
    int st_coord_index = -1;
    int normal_index = -1;

    bool operator<(const FaceVertex& other) const {
        if (vertex_index != other.vertex_index) return vertex_index < other.vertex_index;
        if (st_coord_index != other.st_coord_index) return st_coord_index < other.st_coord_index;
        return normal_index < other.normal_index;
    }

    bool operator==(const FaceVertex& other) const {
        return vertex_index == other.vertex_index &&
               st_coord_index == other.st_coord_index &&
               normal_index == other.normal_index;
    }
};

struct FaceGroup {
    CArray<FaceVertex> face_vertices;
    string name;
};

static void ParseFaceVertex(const string& tuple, FaceVertex& fv) {
    stringstream ss(tuple);
    string part;

    if (getline(ss, part, '/')) {
        if (!part.empty()) fv.vertex_index = stoi(part) - 1;
    }
    if (getline(ss, part, '/')) {
        if (!part.empty()) fv.st_coord_index = stoi(part) - 1;
    }
    if (getline(ss, part, '/')) {
        if (!part.empty()) fv.normal_index = stoi(part) - 1;
    }
}

Mesh* CMeshLoader::LoadMeshFromObj(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        LOG_ERROR("Could not open file: " + filename)
        return nullptr;
    }

    CArray<Vertex> temp_vertices;
    CArray<TextureCoordinates> temp_texCoords;
    CArray<Vec3> temp_normals;
    
    // Using deque for stable references as suggested in the provided logic
    deque<FaceGroup> face_groups;
    face_groups.emplace_back();
    FaceGroup* cur_face_group = &face_groups.back();

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string type;
        if (!(ss >> type)) continue;

        if (type == "v") {
            Vertex v;
            ss >> v.x >> v.y >> v.z;
            temp_vertices.Append(v);
            if (cur_face_group->face_vertices.Size() != 0) {
                face_groups.emplace_back();
                cur_face_group = &face_groups.back();
            }
        } else if (type == "vt") {
            TextureCoordinates vt;
            ss >> vt.u >> vt.v;
            temp_texCoords.Append(vt);
        } else if (type == "vn") {
            Vec3 vn;
            ss >> vn.x >> vn.y >> vn.z;
            temp_normals.Append(vn);
        } else if (type == "f") {
            string tuple;
            CArray<FaceVertex> face;
            while (ss >> tuple) {
                FaceVertex fv;
                ParseFaceVertex(tuple, fv);
                face.Append(fv);
            }
            // Triangulate
            for (int i = 1; i < face.Size() - 1; ++i) {
                cur_face_group->face_vertices.Append(face[0]);
                cur_face_group->face_vertices.Append(face[i]);
                cur_face_group->face_vertices.Append(face[i + 1]);
            }
        } else if (type == "g") {
            if (cur_face_group->face_vertices.Size() != 0) {
                face_groups.emplace_back();
                cur_face_group = &face_groups.back();
            }
            ss >> cur_face_group->name;
        }
    }

    Mesh* mesh = new Mesh();
    CArray<Vertex> out_vertices;
    CArray<TextureCoordinates> out_texCoords;
    CArray<Vec3> out_normals;
    CArray<GLushort> out_indices;
    map<FaceVertex, GLushort> uniqueVertices;

    for (const auto& group : face_groups) {
        for (int i = 0; i < group.face_vertices.Size(); ++i) {
            const FaceVertex& fv = group.face_vertices[i];
            
            if (uniqueVertices.find(fv) == uniqueVertices.end()) {
                uniqueVertices[fv] = (GLushort)out_vertices.Size();
                
                out_vertices.Append(temp_vertices[fv.vertex_index]);
                
                if (fv.st_coord_index != -1 && fv.st_coord_index < temp_texCoords.Size())
                    out_texCoords.Append(temp_texCoords[fv.st_coord_index]);
                else
                    out_texCoords.Append({0, 0});

                if (fv.normal_index != -1 && fv.normal_index < temp_normals.Size())
                    out_normals.Append(temp_normals[fv.normal_index]);
                else
                    out_normals.Append({0, 0, 0});
            }
            out_indices.Append(uniqueVertices[fv]);
        }
    }

    mesh->vertexCount = out_vertices.Size();
    mesh->vertices = out_vertices.Data();
    mesh->texCoordCount = out_texCoords.Size();
    mesh->texCoords = out_texCoords.Data();
    mesh->normalCount = out_normals.Size();
    mesh->normals = out_normals.Data();
    mesh->indexCount = out_indices.Size();
    mesh->indices = out_indices.Data();

    file.close();
    LOG_DEBUG("Mesh loaded successfully from OBJ with groups: " + filename)
    return mesh;
}
