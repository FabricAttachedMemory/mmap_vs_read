#include <string>

#include "../h/base.h"


class MmapRead: public BaseRead {

    public:
        MmapRead(std::string filePath)
            :BaseRead(filePath){}

        virtual ~MmapRead() = default;

        virtual void read(bool verbose=true);

}; //MMapRead class