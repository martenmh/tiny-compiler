//
// Created by marten on 22-09-20.
//

#ifndef PARSING_SYNTAXTREE_H
#define PARSING_SYNTAXTREE_H

#include <utility>
#include <vector>
#include <string>
#include <variant>
#include <optional>
#include <any>


enum class NodeType{
    Num, Operation, Unknown, EOL
};

enum class Precedence {
    TERM,       // +, -
    FACTOR,     // *, /
    EXPONENT,   // ^
    PAREN       // ()
};

//struct Node {
//    NodeType type;
//    std::any value;
//    std::vector<Node> nodes;
//};

#include <memory>
#include <iomanip>

enum Expression {
    ADD, SUB, MUL, DIV, POW, GROUP,
    FLOAT, INTEGER // Number literal (TOKEN_NUMBER, TOKEN_FLOAT)
};

struct ExpressionNode {
    Expression expression;
    std::any value;
    std::unique_ptr<ExpressionNode> left, right;
    ExpressionNode(ExpressionNode const & node) :
        expression(node.expression), value(node.value){
    }
    ExpressionNode(Expression expr, std::any val) : expression(expr), value(std::move(val)), left(nullptr), right(nullptr) {}
    ExpressionNode(Expression expr, std::any val, ExpressionNode left, ExpressionNode right) : expression(expr), value(std::move(val)), left(std::make_unique<ExpressionNode>(left)), right(std::make_unique<ExpressionNode>(right)) {}
};

template<typename Node>
class Tree {
public:
    std::unique_ptr<Node> root;

    Tree(){}

    Node* find(Node node);

    void insert(Node node);

    template<typename... Args>
    void emplace(Args&&... args);

    Node* data(){return root.get();}
};

void postorder(ExpressionNode* p, int indent=0)
{
    if(p) {
        if(p->left) postorder(p->left.get(), indent+4);
        if(p->right) postorder(p->right.get(), indent+4);
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        switch(p->expression){
            case FLOAT: std::cout << std::any_cast<float>(p->value);
                break;
            case INTEGER: std::cout << std::any_cast<int>(p->value);
                break;
        }
        std::cout << "\n ";
    }
}
template<typename Node>
template<typename... Args>
void Tree<Node>::emplace(Args &&... args) {
    insert(std::forward<Args>(args)...);
}

template<typename Node>
void Tree<Node>::insert(Node node) {

}

using SyntaxTree = Tree<ExpressionNode>;


#endif //PARSING_SYNTAXTREE_H
