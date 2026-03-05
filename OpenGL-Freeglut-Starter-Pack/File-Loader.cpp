#include "File-Loader.h"

ifstream CFileLoader::FileContent(const char* filePath) {
    ifstream content;
    content.open(filePath);
    
    if (!content.is_open()) LOG_WARNING("Could not open file.")
    if (!content.good()) LOG_WARNING("File empty.")
    return content;
}
