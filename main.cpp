#include <iostream>
#include <stack>
#include <queue>


#include "tokenizer.h"

/* Parsers */
#include "parsers/ll.h"
#include "parsers/recursivedescent.h"
#include "parsers/lr.h"
#include "parsers/pratt.h"

//// Creates a ARMv8 / x86_64 binary example.out
//void compile(ParseTree tree){}
//// Runs the parse tree
//void interpret(ParseTree tree){}


void eval(std::string& str){
//    interpret(LRparse(tokenize(str)));
//    interpret(LLparse(tokenize(str)));
//    interpret(prattParse(tokenize(str)));
//    prattParse
    //compile(parse(tokenize(str)));
    auto p = tokenize(str);
    for(auto& token : p){
        std::cout << "\"" << std::string(token.start,token.length) << "\", ";
    }
    std::cout << std::endl;
}

void REPL(){
    while(true){
        std::cout << "> ";
        std::string input;
        std::cin >> input;
        if(input == ":q"){
            break;
        } else {
            eval(input);
        }
    }
}

int main() {
    //SyntaxTree a;
    //ExpressionNode root(ADD, 0, {INTEGER, 52}, {FLOAT, 3.62});
    //postorder(&root);
    //a.emplace(ADD, NULL, ExpressionNode{FLOAT, 3.52}, ExpressionNode{INTEGER, 1});
    REPL();
    return 0;
}
