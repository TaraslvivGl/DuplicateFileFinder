#include "DuplicateFileFinderApp.h"

#include <iostream>


using namespace std;
//namespace fs = filesystem;
//using namespace std::chrono_literals;

//class DubplicatesFileFinderApp
//{
//public:
//    explicit DubplicatesFileFinderApp(bool showProgress = false) : m_showProgress(showProgress)
//    {}

//    void run(const fs::path &dirPath)
//    {
//        // @todo: add try catch or add it to the main
//        verifyPathDirectory(dirPath);

//        vector<fs::path> files;
//        findFilesRecursively(dirPath, files);

//        const int FilesNumber = files.size();
//        map<string, string> duplicates;
//        vector<bool> markedFiles(FilesNumber, false); // already compared files

//        if (m_showProgress)
//        {
//            showProgress();
//        }
//        for (int i = 0; i < FilesNumber; ++i)
//        {
//            if (markedFiles[i])
//            {
//                // skip already compared file
//                continue;
//            }
//            for (int k = i+1; k < FilesNumber; ++k)
//            {
//                // skip already compared file
//                if (markedFiles[k])
//                {
//                    continue;
//                }

//                if (runWithTreads(files[i], files[k]))
//                {
//                    markedFiles[k] = true;
//                    duplicates[files[i]] += files[k];
//                    duplicates[files[i]].append("; ");

//                }
//            }
//        }

//        printResults(duplicates);
//    }

//private:
//    bool verifyPathDirectory(const fs::path &dirPath)
//    {
//        if (!fs::exists(dirPath))
//        {
//            cout << dirPath << " does not exist" << endl;
//            return false;
//        }

//        if (!fs::is_directory(dirPath))
//        {
//            cout << dirPath << " is not a directory" << endl;
//            return false;
//        }

//        return true;
//    }


//    void printResults(const map<string, string> &duplicates)
//    {
//        m_showProgress = false;
//        cout << '\r';

//        if (duplicates.empty())
//        {
//            cout << "There is no duplicates." << endl;
//            return;
//        }

//        for (const auto& [key, value] : duplicates)
//        {
//            cout << key << "; " << value << endl;
//        }
//    }

//    void showProgress()
//    {
//        const array<string, 4> progressStr = {"Searching", "Searching.", "Searching..", "Searching..."};
//        auto printProgress = [this, progressStr] () {
//        int i = 0;
//            while (m_showProgress)
//            {
//                cout << progressStr[i++%progressStr.size()] << flush;
//                this_thread::sleep_for(chrono::milliseconds(500));
//                cout << "\r";
//            }
//        };

//        thread printer(printProgress);
//        printer.detach();
//    }

//private:
//    atomic<bool> m_showProgress {false};

//};



int main(int argc, char* argv[])
{

    if (argc == 1)
    {
        cout << "Missed argument - path to the directory." << endl;
        return 0;
    }

     DuplicateFileFinderApp app(true);
//     app.run(argv[1]);



    // generate
//    const int FileSize = 10'000'000;
//    generateFile("file1", FileSize, 'a');
//    generateFile("file2", FileSize, 'a');
//    generateFile("file3", FileSize, 'a');
//    generateFile("file4", FileSize, 'b', true);
//    generateFile("file5", FileSize, 'b');
//    generateFile("file6", FileSize, 'a', true);
//    generateFile("file7", FileSize, 'c');
//    generateFile("file8", FileSize, 'c');
//    generateFile("file9", FileSize, 'd');
//    generateFile("file10", FileSize, 'd');

//     DubplicatesFileFinderApp app(true);
     app.run(".");


//    if (!verifyPathDirectory(argv[1]))
//    {
//        return 0;
//    }

//    vector<fs::path> filePaths;
//    findFilesRecursively(argv[1], filePaths);

//    map<string, string> result;
//    vector<bool> marked(filePaths.size(), false);

//    for (int i = 0; i < filePaths.size(); ++i)
//    {
//        if (marked[i])
//        {
//            continue;
//        }
//        for (int k = i+1; k < filePaths.size(); ++k)
//        {
//            if (marked[k])
//            {
//                continue;
//            }

//            if (runWithTreads(filePaths[i], filePaths[k]))
//            {
//                marked[k] = true;
//                result[filePaths[i]] += filePaths[k];
//                result[filePaths[i]].append("; ");

//            }
//        }
//    }

//    for (const auto& [key, value] : result)
//    {
//        cout << key << "; " << value << endl;
//    }


//    using std::chrono::high_resolution_clock;
//    using std::chrono::duration_cast;
//    using std::chrono::duration;
//    using std::chrono::milliseconds;


//    const int FileSize = 10'000'000;
//    vector<fs::path> paths1 = {
//    generateFile("file1", FileSize, 'a'),
//    generateFile("file2", FileSize, 'a'),
//    generateFile("file3", FileSize, 'a'),
//    generateFile("file4", FileSize, 'b', true),
//    generateFile("file5", FileSize, 'b'),
//    generateFile("file6", FileSize, 'a', true),
//    generateFile("file7", FileSize, 'c'),
//    generateFile("file8", FileSize, 'c'),
//    generateFile("file9", FileSize, 'd'),
//    generateFile("file10", FileSize, 'd')
//    };


//    fs::path f1("file1");
//    fs::path f2("file2");

//    bool idetical {false};
//    cout << "File size = " << fs::file_size(f1) << endl;


//    auto t1 = high_resolution_clock::now();
//    idetical = runWithTreads(f1, f2, ThreadNum);
//    this_thread::sleep_for(chrono::milliseconds(1000));




//    auto t2 = high_resolution_clock::now();
    /* Getting number of milliseconds as an integer. */
//    auto ms_int = duration_cast<milliseconds>(t2 - t1);
//    std::cout << ms_int.count() << "ms\n";

//    cout << "identical = " << idetical << " ThreadNum = " << ThreadNum <<  endl;



    return 0;
}
