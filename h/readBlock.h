#include <string>

#include "../h/base.h"


class BlockRead: public BaseRead {

    public:
        BlockRead(std::string filePath)
            :BaseRead(filePath){}

        virtual void read();

}; //MMapRead class