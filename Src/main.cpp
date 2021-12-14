#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

// id do token -> identificador do token
std::map<std::string, int> tokenId;
// token -> id do token
std::map<int, std::string> token;

void buildMap()
{
    tokenId["Identificator"] = 0;
    tokenId["function"] = 1;
    tokenId["main"] = 2;
    tokenId["void"] = 3;
    tokenId["itg"] = 4;
    tokenId["dbl"] = 5;
    tokenId["chr"] = 6;
    tokenId["bool"] = 7;
    tokenId["str"] = 8;
    tokenId["list"] = 9;
    tokenId["{"] = 10;
    tokenId["}"] = 11;
    tokenId["["] = 12;
    tokenId["]"] = 13;
    tokenId["("] = 14;
    tokenId[")"] = 15;
    tokenId["\\n"] = 16;
    tokenId["if"] = 17;
    tokenId["elseif"] = 18;
    tokenId["else"] = 19;
    tokenId["for"] = 20;
    tokenId["while"] = 21;
    tokenId["write"] = 22;
    tokenId["read"] = 23;
    tokenId[";"] = 24;
    tokenId[","] = 25;
    tokenId["+"] = 26;
    tokenId["-"] = 27;
    tokenId["*"] = 28;
    tokenId["/"] = 29;
    tokenId["++"] = 30;
    tokenId["--"] = 31;
    tokenId["+="] = 32;
    tokenId["!"] = 33;
    tokenId["^"] = 34;
    tokenId["|"] = 35;
    tokenId["&"] = 36;
    tokenId["and"] = 37;
    tokenId["or"] = 38;
    tokenId["not"] = 39;
    tokenId["="] = 40;
    tokenId["=="] = 41;
    tokenId["!="] = 42;
    tokenId[">"] = 43;
    tokenId["<"] = 44;
    tokenId[">="] = 45;
    tokenId["<="] = 46;
    tokenId["false"] = 47;
    tokenId["true"] = 48;
    tokenId["return"] = 49;
    tokenId["CharConst"] = 50;
    tokenId["StringConst"] = 51;
    tokenId["DoubleConst"] = 52;
    tokenId["IntConst"] = 53;
    tokenId["true"] = 54;
    tokenId["false"] = 54;

    token[0] = "Identificator";
    token[1] = "DefFunction";
    token[2] = "ReservedMain";
    token[3] = "TypeVoid";
    token[4] = "TypeInteger";
    token[5] = "TypeDouble";
    token[6] = "TypeChar";
    token[7] = "TypeBoolean";
    token[8] = "TypeString";
    token[9] = "TypeList";
    token[10] = "OpenBrace";
    token[11] = "CloseBrace";
    token[12] = "OpenBrack";
    token[13] = "CloseBrack";
    token[14] = "OpenPar";
    token[15] = "ClosePar";
    token[16] = "EndLine";
    token[17] = "ReservedIf";
    token[18] = "ReservedElseIf";
    token[19] = "ReservedElse";
    token[20] = "ReservedFor";
    token[21] = "ReservedWhile";
    token[22] = "ReservedWrite";
    token[23] = "ReservedRead";
    token[24] = "SignalSemiColon";
    token[25] = "SignalComma";
    token[26] = "OperationAdd";
    token[27] = "OperationSub";
    token[28] = "OperationMult";
    token[29] = "OperationDiv";
    token[30] = "OperationInc";
    token[31] = "OperationDec";
    token[32] = "OperationConc";
    token[33] = "OperationNot";
    token[34] = "OperationXor";
    token[35] = "OperationOr";
    token[36] = "OperationAnd";
    token[37] = "LogicAnd";
    token[38] = "LogicOr";
    token[39] = "LogicNot";
    token[40] = "AtributionEqual";
    token[41] = "RelationEqual";
    token[42] = "RelationNotEqual";
    token[43] = "RelationGreater";
    token[44] = "RelationLower";
    token[45] = "RelationGreaterEqual";
    token[46] = "RelationLowerEqual";
    token[47] = "BooleanFalse";
    token[48] = "BooleanTrue";
    token[49] = "ReservedReturn";
    token[50] = "CharConst";
    token[51] = "StringConst";
    token[52] = "DoubleConst";
    token[53] = "IntConst";
    token[54] = "BooleanConst";
    token[55] = "BooleanConst";
}

