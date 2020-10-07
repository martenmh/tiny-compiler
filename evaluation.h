#ifndef EVALUATION_H
#define EVALUATION_H

std::string compile(AST::Node& ast);

std::stack<TokenType> registers;

std::string compileBinary(AST::Node& node){
	std::string s;
	registers.push(node.value.type);
	if(node.right()->value.type != TOKEN_NUMBER || node.right()->value.type != TOKEN_FLOAT){
		s += compile(*node.right());
		s += compile(*node.left());
	} else {
		s += compile(*node.left());
		s += compile(*node.right());
	}


	switch(node.value.type) {
		case TOKEN_PLUS:
			s += "ADD";
			break;
		case TOKEN_MIN:
			s += "SUB";
			break;
		case TOKEN_MUL:
			s += "MUL";
			break;
		case TOKEN_SLASH:
			s += "DIV";
			break;
	}
	std::string rhs = std::to_string(12 + registers.size());
	registers.pop();
	std::string lhs = std::to_string(12 + registers.size());
	registers.pop();
	std::string dst = std::to_string(12 + registers.size());
	s += (" X" + dst) + (", X" + lhs) + (", X" + rhs);

	return s;
}

// Creates a ARMv8 / x86_64 binary a.out
std::string compile(AST::Node& ast) {
	auto value = ast.value;
	std::string s;

	switch (value.type) {
		case TOKEN_PLUS:
		case TOKEN_MIN:
		case TOKEN_MUL:
		case TOKEN_SLASH:
			s += compileBinary(ast);
			break;
		case TOKEN_NUMBER:
		case TOKEN_FLOAT: {
			registers.push(ast.value.type);
			std::string reg = std::to_string(12 + registers.size());
			s += ("MOV X" + reg) + ", #";
			s += std::string(value.start, value.length);
			break;
		}
		case TOKEN_EOF:
			break;
		default:
			throw;
	}
	s += '\n';
	return s;
}
// Runs the parse tree
enum ResultType {
	NUMBER, FLOAT
};

#include <typeindex>

class Any {
	std::type_index type;
	std::unique_ptr<void> value;
public:
	template<typename T>
	Any(const T& rhs): type(typeid(T)), value(std::make_unique<void>(rhs)){}

	template<typename T>
	Any& operator=(const T& rhs){
		type = typeid(T);
		value = std::make_unique<void>(rhs);
	}
	template<typename T>
	T get(){
		return *static_cast<T*>(value.get());
	}
	int getInt(){
		return *static_cast<int*>(value.get());
	}
	float getFloat(){
		return *static_cast<float*>(value.get());
	}
};

struct InterpretResult {
	double value;
	ResultType type;
};

std::ostream& operator<<(std::ostream& os, const InterpretResult& result){
	if(result.type == FLOAT)       os << static_cast<float>(result.value);
	else if(result.type == NUMBER) os << static_cast<int>(result.value);
	return os;
}

InterpretResult interpret(AST::Node& node);

InterpretResult binary(AST::Node& node) {
	auto lhs = interpret(*node.left());
	auto rhs = interpret(*node.right());
	double value;
	switch (node.value.type) {
		case TOKEN_PLUS: value  = lhs.value + rhs.value;  break;
		case TOKEN_MIN: value   = lhs.value - rhs.value;   break;
		case TOKEN_MUL: value   = lhs.value * rhs.value;   break;
		case TOKEN_SLASH: value = lhs.value / rhs.value; break;
	}
	ResultType type = value - static_cast<int>(value) != 0 ? FLOAT : NUMBER;
	return {value, type};
}

InterpretResult interpret(AST::Node& ast) {
	auto value = ast.value;
	switch(value.type){
		case TOKEN_POW:
		case TOKEN_PLUS:
		case TOKEN_MIN:
		case TOKEN_MUL:
		case TOKEN_SLASH:  return binary(ast);
		case TOKEN_NUMBER: return {static_cast<double>(std::stoi(std::string(value.start, value.length))), NUMBER};
		case TOKEN_FLOAT:  return {std::stof(std::string(value.start, value.length)), FLOAT};
		case TOKEN_EOF:    break;
		default: throw;
	}
}


#endif //EVALUATION_H
