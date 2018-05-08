#include <string>
#include "headers/readBlock.h"

using namespace std;

int main(int argc, char * argv[]){
    string file_path = argv[1];

    BlockRead* blockReader = new BlockRead(file_path);
    blockReader->read();

    return 0;
}//run