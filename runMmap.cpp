#include <string>
#include <iostream>

#include "readMmap.h"

using namespace std;


int main(int argc, char * argv[]){
    // string filePath = argv[1];
    MmapRead reader("SomePath");
    // cout << reader.GetFilePath() << endl;

    // int startTime = clock();
    reader.read();
    // int endTime = clock();

    // cout << "time: " << (endTime - startTime) / double(CLOCKS_PER_SEC) << endl;
    return 0;
}//main