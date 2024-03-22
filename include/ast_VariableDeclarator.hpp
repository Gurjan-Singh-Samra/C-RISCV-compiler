#ifndef ast_VariableDeclarator_hpp
#define ast_VariableDeclarator_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class VariableDeclarator : public Node
{
public:
    VariableDeclarator(NodePtr declarator);

    virtual ~VariableDeclarator();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual std::string Returnid() const override;

    virtual void isPointer(context &context) const override;

};

#endif
