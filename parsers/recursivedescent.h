//
// Created by marten on 22-09-20.
//

#ifndef PARSING_RECURSIVEDESCENT_H
#define PARSING_RECURSIVEDESCENT_H

#include <vector>
#include <string>
#include <cmath>

#include "syntaxtree.h"
#include "BTree.h"

struct Expression {
	TokenType type;
	std::any value;
};

using AST = BTree<Token>;

std::optional<Token> maybe_match(std::queue<Token>& tokens, char c){
	if(*tokens.front().start == c){
		auto tok = tokens.front();
		tokens.pop();
		return tok;
	}
	else return std::nullopt;
}

template<typename ...Arr>
std::optional<Token> maybe_match(std::queue<Token>& tokens, char c, Arr&& ...args){
	std::optional<Token> tok = maybe_match(tokens, args...);
	if(tok.has_value()) {
		return tok;
	} else if(*tokens.front().start == c) {
		auto tok = tokens.front();
		tokens.pop();
		return tok;
	} else return std::nullopt;
}

AST::Node term(std::queue<Token>& tokens);

AST::Node expression(std::queue<Token>& tokens){
	auto lhs = term(tokens);
	while(true){
		std::optional<Token> op = maybe_match(tokens, '+','-');
		if(!op.has_value()) break;
		auto rhs = term(tokens);
		lhs = AST::Node(*op, lhs, rhs);
	}
	return lhs;
}

AST::Node factor(std::queue<Token>& tokens){
	auto tok = tokens.front();
	if(tok.type == TOKEN_LEFT_PAREN){
		tokens.pop();
		return expression(tokens);
	}
	tokens.pop();
	return AST::Node(tok);
}

AST::Node term(std::queue<Token>& tokens){
	auto lhs = factor(tokens);
	while(tokens.front().type != TOKEN_EOF){
		std::optional<Token> op = maybe_match(tokens, '*','/');
		if(!op.has_value()) break;
		auto rhs = factor(tokens);
		lhs = AST::Node(*op, lhs, rhs);
	}
	return lhs;
}

AST parse(std::queue<Token>& tokens){
	return AST(expression(tokens));
}

#endif //PARSING_RECURSIVEDESCENT_H
