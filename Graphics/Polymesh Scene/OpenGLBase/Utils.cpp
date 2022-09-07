//
//  Utils.cpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef __AAPLE__
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <iostream>

#include "Utils.hpp"

using std::cerr;
using std::cout;
using std::endl;
using std::string;

//----------------------------------------------------------------------

std::string pathUsingEnvironmentVariable(std::string filePath, std::string environmentVariable)
{
    FILE *fp;
#ifdef __APPLE__
    fp = fopen(filePath.c_str(), "r");
#else // Windows
    fopen_s(&fp, filePath.c_str(), "r");
#endif

    // try to open as is
    std::string fullPath = filePath;

    // if file not found
    if (fp == NULL) {
        // if file not found, try to get from environmentVariable environment variable
        char *envVarValue;
#ifdef __APPLE__
        envVarValue = getenv(environmentVariable.c_str());
#else // Windows
        size_t numElements;
        _dupenv_s(&envVarValue, &numElements, environmentVariable.c_str());
#endif

        // if environmentVariable environment variable found
        if (envVarValue != NULL) {

            // make a C++ string from the environment variable
            string envVar(envVarValue);

            size_t lastSlash;
#ifdef __APPLE__
            // look for last slash
            lastSlash = filePath.rfind('/');
#else // Windows
            // look for backslash
            lastSlash = filePath.rfind('\\');
#endif

            // if found a slash or backslash
            if (lastSlash != string::npos) {
                // grab last path component after the directory separator
                filePath = filePath.substr(lastSlash + 1);
            }

            // make full path using environment variable and shaderFile
#ifdef __APPLE__
            fullPath = envVar + "/" + filePath;
            fp = fopen(fullPath.c_str(), "r");
#else
            fullPath = envVar + "\\" + filePath;
            fopen_s(&fp, fullPath.c_str(), "r");
#endif
        }

        // if still NULL, print error message
        if (fp == NULL) {
            cerr << "error opening: " << filePath << endl;
        }
    }

    // if found, close the file we opened
    if (fp != NULL) {
        fclose(fp);
    }
    // otherwise set to empty string indicating not found
    else {
        fullPath = "";
    }

    return fullPath;
}

//----------------------------------------------------------------------

std::string contentsOfFile(std::string filePath)
{
    FILE *fp = NULL;
#ifdef __APPLE__
    fp = fopen(filePath.c_str(), "r");
#else
    fopen_s(&fp, filePath.c_str(), "r");
#endif

    if (fp != NULL) {
        // determine number of bytes in file
        fseek(fp, 0L, SEEK_END);
        long size = ftell(fp);

        // move back to beginning of file
        fseek(fp, 0L, SEEK_SET);

        // allocate buffer to hold file contents plus a \0
        char* buf = new char[size + 1];

        // work around issue where Windows cannot properly determine size of file in
        // By putting 0 in it we will get a \0 in all spots after the locations fread fills in.
        // it appears to be an issue with DOS vs. Unix end of line characters
        memset(buf, 0, size+1);

        size_t bytesRead = fread(buf, 1, size, fp);
        buf[bytesRead] = '\0';
        fclose(fp);

        string fileContents(buf);
        delete [] buf;

        return fileContents;
    // return allocated buffer
    }
    return string("");
}

//----------------------------------------------------------------------
// from: http://stackoverflow.com/questions/1798112/removing-leading-and-trailing-spaces-from-a-string

std::string trim(const std::string& str, const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

//----------------------------------------------------------------------
