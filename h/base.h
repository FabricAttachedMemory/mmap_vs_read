#ifndef BASE_H
#define BASE_H

#include <string>

class BaseRead {

    public:
        BaseRead(std::string filePath)
                :targetFile(filePath){}

        virtual void read() { std::cout << "I am a potato!" << std::endl; }
        std::string GetFilePath() const { return targetFile; }

    protected:
        std::string targetFile;

};

#endif
