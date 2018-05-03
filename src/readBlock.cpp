#include <string>
#include <fstream>      // std::ifstream
#include <iostream>     // std::cout

#include "../headers/readBlock.h"

using namespace std;


void BlockRead::read(bool verbose){
    std::ifstream is (this->targetFile.c_str(), std::ifstream::binary);
    if (!is)
        return;

    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    char * buffer = new char [length];
    if(verbose)
        cout << "Reading " << length << " characters using read(). " << endl;
    // read data as a block:
    is.read (buffer,length);

    if (!is)
        cout << "error: only " << is.gcount() << " could be read" << endl;

    is.close();

    // ...buffer contains the entire file...
    delete[] buffer;
}//read