#include <string>

#include "../h/base.h"


class BlockRead: public BaseRead {

    public:
        BlockRead(std::string filePath)
            :BaseRead(filePath){}

        void read();

}; //MMapRead class