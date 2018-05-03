#ifndef BASE_H
#define BASE_H

#include <string>

class BaseRead {

    public:
        BaseRead(std::string filePath)
                :targetFile(filePath){}

        virtual ~BaseRead() { }

        virtual void read(bool verbose=true) = 0;
        std::string GetFilePath() const { return targetFile; }

    protected:
        std::string targetFile;

};

#endif
