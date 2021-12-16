#include "tokens.cpp"

class LexicalAnalyzer {
private:
    std::ifstream file;
    std::string currentLine;
    std::map<char, bool> canBreak;
    std::map<std::string, bool> canBreak2;
    Token token;
    int line, row;

public: 
    LexicalAnalyzer(std::string filePath) {
        file = std::ifstream(filePath);
        token = Token();
        line = 0, row = 0;
        currentLine = "";
        canBreak['{'] = true;
        canBreak['}'] = true;
        canBreak['('] = true;
        canBreak[')'] = true;
        canBreak['['] = true;
        canBreak[']'] = true;
        canBreak[','] = true;
        canBreak[';'] = true;
        canBreak['\"'] = true;
        canBreak['\''] = true;

        canBreak['+'] = true;
        canBreak['-'] = true;
        canBreak['*'] = true;
        canBreak['/'] = true;
        canBreak['>'] = true;
        canBreak['<'] = true;
        canBreak['='] = true;
        canBreak['^'] = true;
        canBreak['|'] = true;
        canBreak['&'] = true;

        canBreak2["++"] = true;
        canBreak2["--"] = true;
        canBreak2["=="] = true;
        canBreak2["!="] = true;
        canBreak2[">="] = true;
        canBreak2["<="] = true;
    }

    bool hasToken() {
        if (row == currentLine.size()) {
            if (getline(file, currentLine)) {
                // TODO: printar linha!!
                row = 0;
                line++;
                std::cout << std::endl;
                return hasToken();
            }
            return false;
        }

        while (row < currentLine.size() && (currentLine[row] == '\t' || currentLine[row] == ' ')) {
            row++;
        }

        if (row < currentLine.size()) {
            return true;
        }

        return hasToken();
    }

    std::pair<int, std::string> readStringConst() {
        std::string cur_token = "\"";
        while (row < currentLine.size()) {
            cur_token += currentLine[row];
            row++;
            if (currentLine[row - 1] == '\"') {
                break;
            }
        }
        return make_pair(token.getTokenId("StringConst"), cur_token);
    }

    std::pair<int, std::string> readCharConst() {
        std::string cur_token = "\'";
        while (row < currentLine.size()) {
            cur_token += currentLine[row];
            row++;
            if (currentLine[row - 1] == '\'') {
                break;
            }
        }
        return make_pair(token.getTokenId("CharConst"), cur_token);
    }

    std::pair<int, std::string> readNumberConst() {
        std::string cur_token = "";
        bool has_point = false;
        while (row < currentLine.size() && ((currentLine[row] >= '0' && currentLine[row] <= '9') || currentLine[row] == '.')) {
            if (currentLine[row] == '.') {
                has_point = true;
            }
            cur_token += currentLine[row];
            row++;
        }
        return make_pair(token.getTokenId(has_point ? "DoubleConst" : "IntConst"), cur_token);
    }

    std::pair<int, std::string> nxtToken() {
        std::string cur_token = "";

        while (row < currentLine.size() && currentLine[row] != '\t' && currentLine[row] != ' ') {
            if (cur_token.size() && canBreak[currentLine[row]]) {
                break;
            } else if (cur_token.size() && canBreak2[currentLine.substr(row, 2)]) {
                break;
            } else if (!cur_token.size() && currentLine[row] >= '0' && currentLine[row] <= '9') {
                return readNumberConst();
            }

            cur_token += currentLine[row];
            row++;

            if (currentLine[row - 1] == '\'') {
                return readCharConst();
            } else if (currentLine[row - 1] == '\"'){
                return readStringConst();
            } else if (canBreak2[currentLine.substr(row - 1, 2)]) {
                cur_token += currentLine[row];
                row++;
                break;
            } else if (canBreak[currentLine[row - 1]]) {
                break;
            }
        }

        return make_pair(token.getTokenId(cur_token), cur_token);
    }

    void printToken(std::pair<int, std::string> t) {
        std::cout << token.getToken(t.first) << " ";
        std::cout << t.first << " " << t.second << std::endl;
        // std::cout << "(" << t.first << ", " << token.getTokenId(t.first) << ") " << t.second << std::endl;
    }
};