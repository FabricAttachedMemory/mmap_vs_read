#include <ctime>
#include <stdio.h>
#include <iostream>

#include "../h/readMmap.h"
#include "../h/readBlock.h"

using namespace std;


float bench_the_mark(BaseRead* reader){
    int startTime = clock();
    reader->read();
    int endTime = clock();
    return (endTime - startTime) / double(CLOCKS_PER_SEC);
}//bench_the_mark


int main(int argc, char * argv[]){
    string filePath = argv[1];

    MmapRead* mmapReader = new MmapRead(filePath);
    float runTime = bench_the_mark(mmapReader);
    cout << "MMap() time: " << runTime << endl;
    delete mmapReader;

    BlockRead* blockReader = new BlockRead(filePath);
    runTime = bench_the_mark(blockReader);
    cout << "Read() time: " << runTime << endl;
    delete blockReader;
 
    return 0;
}//main