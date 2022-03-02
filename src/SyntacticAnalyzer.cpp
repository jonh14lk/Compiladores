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
        token_pair = lexical.nxtToken();
        token = token_pair.first;
    }

    bool isDeclaration() {
        return (token >= Token::TypeInteger && token <= Token::TypeList);
    }

    bool isType() {
        return (token >= Token::TypeInteger && token <= Token::TypeString);
    }

    void S() {
        if (!hasToken()) {
            return;
        }
        nxtToken();
        printProduction("S = FunctionDeclaration S | Declaration S | épsilon");
        printToken();
        
        if (token == Token::DefFunction) {
            FunctionDeclaration();
        } else if (isDeclaration()) {
            Declaration();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }

        S();
    }

    void Declaration() {
        printProduction("Declaration = VariableDeclaration | ListDeclaration");
        printToken();
        if (token == Token::TypeList) {
            ListDeclaration();
        } else if (isType()) {
            VariableDeclaration();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void ListDeclaration() {
        if (!hasToken()) {
            return;
        }
        nxtToken();
        printProduction("ListDeclaration = \'list\' \'(\' Type \')\' \'Identificator\'");
        printToken();

        if (token == Token::OpenPar) {
            checkType();
            checkNxt(ClosePar);  
            checkNxt(Identificator); 
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void checkNxt(int expected) {
        if (!hasToken()) {
            return;
        }
        nxtToken();
        printToken();

        if (token != expected) {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void checkType() {
        if (!hasToken()) {
            return;
        }
        nxtToken();
        printToken();

        if (!isType()) {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void VariableDeclaration() {
        if(!hasToken()) {
            return;
        }
        nxtToken();
        printToken();

        if(isType()) {
            checkNxt(Token::Identificator);
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void FunctionDeclaration() {
        printProduction("FunctionDeclaration = \'function\' FunctionDeclarationAuxiliar");
        if (token == Token::DefFunction) {
            FunctionDeclarationAuxiliar();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void FunctionDeclarationAuxiliar() {
        if(!hasToken()) {
            return;
        }
        nxtToken();
        printProduction("FunctionDeclarationAuxiliar = VoidFunction OtherTypeFunction");
        printToken();

        if (token == Token::TypeVoid) {
            VoidFunction();
        } else if (isType()) {
            // OtherTypeFunction()
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
    }

    void VoidFunction() {
        if(!hasToken()) {
            return;
        }
        nxtToken();
        printProduction("VoidFunction = \'void\' VoidFunctionAuxiliar");
        printToken();

        if (token == Token::ReservedMain) {
           //VoidFunctionAuxiliar();
        } else if (token == Token::Identificator) {
            //VoidFunctionAuxiliar();
        } else {
            std::cout << "Syntactic Error\n";
            exit(1);
        }
        
    }
};