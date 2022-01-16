class TokenClassifier {
private:
    std::unordered_map<int, std::string> tokenIdToStr;

    void initTokens() {
		tokenIdToStr[Token::Identificator] = "Identificator";
		tokenIdToStr[Token::DefFunction] = "DefFunction";
		tokenIdToStr[Token::ReservedMain] = "ReservedMain";
		tokenIdToStr[Token::TypeVoid] = "TypeVoid";
		tokenIdToStr[Token::TypeInteger] = "TypeInteger";
		tokenIdToStr[Token::TypeDouble] = "TypeDouble";
		tokenIdToStr[Token::TypeChar] = "TypeChar";
		tokenIdToStr[Token::TypeBoolean] = "TypeBoolean";
		tokenIdToStr[Token::TypeString] = "TypeString";
		tokenIdToStr[Token::TypeList] = "TypeList";
		tokenIdToStr[Token::OpenBrace] = "OpenBrace";
		tokenIdToStr[Token::CloseBrace] = "CloseBrace";
		tokenIdToStr[Token::OpenBrack] = "OpenBrack";
		tokenIdToStr[Token::CloseBrack] = "CloseBrack";
		tokenIdToStr[Token::OpenPar] = "OpenPar";
		tokenIdToStr[Token::ClosePar] = "ClosePar";
		tokenIdToStr[Token::EndLine] = "EndLine";
		tokenIdToStr[Token::ReservedIf] = "ReservedIf";
		tokenIdToStr[Token::ReservedElseIf] = "ReservedElseIf";
		tokenIdToStr[Token::ReservedElse] = "ReservedElse";
		tokenIdToStr[Token::ReservedFor] = "ReservedFor";
		tokenIdToStr[Token::ReservedWhile] = "ReservedWhile";
		tokenIdToStr[Token::ReservedWrite] = "ReservedWrite";
		tokenIdToStr[Token::ReservedRead] = "ReservedRead";
		tokenIdToStr[Token::SignalSemiColon] = "SignalSemiColon";
		tokenIdToStr[Token::SignalComma] = "SignalComma";
		tokenIdToStr[Token::OperationAdd] = "OperationAdd";
		tokenIdToStr[Token::OperationSub] = "OperationSub";
		tokenIdToStr[Token::OperationMult] = "OperationMult";
		tokenIdToStr[Token::OperationDiv] = "OperationDiv";
		tokenIdToStr[Token::OperationInc] = "OperationInc";
		tokenIdToStr[Token::OperationDec] = "OperationDec";
		tokenIdToStr[Token::OperationConc] = "OperationConc";
		tokenIdToStr[Token::OperationNot] = "OperationNot";
		tokenIdToStr[Token::OperationXor] = "OperationXor";
		tokenIdToStr[Token::OperationOr] = "OperationOr";
		tokenIdToStr[Token::OperationAnd] = "OperationAnd";
		tokenIdToStr[Token::LogicAnd] = "LogicAnd";
		tokenIdToStr[Token::LogicOr] = "LogicOr";
		tokenIdToStr[Token::LogicNot] = "LogicNot";
		tokenIdToStr[Token::AtributionEqual] = "AtributionEqual";
		tokenIdToStr[Token::RelationEqual] = "RelationEqual";
		tokenIdToStr[Token::RelationNotEqual] = "RelationNotEqual";
		tokenIdToStr[Token::RelationGreater] = "RelationGreater";
		tokenIdToStr[Token::RelationLower] = "RelationLower";
		tokenIdToStr[Token::RelationGreaterEqual] = "RelationGreaterEqual";
		tokenIdToStr[Token::RelationLowerEqual] = "RelationLowerEqual";
		tokenIdToStr[Token::ReservedReturn] = "ReservedReturn";
		tokenIdToStr[Token::CharConst] = "CharConst";
		tokenIdToStr[Token::StringConst] = "StringConst";
		tokenIdToStr[Token::DoubleConst] = "DoubleConst";
		tokenIdToStr[Token::IntConst] = "IntConst";
		tokenIdToStr[Token::BooleanConst] = "BooleanConst";
		tokenIdToStr[Token::SignalDot] = "SignalDot";
		tokenIdToStr[Token::ReservedAppend] = "ReservedAppend";
        tokenIdToStr[Token::Unknown] = "Unknown";
    }

public:
    TokenClassifier() {
        this->initTokens();
    }

    Token classify(std::string token) {
        std::unordered_map<std::string, Token> reserved_words = {
            {"str", Token::TypeString},
            {"bool", Token::TypeBoolean},
            {"dbl", Token::TypeDouble},
            {"itg", Token::TypeInteger},
            {"void", Token::TypeVoid},
            {"list", Token::TypeList},
            {"main", Token::ReservedMain},
            {"function", Token::DefFunction},
            {"if", Token::ReservedIf},
            {"elseif", Token::ReservedElseIf},
            {"else", Token::ReservedElse},
            {"write", Token::ReservedWrite},
            {"read", Token::ReservedRead}

        };
        Token tokenType = reserved_words[token];
        if(!tokenType) {
            return Token::Identificator;
        }
        return tokenType;
    }

    std::string getToken(Token token) {
        return this->tokenIdToStr[token];
    }

};

