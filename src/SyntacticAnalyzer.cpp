#include "LexicalAnalyzer.cpp"

class SyntacticAnalyzer {
private:
    LexicalAnalyzer lexical;
    std::pair<Token, std::string> token_pair;
    int token;

public:
    SyntacticAnalyzer(std::string filePath) {
        lexical = LexicalAnalyzer(filePath);
        S();
    }

    void printProduction(std::string production) {
        printf("          %s\n", production.c_str());
    }

    bool hasToken() {
        return lexical.hasToken();
    }

    void printToken() {
        lexical.printToken(token_pair);
    }
    
    void nxtToken() {
        if(!hasToken()) {
            std::cout << "Expected Token\n";
            exit(1);
        }
        token_pair = lexical.nxtToken();
        token = token_pair.first;
    }

    bool isDeclaration() {
        return (token >= Token::TypeInteger && token <= Token::TypeList);
    }

    bool isType() {
        return (token >= Token::TypeInteger && token <= Token::TypeString);
    }

    bool isBitwise() {
        return (token == Token::OperationOr || token == Token::OperationXor || token == Token::OperationAnd);
    }

    bool isAdditive() {
        return (token == Token::OperationAdd || token == Token::OperationSub);
    }

    bool isMultiplicative() {
        return (token == Token::OperationMult || token == Token::OperationDiv);
    }

    bool isIncrement() {
        return (token == Token::OperationInc || token == Token::OperationDec);
    }
    
    bool isConst() {
        return (token >= Token::CharConst && token <= Token::BooleanConst);
    }

    bool isValue() {
        return (isConst() || token == Token::Identificator);
    }

    bool isRel() {
        return (token >= Token::RelationEqual && token <= Token::RelationLowerEqual);
    }

