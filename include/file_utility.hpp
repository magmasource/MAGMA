#ifndef FILE_UTILITY_HPP
#define FILE_UTILITY_HPP

#include <vector>
#include <string>

class FileUtility {
    public:
    FileUtility() = default;
    std::vector<std::string> GetFilesWithName(std::string name);
    bool FileExists(std::string name);
};

#endif //FILE_UTILITY_HPP