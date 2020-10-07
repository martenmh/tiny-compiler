//
// Created by marten on 22-09-20.
//

#ifndef PARSING_SYNTAXTREE_H
#define PARSING_SYNTAXTREE_H

#include "BTree.h"
#include "tokenizer.h"
#include <any>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

enum class NodeType{
    Num, Operation, Unknown, EOL
};

enum class Precedence {
    TERM,       // +, -
    FACTOR,     // *, /
    EXPONENT,   // ^
    PAREN       // ()
};
#include <iomanip>

template<typename T>
void printBT(std::ostream& os, TreeNode<T>* node, const std::string& prefix = "" , bool isLeft = false){
	if(node){
		os << prefix;
		os << (isLeft ? "├──" : "└──" );

		// print the value of the node
		os << node->value << std::endl;
		// enter the next tree level - left and right branch
		printBT(os, node->left(), prefix + (isLeft ? "│   " : "    "), true);
		printBT(os, node->right(), prefix + (isLeft ? "│   " : "    "), false);
	}
}


#endif //PARSING_SYNTAXTREE_H
