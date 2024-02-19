#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace filecmp
{
    /**
     * @brief isIdentical - performs binary comparison between two parts of two different files.
     * @param f1 - first file to be compared
     * @param f2 - second file to be compared
     * @param pos - starting position of the files
     * @param n - number of bytes to be compared
     * @return - true if equal
     */
    bool isIdentical(const fs::path& f1, const fs::path& f2, int pos, int n);

    /**
     * @brief compareBinaryFiles - performs binary comparison of two files.
     * @param f1 - first file to be compared
     * @param f2 - second file to be compared
     * @param threadsNum - number of threads to be used for comparison. If 0 is passed
     * then the max number of threads is used
     * @return - true if two files are equal
     */
    bool compareBinaryFiles(const fs::path& f1, const fs::path& f2, unsigned int threadsNum = 0);
}

namespace files
{
    /**
     * @brief generateFile - helper function to generate file with a set of parameters
     * @param fileName - file name
     * @param fileSize - file size
     * @param initSymbol - initial character. The next characters are shifted to 10
     * @param changeLastChar - change the last character
     * @return - absolute path to the generated file
     */
    fs::path generateFile(std::string fileName, int fileSize, char initSymbol, bool changeLastChar = false);

    /**
     * @brief findFilesRecursively - finds all files recursively in particular directory
     * @param dirPath - starting point for recursive search
     * @param [out]files - found files
     */
    void findFilesRecursively(const fs::path& dirPath, std::vector<fs::path> &files);

    /**
     * @brief verifyPathDirectory - verify passed path to the directory
     * @param dirPath - path to the directory
     * @return - true if path to the directory is valid
     * @throws invalid_argument if passed path is not a directory of doesn't exist
     */
    bool verifyPathDirectory(const fs::path &dirPath);
}