    void checkToken(int expected) {
        if (token != expected) {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
        printToken();
    }

    void checkValue() {
        if (token == Token::Identificator || isConst()) {
            printToken();
            return;
        }
        std::cout << "Syntactic Error\n";
        exit(1);
    }

    void checkIncrement() {
        if (isIncrement()) {
            printToken();
            return;
        }
        std::cout << "Syntactic Error\n";
        exit(1);
    }

    void CheckInt() {
        nxtToken();
        if (token == Token::Identificator || token == Token::IntConst) {
            printToken();
            return;
        }
        std::cout << "Syntactic Error\n";
        exit(1);
    }

    void checkNxt(int expected) {
        nxtToken();
        checkToken(expected);
    }

    void checkType() {
        nxtToken();
        printToken();
        if (!isType()) {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void S() {
        if (!hasToken()) {
            printProduction("S = épsilon");
            return;
        }
        nxtToken();
        
        if (token == Token::DefFunction) {
            printProduction("S = FunctionDeclaration S");
            FunctionDeclaration();
        } else if (isDeclaration()) {
            printProduction("S = Declaration S");
            Declaration();
            checkNxt(Token::SignalSemiColon);
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }

        S();
    }

    void Declaration() {
        if (token == Token::TypeList) {
            printProduction("Declaration = ListDeclaration");
            ListDeclaration();
        } else if (isType()) {
            printProduction("Declaration = VariableDeclaration");
            VariableDeclaration();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void ListDeclaration() {
        if (token == Token::TypeList) {
            printProduction("ListDeclaration = \'list\' \'(\' Type \')\' \'Identificator\'");
            printToken();
            checkNxt(Token::OpenPar);
            checkType();
            checkNxt(Token::ClosePar);  
            checkNxt(Token::Identificator); 
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void VariableDeclaration() {
        if(isType()) {
            printProduction("VariableDeclaration = Type \'Identificator\'");
            printToken();
            checkNxt(Token::Identificator);
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void FunctionDeclaration() {
        if (token == Token::DefFunction) {
            printProduction("FunctionDeclaration = \'function\' FunctionDeclarationAuxiliar");
            printToken();
            FunctionDeclarationAuxiliar();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void FunctionDeclarationAuxiliar() {
        nxtToken();
        if (token == Token::TypeVoid) {
            printProduction("FunctionDeclarationAuxiliar = VoidFunction");
            VoidFunction();
        } else if (isType()) {
            printProduction("FunctionDeclarationAuxiliar = OtherTypeFunction");
            OtherTypeFunction();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void VoidFunction() {
        if (token == Token::TypeVoid) {
            printProduction("VoidFunction = \'void\' VoidFunctionAuxiliar");
            printToken();
            VoidFunctionAuxiliar();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }  
    }

    void VoidFunctionAuxiliar() {
        nxtToken();
        if (token == Token::ReservedMain) {
            printProduction("VoidFunctionAuxiliar = MainFunction");
            MainFunction();
        } else if (token == Token::Identificator) {
            printProduction("VoidFunctionAuxiliar = Function");
            Function();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void OtherTypeFunction() {
        if (isType()) {
            printProduction("OtherTypeFunction = FunctionType Function");
            printToken();
            nxtToken();
            Function();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void MainFunction() {
        if (token == Token::ReservedMain) {
            printProduction("MainFunction = \'main\' \'{\' \'}\' \'[\' CommandsBlock \']\'");
            printToken();
            checkNxt(Token::OpenBrace);
            checkNxt(Token::CloseBrace);
            checkNxt(Token::OpenBrack);
            nxtToken();
            CommandsBlock();
            checkToken(Token::CloseBrack);

        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void Function() {
        if (token == Token::Identificator) {
            printProduction("Function = \'Identificator\' \'{\' ParametersList \'}\' \'[\' CommandsBlock \']\'");
            printToken();
            checkNxt(Token::OpenBrace);
            Parameters();
            checkToken(Token::CloseBrace);
            checkNxt(Token::OpenBrack);
            nxtToken();
            CommandsBlock();
            checkToken(Token::CloseBrack);

        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void Parameters() {
        nxtToken();
        if (isDeclaration()) {
            printProduction("Parameters = ParametersList");
            ParametersList();
        } else {
            printProduction("Parameters = épsilon");
        } 
    }

    void ParametersList() {
        if (isDeclaration()) {
            printProduction("ParametersList = Declaration ParametersListAuxiliar");
            Declaration();
            ParametersListAuxiliar();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void ParametersListAuxiliar() {
        nxtToken();
        if (token == Token::SignalComma) {
            printProduction("ParametersListAuxiliar = \',\' ParametersList");
            printToken();
            nxtToken();

            ParametersList();
        } else {
            printProduction("ParametersListAuxiliar = épsilon");
        }
    }

    void CommandsBlock() {
        if (token == Token::Identificator) {
            printProduction("CommandsBlock = Command CommandsBlock");
            Command();
            CommandsBlock();
        } else if (isDeclaration()) {
            printProduction("CommandsBlock = Command CommandsBlock");
            Command();
            CommandsBlock();
        } else if (token == Token::ReservedIf) {
            printProduction("CommandsBlock = Command CommandsBlock");
            Command();
            CommandsBlock();
        } else if (token == Token::ReservedFor) {
            printProduction("CommandsBlock = Command CommandsBlock");
            Command();
            CommandsBlock();
        } else if (token == Token::ReservedWhile) {
            printProduction("CommandsBlock = Command CommandsBlock");
            Command();
            CommandsBlock();
        } else if (token == Token::ReservedWrite) {
            printProduction("CommandsBlock = Command CommandsBlock");
            Command();
            CommandsBlock();
        } else if (token == Token::ReservedRead) {
            printProduction("CommandsBlock = Command CommandsBlock");
            Command();
            CommandsBlock();
        } else if (token == Token::ReservedReturn) {
            printProduction("CommandsBlock = Command CommandsBlock");
            Command();
            CommandsBlock();
        } else {
            printProduction("CommandsBlock = épsilon");
        }
    }

    void Command() {
        if (token == Token::Identificator) {
            IdentificatorCommand();
            checkToken(Token::SignalSemiColon);
            nxtToken();
        } else if (isDeclaration()) {
            printProduction("Command = DeclarationCommand \';\'");
            DeclarationCommand();
            checkToken(Token::SignalSemiColon);
            nxtToken();
        } else if (token == Token::ReservedIf) {
            Condition();
        } else if (token == Token::ReservedFor) {
            Loop();
        } else if (token == Token::ReservedWhile) {
            Loop();
        } else if (token == Token::ReservedWrite) {
            Output();
            checkToken(Token::SignalSemiColon);
            nxtToken();
        } else if (token == Token::ReservedRead) {
            Input();
            checkToken(Token::SignalSemiColon);
            nxtToken();
        } else if (token == Token::ReservedReturn) {
            Return();
            checkToken(Token::SignalSemiColon);
            nxtToken();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void DeclarationCommand() {
        if (token == Token::TypeList) {
            printProduction("DeclarationCommand = ListDeclaration");
            ListDeclaration();
            nxtToken();
        } else {
            printProduction("DeclarationCommand = VariableDeclaration DeclarationCommandAuxiliar");
            VariableDeclaration();
            DeclarationCommandAuxiliar();
        }
    }

    void DeclarationCommandAuxiliar() {
        nxtToken();
        if (token == Token::AtributionEqual) {
            printProduction("DeclarationCommandAuxiliar = AttributionExpression");
            AttributionExpression();
        } else {
            printProduction("DeclarationCommandAuxiliar = épsilon");
        }
    }

    void AttributionExpression() {
        if (token == Token::AtributionEqual) {
            printProduction("AttributionExpression = \'=\' ArithmeticExpression");
            printToken();
            nxtToken();
            ArithmeticExpression();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void ArithmeticExpression() {
        printProduction("ArithmeticExpression = AddtiveExpression ArithmeticAuxiliar");
        AdditiveExpression();
        ArithmeticAuxiliar();
    }

    void ArithmeticAuxiliar(){
        if (isBitwise()) {
            printProduction("ArithmeticAuxiliar = BitwiseOperation AddtiveExpression ArithmeticAuxiliar");
            printToken();
            nxtToken();
            AdditiveExpression();
            ArithmeticAuxiliar();
        } else {
            printProduction("ArithmeticAuxiliar = épsilon");
        }
    }

    void AdditiveExpression() {
        printProduction("AddtiveExpression = MultiplicativeExpression AddtiveAuxiliar");
        MultiplicativeExpression();
        AdditiveAuxiliar();
    }

    void AdditiveAuxiliar() {
        if (isAdditive()) {
            printProduction("AddtiveAuxiliar = AddtiveOperation MultiplicativeExpression AddtiveAuxiliar");
            printToken();
            nxtToken();
            MultiplicativeExpression();
            AdditiveAuxiliar();
        } else {
            printProduction("AddtiveAuxiliar = épsilon");
        }
    }

    void MultiplicativeExpression() {
        printProduction("MultiplicativeExpression = ArithmeticValue MultiplicativeAuxiliar");
        ArithmeticValue();
        MultiplicativeAuxiliar();
    }

    void MultiplicativeAuxiliar() {
        if (isMultiplicative()) {
            printProduction("MultiplicativeAuxiliar = MultiplicativeOperation ArithmeticValue MultiplicativeAuxiliar");
            printToken();
            nxtToken();
            ArithmeticValue();
            MultiplicativeAuxiliar();
        } else {
            printProduction("MultiplicativeAuxiliar = épsilon");
        }
    }

    void ArithmeticValue() {
        printProduction("ArithmeticValue = ArithmeticFactor ArithmeticValueAuxiliar");
        ArithmeticFactor();
        ArithmeticValueAuxiliar();
    }

    void ArithmeticValueAuxiliar() {
        if (isIncrement()) {
            printProduction("ArithmeticValueAuxiliar = IncrementOperation");
            printToken();
            nxtToken();
        } else {
            printProduction("ArithmeticValueAuxiliar = épsilon");
        }
    }

    void ArithmeticFactor() {
        if (isConst()) {
            printProduction("ArithmeticFactor = Constant");
            printToken();
            nxtToken();
        } else if (token == Token::Identificator) {
            printProduction("ArithmeticFactor = IdentificatorFactor");
            IdentificatorFactor();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void IdentificatorFactor() {
        printProduction("IdentificatorFactor = \'Identificator\' IdentificatorFactorAuxiliar");
        checkToken(Token::Identificator);
        nxtToken();
        IdentificatorFactorAuxiliar();
    }

    void IdentificatorFactorAuxiliar() {
        if (token == Token::OpenBrace) {
            printProduction("IdentificatorFactorAuxiliar = FunctionCall");
            FunctionCall();
        } else if (token == Token::OpenPar) {
            printProduction("IdentificatorFactorAuxiliar = ListAcess");
            ListAcess();
        } else {
            printProduction("IdentificatorFactorAuxiliar = épsilon");
        }
    }
    
    void ListAcess() {
        checkToken(Token::OpenPar);
        nxtToken();
        ArithmeticExpression();
        checkToken(Token::ClosePar);
        nxtToken();
    }

    void FunctionCall() {
        printProduction("FunctionCall = \'{\' IdList \'}\'");
        checkToken(Token::OpenBrace);
        IdList();
        checkToken(Token::CloseBrace);
        nxtToken();
    }

    void IdList() {
        nxtToken();
        if (token == Token::Identificator) {
            printProduction("IdList = IdSequence");
            IdSequence();
        } else {
            printProduction("IdList = épsilon");
        }
    }

    void IdSequence() {
        if (token == Token::Identificator) {
            printProduction("IdSequence = \'Identificator\' IdSequenceAuxiliar");
            printToken();
            IdSequenceAuxiliar();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void IdSequenceAuxiliar() {
        nxtToken();
        if(token == Token::SignalComma) {
            printProduction("IdSequenceAuxiliar = \',\'  IdList");
            printToken();
            IdList();
        } else {
            printProduction("IdSequenceAuxiliar = épsilon");
        }
    }

    void Condition() {
        printProduction("Condition = IfCommand ConditionAuxiliar");
        IfCommand();
        ConditionAuxiliar();
    }
    
    void ElseCondition() {
        if(token == Token::ReservedElseIf) {
            printProduction("ElseCondition = ElseIfCommand ConditionAuxiliar");
            ElseIfCommand();
            ConditionAuxiliar();
        } else if (token == Token::ReservedElse) {
            printProduction("ElseCondition = ElseCommand");
            ElseCommand();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void ConditionAuxiliar() {
        if(token == Token::ReservedElseIf) {
            printProduction("ConditionAuxiliar = ElseCondition");
            ElseCondition();
        } else if (token == Token::ReservedElse) {
            printProduction("ConditionAuxiliar = ElseCondition");
            ElseCondition();
        } else {
            printProduction("ConditionAuxiliar = épsilon");
        }
    }

    void IfCommand() {
        printProduction("IfCommand = \'if\' \'{\' BooleanExpression  \'}\' \'[\' CommandsBlock  \']\'");
        checkToken(Token::ReservedIf);
        checkNxt(Token::OpenBrace);
        nxtToken();
        BooleanExpression();
        checkToken(Token::CloseBrace);
        checkNxt(Token::OpenBrack);
        nxtToken();
        CommandsBlock();
        checkToken(Token::CloseBrack);
        nxtToken();
    }

    void ElseIfCommand() {
        printProduction("ElseIfCommand = \'elseif\' \'{\' BooleanExpression  \'}\' \'[\' CommandsBlock  \']\'");
        checkToken(Token::ReservedElseIf);
        checkNxt(Token::OpenBrace);
        nxtToken();
        BooleanExpression();
        checkToken(Token::CloseBrace);
        checkNxt(Token::OpenBrack);
        nxtToken();
        CommandsBlock();
        checkToken(Token::CloseBrack);
        nxtToken();
    }

    void ElseCommand() {
        printProduction("ElseCommand = \'else\' \'[\' CommandsBlock  \']\'");
        checkToken(Token::ReservedElse);
        checkNxt(Token::OpenBrack);
        nxtToken();
        CommandsBlock();
        checkToken(Token::CloseBrack);
        nxtToken();
    }

    void Loop() {
        if (token == Token::ReservedFor) {
            printProduction("Loop = ForStatement");
            ForStatement();
        } else if (token == Token::ReservedWhile) {
            printProduction("Loop = WhileStatement");
            WhileStatement();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void WhileStatement() {
        printProduction("WhileStatement = \'while\' \'{\' BooleanExpression \'}\' \'[\' CommandsBlock \']\'");
        checkToken(Token::ReservedWhile);
        checkNxt(Token::OpenBrace);
        nxtToken();
        BooleanExpression();
        checkToken(Token::CloseBrace);
        checkNxt(Token::OpenBrack);
        nxtToken();
        CommandsBlock();
        checkToken(Token::CloseBrack);
        nxtToken();
    }

    void ForStatement() {
        printProduction("ForStatement = \'for\' \'{\' \'Identificator\' ForStatmentAuxiliar");
        checkToken(Token::ReservedFor);
        checkNxt(Token::OpenBrace);
        checkNxt(Token::Identificator);
        ForStatementAuxiliar();
    }

    void ForStatementAuxiliar() {
        nxtToken();
        if (token == Token::SignalComma) {
            printProduction("ForStatmentAuxiliar = CounterForStatement");
            CounterForStatement();
        } else if (token == Token::AtributionEqual) {
            printProduction("ForStatmentAuxiliar = LogicForStatement");
            LogicForStatement();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void LogicForStatement() {
        printProduction("LogicForStatement = AttributionExpression \';\' BooleanExpression \';\' ArithmeticExpression \'}\' \'[\' CommandsBlock \']\'");
        AttributionExpression();
        checkToken(Token::SignalSemiColon);
        nxtToken();
        BooleanExpression();
        checkToken(Token::SignalSemiColon);
        nxtToken();
        ArithmeticExpression();
        checkToken(Token::CloseBrace);
        checkNxt(Token::OpenBrack);
        nxtToken();
        CommandsBlock();
        checkToken(Token::CloseBrack);
        nxtToken();
    }

    void CounterForStatement() {
        printProduction("CounterForStatement = \',\'  IntValue \',\' IntValue \',\' IntValue CounterForStatementAuxiliar");
        checkToken(Token::SignalComma);
        CheckInt();
        checkNxt(Token::SignalComma);
        CheckInt();
        CounterForStatementAuxiliar();
    }

    void CounterForStatementAuxiliar() {
        printProduction("CounterForStatementAuxiliar =  \'}\' \'[\' CommandsBlock \']\' | \',\' IntValue \'}\' \'[\' CommandsBlock \']\'");
        nxtToken();
        if (token == Token::CloseBrace) {
            checkToken(Token::CloseBrace);
            checkNxt(Token::OpenBrack);
            nxtToken();
            CommandsBlock();
            checkToken(Token::CloseBrack);
            nxtToken();
        } else if (token == Token::SignalComma) {
            checkToken(Token::SignalComma);
            CheckInt();
            checkNxt(Token::CloseBrace);
            checkNxt(Token::OpenBrack);
            nxtToken();
            CommandsBlock();
            checkToken(Token::CloseBrack);
            nxtToken();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void Output() {
        printProduction("Output = \'write\' \'{\' OutputValues \'}\'");
        checkToken(Token::ReservedWrite);
        checkNxt(Token::OpenBrace);
        OutputValues();
        checkToken(Token::CloseBrace);
        nxtToken();
    }

    void OutputValues() {
        printProduction("OutputValues = Value OutputValuesAuxiliar");
        nxtToken();
        ArithmeticExpression();
        OutputValuesAuxiliar();
    }

    void OutputValuesAuxiliar() {
        if (token == Token::SignalComma) {
            printProduction("OutputValuesAuxiliar = OutputValues");
            OutputValues();
        } else {
            printProduction("OutputValuesAuxiliar = épsilon");
        }
    }

    void Input() {
        printProduction("Input = \'read\' \'{\' IdList \'}\'");
        checkToken(Token::ReservedRead);
        checkNxt(Token::OpenBrace);
        nxtToken();
        IdSequence();
        checkToken(Token::CloseBrace);
        nxtToken();
    }

    void Return() {
        printProduction("Return = \'return\' ArithmeticExpression");
        checkToken(Token::ReservedReturn);
        nxtToken();
        ArithmeticExpression();
    }

    void BooleanExpression() {
        printProduction("BooleanExpression = BooleanTerm BooleanAuxiliar");
        BooleanTerm();
        BooleanAuxiliar();
    }

    void BooleanAuxiliar() {
        if (token == Token::LogicOr) {
            printProduction("BooleanAuxiliar = \'LogicOr\' BooleanTerm BooleanAuxiliar");
            printToken();
            nxtToken();
            BooleanTerm();
            BooleanAuxiliar();
        } else {
            printProduction("BooleanAuxiliar = épsilon");
        }
    }

    void BooleanTerm() {
        printProduction("BooleanTerm = BooleanFactor BooleanAuxiliarTerm");
        BooleanFactor();
        BooleanAuxiliarTerm();
    } 

    void BooleanAuxiliarTerm() {
        if (token == Token::LogicAnd) {
            printProduction("BooleanAuxiliarTerm = \'LogicAnd\' BooleanFactor BooleanAuxiliarTerm");
            printToken();
            nxtToken();
            BooleanFactor();
            BooleanAuxiliarTerm();
        } else {
            printProduction("BooleanAuxiliarTerm = épsilon");
        }
    }

    void BooleanFactor() {
        if (token == Token::LogicNot) {
            printProduction("BooleanFactor = \'LogicNot\' BooleanRelation");
            printToken();
            nxtToken();
            BooleanRelation();
        } else {
            printProduction("BooleanFactor = BooleanRelation");
            BooleanRelation();
        }
    }
    
    void BooleanRelation() {
        printProduction("BooleanRelation = ArithmeticExpression BooleanRelationAuxiliar");
        ArithmeticExpression();
        BooleanRelationAuxiliar();
    }

    void BooleanRelationAuxiliar() {
        if (isRel()) {
            printProduction("BooleanRelationAuxiliar = LogicalRelation ArithmeticExpression");
            printToken();
            nxtToken();
            ArithmeticExpression();
        } else {
            printProduction("BooleanRelationAuxiliar = épsilon");
        }
    }

    void IdentificatorCommand() {
        if (token == Token::Identificator) {
            printProduction("IdentificatorCommand = \'Identificator\' IdentificatorCommandAuxiliar");
            printToken();
            nxtToken();
            IdentificatorCommandAuxiliar();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void IdentificatorCommandAuxiliar() {
        if (token == Token::OpenBrace) {
            printProduction("IdentificatorCommandAuxiliar = FunctionCall");
            FunctionCall();
        } else if (token == Token::AtributionEqual) {
            printProduction("IdentificatorCommandAuxiliar = AttributionExpression");
            AttributionExpression();
        } else if (token == Token::SignalDot) {
            printProduction("IdentificatorCommandAuxiliar = AppendList");
            AppendList();
        } else if (token == Token::OpenPar) {
            printProduction("IdentificatorCommandAuxiliar = ListAcessAuxiliar");
            ListAcessAuxiliar();
        } else if (isIncrement()) {
            checkIncrement();
            nxtToken();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void ListAcessAuxiliar() {
        printProduction("IdentificatorCommandAuxiliar = ListAcess AttributionExpression");
        ListAcess();
        if (token == Token::AtributionEqual) {
            AttributionExpression();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void AppendList() {
        printProduction("AppendList = \'.\' \'append\' \'{\' ArithmeticExpression \'}\'");
        checkToken(Token::SignalDot);
        checkNxt(Token::ReservedAppend);
        checkNxt(Token::OpenBrace);
        nxtToken();
        ArithmeticExpression();
        checkToken(Token::CloseBrace);
        nxtToken();
    }
};