class LexicalAnalyzer
{
private:
    std::ifstream file;
    std::string currentLine;
    std::map<char, bool> canBreak;
    std::map<std::string, bool> canBreak2;
    int line, row;

public:
    LexicalAnalyzer(std::string filePath)
    {
        file = std::ifstream(filePath);
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

    bool hasToken()
    {
        if (row == currentLine.size())
        {
            if (getline(file, currentLine))
            {
                // TODO: printar linha!!
                row = 0;
                line++;
                std::cout << std::endl;
                return hasToken();
            }
            return false;
        }

        while (row < currentLine.size() && (currentLine[row] == '\t' || currentLine[row] == ' '))
        {
            row++;
        }

        if (row < currentLine.size())
        {
            return true;
        }

        return hasToken();
    }

    std::pair<int, std::string> readStringConst()
    {
        std::string token = "\"";
        while (row < currentLine.size())
        {
            token += currentLine[row];
            row++;
            if (currentLine[row - 1] == '\"')
            {
                break;
            }
        }
        return make_pair(tokenId["StringConst"], token);
    }

    std::pair<int, std::string> readCharConst()
    {
        std::string token = "\'";
        while (row < currentLine.size())
        {
            token += currentLine[row];
            row++;
            if (currentLine[row - 1] == '\'')
            {
                break;
            }
        }
        return make_pair(tokenId["CharConst"], token);
    }

    std::pair<int, std::string> readNumberConst()
    {
        std::string token = "";
        bool has_point = false;
        while (row < currentLine.size() && ((currentLine[row] >= '0' && currentLine[row] <= '9') || currentLine[row] == '.'))
        {
            if (currentLine[row] == '.')
            {
                has_point = true;
            }
            token += currentLine[row];
            row++;
        }
        int id = (has_point) ? tokenId["DoubleConst"] : tokenId["IntConst"];
        return make_pair(id, token);
    }

    std::pair<int, std::string> nxtToken()
    {
        std::string token = "";

        while (row < currentLine.size() && currentLine[row] != '\t' && currentLine[row] != ' ')
        {
            if (token.size() && canBreak[currentLine[row]])
            {
                break;
            }
            else if (token.size() && canBreak2[currentLine.substr(row, 2)])
            {
                break;
            }
            else if (!token.size() && currentLine[row] >= '0' && currentLine[row] <= '9')
            {
                return readNumberConst();
            }

            token += currentLine[row];
            row++;

            if (currentLine[row - 1] == '\'')
            {
                return readCharConst();
            }
            else if (currentLine[row - 1] == '\"')
            {
                return readStringConst();
            }
            else if (canBreak2[currentLine.substr(row - 1, 2)])
            {
                token += currentLine[row];
                row++;
                break;
            }
            else if (canBreak[currentLine[row - 1]])
            {
                break;
            }
        }

        return make_pair(tokenId[token], token);
    }

    void printToken(std::pair<int, std::string> t)
    {
        //printf("        [%04d, %04d] (%04d, %10s) {%s}\n", t.line + 1, t.column + 1, t.type, t.getString(t.type, enumToString).c_str(), t.value.c_str());
        std::cout << "(" << t.first << ", " << token[t.first] << ") " << t.second << std::endl;
    }
};

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        std::cout << "No file provided" << std::endl;
        return 1;
    }

    buildMap();

    std::string filePath = std::string(argv[1]);
    LexicalAnalyzer analyzer(filePath);

    while (analyzer.hasToken())
    {
        std::pair<int, std::string> t = analyzer.nxtToken();
        analyzer.printToken(t);
    }
}