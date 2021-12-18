#include "tokens.cpp"

#define DEBUG(msg) std::cout << msg << std::endl;

class LexicalAnalyzer {
private:
    std::ifstream file;
    std::string currentLine;
    std::map<char, bool> canBreakChar;
    std::map<std::string, bool> canBreakCharStr;
    Token token;
    int line, row, initial_col;
public: 
    LexicalAnalyzer(std::string filePath) {
        file = std::ifstream(filePath);
        token = Token();
        line = 0, row = 0, initial_col = 0;

        currentLine = "";
        canBreakChar['{'] = true;
        canBreakChar['}'] = true;
        canBreakChar['('] = true;
        canBreakChar[')'] = true;
        canBreakChar['['] = true;
        canBreakChar[']'] = true;
        canBreakChar[','] = true;
        canBreakChar[';'] = true;
        canBreakChar['.'] = true;
        canBreakChar['\"'] = true;
        canBreakChar['\''] = true;

        canBreakChar['+'] = true;
        canBreakChar['-'] = true;
        canBreakChar['*'] = true;
        canBreakChar['/'] = true;
        canBreakChar['>'] = true;
        canBreakChar['<'] = true;
        canBreakChar['='] = true;
        canBreakChar['^'] = true;
        canBreakChar['|'] = true;
        canBreakChar['&'] = true;

        canBreakCharStr["++"] = true;
        canBreakCharStr["--"] = true;
        canBreakCharStr["=="] = true;
        canBreakCharStr["!="] = true;
        canBreakCharStr[">="] = true;
        canBreakCharStr["<="] = true;

    }

    bool hasToken() {
        if (row == currentLine.size()) {
            if (getline(file, currentLine)) {
                row = 0;
                line++;
                initial_col = 1;
                printf("%04d  %s\n", line, currentLine.c_str());
                return hasToken();
            }

            return false;
        }

        while (row < currentLine.size() && (currentLine[row] == '\t' || currentLine[row] == ' ')) {
            row++;
        }

        if (row < currentLine.size()) {
            initial_col = row + 1;
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
        return make_pair(token.getTokenId("_StringConst"), cur_token);
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
        return make_pair(token.getTokenId("_CharConst"), cur_token);
    }

    std::pair<int, std::string> readNumberConst() {
        std::string cur_token = "";
        bool has_dot = false;
        while (row < currentLine.size()) {
            if (currentLine[row] >= '0' && currentLine[row] <= '9') {
                cur_token += currentLine[row];
                row++;
            } else if (currentLine[row] == '.' && !has_dot) {
                has_dot = true;
                cur_token += currentLine[row];
                row++;
            } else if (cur_token.size() == 0 && (currentLine[row] == '+' || currentLine[row] == '-')) {
                cur_token += currentLine[row];
                row++;
            } else {
                break;
            }
        }
        return make_pair(token.getTokenId(has_dot ? "_DoubleConst" : "_IntConst"), cur_token);
    }

    std::pair<int, std::string> nxtToken() {
        std::string cur_token = "";

        while (row < currentLine.size() && currentLine[row] != '\t' && currentLine[row] != ' ') {
            if (cur_token.size() && canBreakChar[currentLine[row]]) {
                break;
            } else if (cur_token.size() && canBreakCharStr[currentLine.substr(row, 2)]) {
                break;
            } else if ((currentLine[row] == '+' || currentLine[row] == '-') &&
                row + 1 < currentLine.size() && currentLine[row + 1] >= '0' && currentLine[row + 1] <= '9') {
                return readNumberConst();
            } else if (cur_token.size() == 0 && currentLine[row] >= '0' && currentLine[row] <= '9') {
                return readNumberConst();
            }

            cur_token += currentLine[row];
            row++;

            if (currentLine[row - 1] == '\'') {
                return readCharConst();
            } else if (currentLine[row - 1] == '\"'){
                return readStringConst();
            } else if (canBreakCharStr[currentLine.substr(row - 1, 2)]) {
                cur_token += currentLine[row];
                row++;
                break;
            } else if (canBreakChar[currentLine[row - 1]]) {
                break;
            }
        }

        return make_pair(token.getTokenId(cur_token), cur_token);
    }

    void printToken(std::pair<int, std::string> cur_token) {
        printf("        [%04d, %04d] (%04d, %20s) {%s}\n", 
            line, initial_col, 
            cur_token.first, token.getToken(cur_token.first).c_str(), 
            cur_token.second.c_str());
    }
};