#include <string>
#include "headers/readMmap.h"

using namespace std;

int main(int argc, char * argv[]){
    string file_path = argv[1];

    MmapRead* mmapReader = new MmapRead(file_path);
    mmapReader->read();

    return 0;
}//run