#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

#include "SyntacticAnalyzer.cpp"


int main (int argc, char *argv[]) {
    if(argc <= 1) {
        std::cout << "No file provided" << std::endl;
        return 1;
    }
    
    std::string filePath = std::string(argv[1]);
    SyntacticAnalyzer analyzer(filePath);
    
    /*while(analyzer.hasToken()) {
        std::pair<Token, std::string> t = analyzer.nxtToken();
        analyzer.printToken(t);
    }*/
}