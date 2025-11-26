#include "file_utility.hpp"

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#endif
#if defined(__linux__) || defined(__APPLE__)
#define GetCurrentDir getcwd
#endif
#ifdef __APPLE__
#include <cstring>
#endif

#include <cstring>


std::vector<std::string> FileUtility::GetFilesWithName(std::string name) {
    DIR *p_dir = opendir(".");
    struct dirent *dp;
    std::vector<std::string> result;
    while ((dp = readdir(p_dir)) != NULL) {
        std::string res(dp->d_name);
        if (res.find(name) != std::string::npos) {
            result.push_back(res);
        }
    }
    closedir(p_dir);
    return result;
}

bool FileUtility::FileExists(std::string name) {
    struct stat s;
    return (stat(name.c_str(), &s) == 0);
}

bool CreateDirectory(std::string dirname) {
    if (dirname.empty()) return false;
    std::string dir_path = "/";
    struct stat st;
    if (dirname.at(0) != '/')
        dir_path = dir_path+dirname;
    else
        dir_path = dirname;

#ifdef _WIN32
    char buffer[FILENAME_MAX];
    GetCurrentDir(buffer, FILENAME_MAX);
    strcat(buffer, dir_path.c_str());
    if (stat(buffer, &st) == -1) {
        _mkdir(buffer);
    } else return false;
#endif
#if defined(__linux__) || defined(__APPLE__)
    char buffer[FILENAME_MAX];
    GetCurrentDir(buffer, FILENAME_MAX);
    strcat(buffer, dir_path.c_str());
    if (stat(buffer, &st) == -1) {
        mkdir(buffer, 0777);
    } else return false;
#endif

    return true; //directory created
}
