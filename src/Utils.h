#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace filecmp
{
    bool isIdentical(const fs::path& f1, const fs::path& f2, int pos, int n);
    bool runWithTreads(const fs::path& f1, const fs::path& f2, unsigned int threadsNum = 0);
}

namespace files
{
    fs::path generateFile(std::string name, int size, char symbol, bool changeLastChar = false);
    void findFilesRecursively(fs::path dirPath, std::vector<fs::path> &files);
    bool verifyPathDirectory(const fs::path &dirPath);

}
