#pragma once

#include <map>
#include <string>

class DuplicateFileFinderApp
{
public:
    DuplicateFileFinderApp();
    explicit DuplicateFileFinderApp(bool showProgress = false)
        : m_showProgress(showProgress)
    {}
    void run(const char* dirPath);

private:
    void printResults(const std::map<std::string, std::string> &duplicates);
    void showProgress();

private:
    bool m_showProgress {false};
};
