#include "DuplicateFileFinderApp.h"

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        cout << "Missed argument - path to the directory." << endl;
        return 0;
    }


    DuplicateFileFinderApp app(true);

    auto start = high_resolution_clock::now();
    try
    {
        app.run(argv[1]);
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
    }
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Excecution time: " << duration.count() << "ms" << endl;

    return 0;
}
