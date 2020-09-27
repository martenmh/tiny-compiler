//
// Created by marten on 22-09-20.
//

#ifndef PARSING_RECURSIVEDESCENT_H
#define PARSING_RECURSIVEDESCENT_H

#include <vector>
#include <string>

#include "syntaxtree.h"


class RecursiveDescentParser {
};
SyntaxTree rparse(std::vector<Token> tokens){
    SyntaxTree tree;
    Precedence p;
    for(int i = 0; tokens[i].type != TOKEN_EOF; i++){
        switch(tokens[i].type){
            case TOKEN_NUMBER: break;
            case TOKEN_PLUS: break;
            case TOKEN_MIN: break;
            case TOKEN_MUL: break;
            case TOKEN_SLASH: break;
            case TOKEN_LEFT_PAREN: break;
            case TOKEN_POW: break;
            //default: break;
        }
       //tree.emplace_back(Node{.type = NodeType::Num, .value = std::stof(tokens[i])});

    }
}

#endif //PARSING_RECURSIVEDESCENT_H
