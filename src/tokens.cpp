class Token {
private:
    std::map<std::string, int> tokenId;
    std::map<int, std::string> tokenIdToStr;

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
        tokenId["return"] = 47;
        tokenId["CharConst"] = 48;
        tokenId["StringConst"] = 49;
        tokenId["DoubleConst"] = 50;
        tokenId["IntConst"] = 51;
        tokenId["true"] = 52;
        tokenId["false"] = 52;
        tokenId["."] = 53;
        tokenId["append"] = 54;

        tokenIdToStr[0] = "Identificator";
        tokenIdToStr[1] = "DefFunction";
        tokenIdToStr[2] = "ReservedMain";
        tokenIdToStr[3] = "TypeVoid";
        tokenIdToStr[4] = "TypeInteger";
        tokenIdToStr[5] = "TypeDouble";
        tokenIdToStr[6] = "TypeChar";
        tokenIdToStr[7] = "TypeBoolean";
        tokenIdToStr[8] = "TypeString";
        tokenIdToStr[9] = "TypeList";
        tokenIdToStr[10] = "OpenBrace";
        tokenIdToStr[11] = "CloseBrace";
        tokenIdToStr[12] = "OpenBrack";
        tokenIdToStr[13] = "CloseBrack";
        tokenIdToStr[14] = "OpenPar";
        tokenIdToStr[15] = "ClosePar";
        tokenIdToStr[16] = "EndLine";
        tokenIdToStr[17] = "ReservedIf";
        tokenIdToStr[18] = "ReservedElseIf";
        tokenIdToStr[19] = "ReservedElse";
        tokenIdToStr[20] = "ReservedFor";
        tokenIdToStr[21] = "ReservedWhile";
        tokenIdToStr[22] = "ReservedWrite";
        tokenIdToStr[23] = "ReservedRead";
        tokenIdToStr[24] = "SignalSemiColon";
        tokenIdToStr[25] = "SignalComma";
        tokenIdToStr[26] = "OperationAdd";
        tokenIdToStr[27] = "OperationSub";
        tokenIdToStr[28] = "OperationMult";
        tokenIdToStr[29] = "OperationDiv";
        tokenIdToStr[30] = "OperationInc";
        tokenIdToStr[31] = "OperationDec";
        tokenIdToStr[32] = "OperationConc";
        tokenIdToStr[33] = "OperationNot";
        tokenIdToStr[34] = "OperationXor";
        tokenIdToStr[35] = "OperationOr";
        tokenIdToStr[36] = "OperationAnd";
        tokenIdToStr[37] = "LogicAnd";
        tokenIdToStr[38] = "LogicOr";
        tokenIdToStr[39] = "LogicNot";
        tokenIdToStr[40] = "AtributionEqual";
        tokenIdToStr[41] = "RelationEqual";
        tokenIdToStr[42] = "RelationNotEqual";
        tokenIdToStr[43] = "RelationGreater";
        tokenIdToStr[44] = "RelationLower";
        tokenIdToStr[45] = "RelationGreaterEqual";
        tokenIdToStr[46] = "RelationLowerEqual";
        tokenIdToStr[47] = "ReservedReturn";
        tokenIdToStr[48] = "CharConst";
        tokenIdToStr[49] = "StringConst";
        tokenIdToStr[50] = "DoubleConst";
        tokenIdToStr[51] = "IntConst";
        tokenIdToStr[52] = "BooleanConst";
        tokenIdToStr[53] = "SignalDot";
        tokenIdToStr[54] = "ReservedAppend";
    }

public:
    Token() {
        this->initTokens();
    }

    int getTokenId(std::string token) {
        return this->tokenId[token];
    }

    std::string getToken(int tokenId) {
        return this->tokenIdToStr[tokenId];
    }

};

