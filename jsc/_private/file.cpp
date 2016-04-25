//
//  file.cpp
//  jsc
//
//  Created by Scott Bennett on 2016-04-24.
//  Copyright © 2016 Scott Bennett. All rights reserved.
//

#include "file.hpp"

void readFile(const char *filename, std::function<void (const char *contents)> callback) {
    char *contents = nullptr;
    
    FILE *file = fopen(filename, "r");
    if (file != nullptr) {
        fseek(file, 0, SEEK_END);
        size_t length = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        contents = new char[length + 1];
        fread(contents, 1, length, file);
        contents[length] = '\0';
        fclose(file);
    }
    
    callback(contents);
    
    delete [] contents;
}