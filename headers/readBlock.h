#ifndef READBLOCK_H
#define READBLOCK_H

#include <string>

#include "base.h"


class BlockRead: public BaseRead {

    public:
        BlockRead(std::string filePath)
            :BaseRead(filePath){ SetName("BlockDataRead"); }

        virtual ~BlockRead() = default;

        virtual void read(bool verbose=true);

}; //MMapRead class

#endif