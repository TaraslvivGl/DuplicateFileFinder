#include "DuplicateFileFinderApp.h"
#include "Utils.h"

#include <vector>
#include <thread>
#include <iostream>

void DuplicateFileFinderApp::run(const char* dirPath)
{
    // @todo: add try catch or add it to the main
    files::verifyPathDirectory(dirPath);

    std::vector<fs::path> files;
    files::findFilesRecursively(dirPath, files);

    const int FilesNumber = files.size();
    std::map<std::string, std::string> duplicates;
    std::vector<bool> markedFiles(FilesNumber, false); // already compared files

    if (m_showProgress)
    {
        showProgress();
    }

    for (int i = 0; i < FilesNumber; ++i)
    {
        if (markedFiles[i])
        {
            // skip already compared file
            continue;
        }
        for (int k = i+1; k < FilesNumber; ++k)
        {
            // skip already compared file
            if (markedFiles[k])
            {
                continue;
            }

            if (filecmp::runWithTreads(files[i], files[k]))
            {
                markedFiles[k] = true;
                duplicates[files[i]] += files[k];
                duplicates[files[i]].append("; ");
            }
        }
    }

    printResults(duplicates);
}

void DuplicateFileFinderApp::printResults(const std::map<std::string, std::string> &duplicates)
{
    m_showProgress = false;
    std::cout << '\r';

    if (duplicates.empty())
    {
        std::cout << "There is no duplicates" << std::endl;
        return;
    }

    for (const auto& [key, value] : duplicates)
    {
        std::cout << key << "; " << value << std::endl;
    }
}

void DuplicateFileFinderApp::showProgress()
{
    const std::array<std::string, 4> progressStr = {"Searching", "Searching.", "Searching..", "Searching..."};
    auto printProgress = [this, progressStr] () {
        int i = 0;
        while (m_showProgress)
        {
            std::cout << progressStr[i++%progressStr.size()] << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << "\r";
        }
    };

    std::thread printer(printProgress);
    printer.detach();
}
