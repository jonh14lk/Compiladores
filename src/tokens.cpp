class Token {
private:
        // id do token -> identificador do token
    std::map<std::string, int> tokenId;
        // token -> id do token
    std::map<int, std::string> token;

    void initTokens() {
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

public:
    Token() {
        this->initTokens();
    }

    int getTokenId(std::string word) {
        return this->tokenId[word];
    }

    std::string getToken(int tokenId) {
        return this->token[tokenId];
    }

};

