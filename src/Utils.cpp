#include "Utils.h"

#include <fstream>
#include <future>
#include <numeric>

bool filecmp::isIdentical(const fs::path &f1, const fs::path &f2, int pos, int n)
{
    const int bufferSize = 1024;
    int readBytes = 0;
    std::string buffer1(bufferSize, '\0');
    std::string buffer2(bufferSize, '\0');

    std::ifstream ifs1(f1, std::ios::binary);
    std::ifstream ifs2(f2, std::ios::binary);

    ifs1.seekg(pos);
    ifs2.seekg(pos);

    while (readBytes < n)
    {
        const int readSize = std::min(bufferSize, n - readBytes);
        ifs1.read(buffer1.data(), readSize);
        ifs2.read(buffer2.data(), readSize);
        readBytes += ifs1.gcount();
        if (buffer1 != buffer2)
        {
            return false;
        }
    }

    return true;
}

bool filecmp::compareBinaryFiles(const fs::path &f1, const fs::path &f2, unsigned int threadsNum)
{
    const int fileSize = fs::file_size(f1);
    if (fileSize != fs::file_size(f2))
    {
        return false;
    }

    if (threadsNum == 0)
    {
        const int preferableThreadNum = std::thread::hardware_concurrency() - 1;
        threadsNum = preferableThreadNum <= 0 ? 1 : preferableThreadNum;
    }

    if (fileSize < threadsNum)
    {
        return isIdentical(f1, f2, 0, fileSize);
    }
    else
    {
        std::vector<std::shared_future<bool>> result(threadsNum);
        const int Chunk = fileSize / threadsNum;
        int seek = 0;
        for (int i = 0; i < threadsNum; ++i)
        {
            const int readSize = i == threadsNum-1 ? fileSize - seek : Chunk;
            result[i] = async(std::launch::async, isIdentical, f1, f2, seek, readSize);
            seek += Chunk;
        }
        return std::accumulate(result.begin(), result.end(), true,
                               [](bool acc, std::shared_future<bool> el) { return acc && el.get();});
    }

}

fs::path files::generateFile(std::string fileName, int fileSize, char initSymbol, bool changeLastChar)
{
    const int asciiShift = 10;
    const int asciiSize = 256;
    fs::path path{fileName};
    std::ofstream ofs(path);

    for (int i = 0; i < fileSize; ++i)
    {
        if (changeLastChar && (i == fileSize - 1))
        {
            ofs << char((initSymbol + i + asciiShift)%asciiSize);
        }
        else
        {
            ofs << char((initSymbol + i)%asciiSize);
        }
    }

    return path;
}

void files::findFilesRecursively(fs::path dirPath, std::vector<fs::path> &files)
{
    for (const auto& path : fs::recursive_directory_iterator(dirPath))
    {
        if (!fs::is_directory(path))
        {
            files.push_back(path.path());
        }
    }
}

bool files::verifyPathDirectory(const fs::path &dirPath)
{
    if (!fs::exists(dirPath))
    {
        throw std::invalid_argument(std::string(dirPath) + " directory does't exist");
        return false;
    }

    if (!fs::is_directory(dirPath))
    {
        throw std::invalid_argument(std::string(dirPath) + " is not a directory");
        return false;
    }

    return true;
}
