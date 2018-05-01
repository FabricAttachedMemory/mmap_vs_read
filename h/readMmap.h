#include <string>

#include "../h/base.h"


class MmapRead: public BaseRead {

    public:
        MmapRead(std::string filePath)
            :BaseRead(filePath){}

        void read();

}; //MMapRead class