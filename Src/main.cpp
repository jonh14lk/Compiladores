#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

class LexicalAnalyzer {
    private:
    std::ifstream file;
    std::string currentLine;
    std::map<char, bool> canBreak;
    std::map<std::string, bool> incToken;
    int line, row;

    public: 
    LexicalAnalyzer(std::string filePath) {
        file = std::ifstream(filePath);
        line = 0, row = 0;
        currentLine = "";
        canBreak['{'] = true;
        canBreak['}'] = true;
        canBreak['('] = true;
        canBreak[')'] = true;
        canBreak['['] = true;
        canBreak[']'] = true;
        canBreak[';'] = true;
        incToken["++"] = true;
        incToken["--"] = true;
    }

    bool hasToken() {
        if(row == currentLine.size()) {
            if (getline(file, currentLine)) {
                row = 0;
                line++;
                //std::cout << "Line " << line << ": " << currentLine << std::endl;
                std::cout << std::endl;
                return hasToken();
            }
            return false;
        }  

        while(row < currentLine.size() && (currentLine[row] == '\t' || currentLine[row] == ' ')) {
            row++;
        }

        return (row < currentLine.size());
    }

    std::pair<int, std::string> nxtToken() {
        std::string token = "";

        while(row < currentLine.size() && currentLine[row] != '\t' && currentLine[row] != ' ') {
            if (token.size() && canBreak[currentLine[row]]) {
                break;
            }
            else if (token.size() && incToken[currentLine.substr(row, 2)]) {
                break;
            }

            token += currentLine[row];
            row++;

            if (canBreak[currentLine[row - 1]]) {
                break;
            }
        }

        return make_pair(0, token);
    }
};

int main (int argc, char *argv[]) {
    if(argc <= 1) {
        std::cout << "No file provided" << std::endl;
        return 1;
    }

    std::string filePath = std::string(argv[1]);
    LexicalAnalyzer analyzer(filePath);

    while(analyzer.hasToken()) {
        std::pair<int, std::string> t = analyzer.nxtToken();
        std::cout << t.first << " " << t.second << std::endl;
    }
}