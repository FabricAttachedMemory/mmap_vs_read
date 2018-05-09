#include <map>
#include <list>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <iostream>
#include <string.h>
#include <vector>
#include <iterator>
#include <iomanip>

using namespace std;


vector<string> splitLine(char *line){
    string s(line);
    regex ws_re("\\s+"); // whitespace
    vector<string> result{
        sregex_token_iterator(s.begin(), s.end(), ws_re, -1), {}
    };

    return result;
}


void parseStraceLine(map<string, list<double>> *data, char *line){
    vector<string> splitted = splitLine(line);
    cout << splitted.size() << endl;
}//parseStraceLine


void readLog(string logPath){
    map<string, list<double>> logData; //list of values for each etaration
    ifstream openedFile(logPath);

    if(!openedFile){
        cout << "Failed to open file at" << logPath << endl;
        return;
    }//if not opened

    int lineBufferSize = 255;
    char line[lineBufferSize];

    while(openedFile){
        openedFile.getline(line, lineBufferSize);
        parseStraceLine(&logData, line);
    }//while

    openedFile.close();
}//readLog


int main(int argc, char * argv[]){
    string logPath = argv[1];

    readLog(logPath);
}//main