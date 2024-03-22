#ifndef ast_Declarator_hpp
#define ast_Declarator_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class MultiDec : public Node
{
public:
    MultiDec(NodePtr declaration_specifiers, NodePtr init_declarator_list);

    virtual ~MultiDec();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;

};

#endif
