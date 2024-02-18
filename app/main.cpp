#include "DuplicateFileFinderApp.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        cout << "Missed argument - path to the directory." << endl;
        return 0;
    }


     DuplicateFileFinderApp app(true);

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
    try
    {
        app.run(argv[1]);
//        app.run("secdir");
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
