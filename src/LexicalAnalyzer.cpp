#include <unordered_map>
#include "token.cpp"
#include "tokens_classifier.cpp"

#define DEBUG(msg) std::cout << msg << std::endl;

class LexicalAnalyzer {
private:
    std::ifstream file;
    std::string currentLine;
    std::unordered_map<char, Token> canBreakChar;
    std::unordered_map<std::string, Token> canBreakStr;
    TokenClassifier tokenClassifier;
    int line, column, initial_col;
public: 
    LexicalAnalyzer(std::string filePath) {
        file = std::ifstream(filePath);
        tokenClassifier = TokenClassifier();
        line = 0, column = 0, initial_col = 0;

        currentLine = "";
        canBreakChar['{'] = Token::OpenBrace;
        canBreakChar['}'] = Token::CloseBrace;
        canBreakChar['('] = Token::OpenPar;
        canBreakChar[')'] = Token::ClosePar;
        canBreakChar['['] = Token::OpenBrack;
        canBreakChar[']'] = Token::CloseBrack;
        canBreakChar[','] = Token::SignalComma;
        canBreakChar[';'] = Token::SignalSemiColon;
        canBreakChar['.'] = Token::SignalDot;
        canBreakChar['\"'] = Token::Unknown;
        canBreakChar['\''] = Token::Unknown;

        canBreakChar['+'] = Token::OperationAdd;
        canBreakChar['-'] = Token::OperationSub;
        canBreakChar['*'] = Token::OperationMult;
        canBreakChar['/'] = Token::OperationDiv;
        canBreakChar['>'] = Token::RelationGreater;
        canBreakChar['<'] = Token::RelationLower;
        canBreakChar['='] = Token::AtributionEqual;
        canBreakChar['^'] = Token::OperationXor;
        canBreakChar['|'] = Token::OperationOr;
        canBreakChar['&'] = Token::OperationAnd;

        canBreakStr["++"] = Token::OperationInc;
        canBreakStr["--"] = Token::OperationDec;
        canBreakStr["+="] = Token::OperationConc;
        canBreakStr["=="] = Token::RelationEqual;
        canBreakStr["!="] = Token::RelationNotEqual;
        canBreakStr[">="] = Token::RelationGreaterEqual;
        canBreakStr["<="] = Token::RelationLowerEqual;
    }

    bool hasToken() {
        if (column == currentLine.size()) {
            if (getline(file, currentLine)) {
                column = 0;
                line++;
                initial_col = 1;
                printf("%4d  %s\n", line, currentLine.c_str());
                return hasToken();
            }

            return false;
        }

        while (column < currentLine.size() && (currentLine[column] == '\t' || currentLine[column] == ' ')) {
            column++;
        }

        if (column < currentLine.size()) {
            initial_col = column + 1;
            return true;
        }

        return hasToken();
    }

    std::pair<Token, std::string> readStringConst() {
        std::string cur_token = "\"";
        while (column < currentLine.size()) {
            cur_token += currentLine[column];
            column++;
            if (currentLine[column - 1] == '\"') {
                break;
            }
        }
        return make_pair(Token::StringConst, cur_token);
    }

    std::pair<Token, std::string> readCharConst() {
        std::string cur_token = "\'";
        while (column < currentLine.size()) {
            cur_token += currentLine[column];
            column++;
            if (currentLine[column - 1] == '\'') {
                break;
            }
        }
        return make_pair(Token::CharConst, cur_token);
    }

    std::pair<Token, std::string> readNumberConst() {
        std::string cur_token = "";
        bool has_dot = false;
        while (column < currentLine.size()) {
            if (currentLine[column] >= '0' && currentLine[column] <= '9') {
                cur_token += currentLine[column];
                column++;
            } else if (currentLine[column] == '.' && !has_dot) {
                has_dot = true;
                cur_token += currentLine[column];
                column++;
            } else if (cur_token.size() == 0 && (currentLine[column] == '+' || currentLine[column] == '-')) {
                cur_token += currentLine[column];
                column++;
            } else {
                break;
            }
        }
        return make_pair(has_dot ? Token::DoubleConst : Token::IntConst, cur_token);
    }

    std::pair<Token, std::string> nxtToken() {
        std::string cur_token = "";
        Token cur_token_id = Token::Identificator;
        while (column < currentLine.size() && currentLine[column] != '\t' && currentLine[column] != ' ') {
            if (cur_token.size() && canBreakChar[currentLine[column]]) {
                break;
            } else if (cur_token.size() && canBreakStr[currentLine.substr(column, 2)]) {
                cur_token_id = canBreakStr[currentLine.substr(column, 2)];
                return make_pair(cur_token_id, cur_token);
            } else if ((currentLine[column] == '+' || currentLine[column] == '-') &&
                column + 1 < currentLine.size() && currentLine[column + 1] >= '0' && currentLine[column + 1] <= '9') {
                return readNumberConst();
            } else if (cur_token.size() == 0 && currentLine[column] >= '0' && currentLine[column] <= '9') {
                return readNumberConst();
            }

            cur_token += currentLine[column];
            column++;
            
            if (currentLine[column - 1] == '\'') {
                return readCharConst();
            } else if (currentLine[column - 1] == '\"'){
                return readStringConst();
            } else if (canBreakStr[currentLine.substr(column - 1, 2)]) {
                cur_token += currentLine[column];
                column++;
                break;
            } else if (canBreakChar[currentLine[column - 1]]) {
                break;
            }
        }
        Token result_token = Token::Unknown;
        if(cur_token.length() == 1 && canBreakChar[cur_token[0]]) {
            result_token = canBreakChar[cur_token[0]];
        } else if(canBreakStr[cur_token]){
            result_token = canBreakStr[cur_token];
        }
        return make_pair(result_token != Token::Unknown ? result_token : tokenClassifier.classify(cur_token), cur_token);
    }

    void printToken(std::pair<Token, std::string> cur_token) {
        printf("              [%04d, %04d] (%04d, %20s) {%s}\n", 
            line, initial_col, 
            cur_token.first, tokenClassifier.getToken(cur_token.first).c_str(), 
            cur_token.second.c_str());
    }
};