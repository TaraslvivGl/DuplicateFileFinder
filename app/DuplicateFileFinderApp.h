#pragma once

#include <map>
#include <string>

/**
 * @brief The DuplicateFileFinderApp class ecursively finds all the duplicate files in the directory
 */
class DuplicateFileFinderApp
{
public:
    /**
     * @brief DuplicateFileFinderApp
     * @param showProgress - show the User that the application is busy
     */
    explicit DuplicateFileFinderApp(bool showProgress = true)
        : m_showProgress(showProgress)
    {}
    /**
     * @brief run - start searching for the duplicates
     * @param dirPath - the directory where the search starts from
     */
    void run(const char* dirPath);

private:
    void printResults(const std::map<std::string, std::string>& duplicates);
    void showProgress();

private:
    bool m_showProgress {false};
};
