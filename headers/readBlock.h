#include <string>

#include "../h/base.h"


class BlockRead: public BaseRead {

    public:
        BlockRead(std::string filePath)
            :BaseRead(filePath){}

        virtual ~BlockRead() = default;

        virtual void read(bool verbose=true);

}; //MMapRead class