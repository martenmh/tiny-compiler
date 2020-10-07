#include <iostream>
#include <stack>
#include <queue>


#include "tokenizer.h"

/* Parsers */
#include "parsers/ll.h"
#include "parsers/recursivedescent.h"
#include "parsers/lr.h"
#include "parsers/pratt.h"

#include "evaluation.h"

using AST = BTree<Token>;

void eval(std::string& str){
    auto p = tokenize(str);
	std::cout << p << std::endl;
	auto ast = parse(p);
	std::cout << ast << std::endl;
	std::cout << compile(ast) << std::endl;
	std::cout << interpret(ast) << std::endl;
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
    REPL();
    return 0;
}
