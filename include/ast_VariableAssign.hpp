#ifndef ast_VariableAssign_hpp
#define ast_VariableAssign_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class VariableAssign : public Node
{
public:
    VariableAssign(NodePtr declarator, NodePtr initializer);

    virtual ~VariableAssign();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual std::string Returnid() const override;

    virtual void isPointer(context &context) const override;

};

#endif
