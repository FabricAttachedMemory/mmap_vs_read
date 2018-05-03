#include <string>

#include "base.h"


class MmapRead: public BaseRead {

    public:
        MmapRead(std::string filePath)
            :BaseRead(filePath){ this->SetName("MmapDataRead"); }

        virtual ~MmapRead() = default;

        virtual void read(bool verbose=true);

}; //MMapRead class