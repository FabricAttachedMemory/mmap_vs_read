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
        std::string GetName() const { return this->name; }
        void SetName(std::string className) { this->name = className; }

    protected:
        std::string targetFile;
        std::string name;

};

#endif
