#include "Utils.h"

#include <fstream>
#include <future>
#include <numeric>

bool filecmp::isIdentical(const fs::path &f1, const fs::path &f2, int pos, int n)
{
    const int BufferSize = 1024;
    int readBytes = 0;
    std::string buffer1(BufferSize, '\0');
    std::string buffer2(BufferSize, '\0');

    std::ifstream ifs1(f1, std::ios::binary);
    std::ifstream ifs2(f2, std::ios::binary);

    ifs1.seekg(pos);
    ifs2.seekg(pos);

    while (readBytes < n)
    {
        const int ReadSize = std::min(BufferSize, n - readBytes);
        ifs1.read(buffer1.data(), ReadSize);
        ifs2.read(buffer2.data(), ReadSize);
        if (buffer1 != buffer2)
        {
            return false;
        }
        readBytes += ifs1.gcount();
    }

    return true;
}

bool filecmp::compareBinaryFiles(const fs::path &f1, const fs::path &f2, unsigned int threadsNum)
{
    const int FileSize = fs::file_size(f1);
    if (FileSize != fs::file_size(f2))
    {
        return false;
    }

    if (threadsNum == 0)
    {
        const int preferableThreadNum = std::thread::hardware_concurrency() - 1;
        threadsNum = preferableThreadNum <= 0 ? 1 : preferableThreadNum;
    }

    if (FileSize < threadsNum)
    {
        return isIdentical(f1, f2, 0, FileSize);
    }
    else
    {
        std::vector<std::shared_future<bool>> result(threadsNum);
        const int Chunk = FileSize / threadsNum;
        int seek = 0;
        for (int i = 0; i < threadsNum; ++i)
        {
            const int readSize = i == threadsNum-1 ? FileSize - seek : Chunk;
            result[i] = async(std::launch::async, isIdentical, f1, f2, seek, readSize);
            seek += Chunk;
        }

        for (const auto& el : result)
        {
            if (!el.get())
            {
                return false;
            }
        }
        return true;
    }

}

fs::path files::generateFile(std::string fileName, int fileSize, char initSymbol, bool changeLastChar)
{
    const int AsciiShift = 10;
    const int AsciiSize = 256;
    fs::path path{fileName};
    std::ofstream ofs(path);

    for (int i = 0; i < fileSize; ++i)
    {
        if (changeLastChar && (i == fileSize - 1))
        {
            ofs << char((initSymbol + i + AsciiShift)%AsciiSize);
        }
        else
        {
            ofs << char((initSymbol + i)%AsciiSize);
        }
    }

    return path;
}

void files::findFilesRecursively(const fs::path& dirPath, std::vector<fs::path> &files)
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
