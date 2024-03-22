#ifndef ast_ArgDeclaration_hpp
#define ast_ArgDeclaration_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class Arg_Declarator : public Node
{
public:
    Arg_Declarator(NodePtr assignment_expression);

    virtual ~Arg_Declarator();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual int GetArgLocation() const override;

    virtual std::string Returnid() const override;

};

class Arg_List_Declarator : public Node
{
public:
    Arg_List_Declarator(NodePtr argument_expression_list, NodePtr assignment_expression);

    virtual ~Arg_List_Declarator();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual int GetArgLocation() const override;

    virtual std::string Returnid() const override;

};

#endif
