//
//  Utils.hpp
//  ComputerGraphics
//
//  Created by David M Reed on 11/10/19.
//  Copyright © 2019 David M Reed. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <string>

/// try to find file at filePath
/// @param filePath string containg the filename
/// @param environmentVariable environment variable name to search in if filePath does not exist as is
/// @return if filePath exists, return as is; if filePath does not exists, but exists in directory specified by environmentVariable parameter, full path environmentVariable/filePath is returned; if not found in either location, empty string is returned
std::string pathUsingEnvironmentVariable(std::string filePath, std::string environmentVariable);

/// returns contents of file at filePath
/// @param filePath path to the file
/// @return contents of the file at filePath or empty string if file does not exist
std::string contentsOfFile(std::string filePath);

/// returns new string with leading and trailing characters specifed by whitespace parameter removed
/// @param str characters to be removed from beginning and end of str
/// @return new string with leading and trailing characters specifed by whitespace parameter removed
std::string trim(const std::string& str, const std::string& whitespace = " \t");

#endif /* Utils_hpp */
