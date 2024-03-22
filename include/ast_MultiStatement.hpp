#ifndef ast_MultiStatement_hpp
#define ast_MultiStatement_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class MultiStatement : public Node
{
public:
    MultiStatement(NodePtr statement_list, NodePtr statement);

    virtual ~MultiStatement();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;
};

#endif
