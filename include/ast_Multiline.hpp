#ifndef ast_Multiline_hpp
#define ast_Multiline_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class Multiline : public Node
{
public:
    Multiline(NodePtr declaration_list, NodePtr statement_list);

    virtual ~Multiline();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;

};

#endif
