#ifndef FileLoader
#define FileLoader
#include "main.h"

class CFileLoader {
public:
    static auto FileContent(const char* filePath) -> ifstream;
};

#endif
