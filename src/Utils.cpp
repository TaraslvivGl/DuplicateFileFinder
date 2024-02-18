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

bool filecmp::runWithTreads(const fs::path &f1, const fs::path &f2, unsigned int threadsNum)
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

fs::path files::generateFile(std::string name, int size, char symbol, bool changeLastChar)
{
    fs::path path {name};
    std::ofstream ofs(path);
    for (int i = 0; i < size; ++i)
    {
        if (changeLastChar && (i == size - 1))
        {
            ofs << char((symbol + i + 10)%256);
        }
        else
        {
            ofs << char((symbol + i)%256);
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
//        cout << dirPath << " does not exist" << endl; // exeption
        return false;
    }

    if (!fs::is_directory(dirPath))
    {
//        cout << dirPath << " is not a directory" << endl; // exeptions
        return false;
    }

    return true;
}
