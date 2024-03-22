#ifndef ast_ParamDeclaration_hpp
#define ast_ParamDeclaration_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class Param_Declarator : public Node
{
public:

    Param_Declarator(NodePtr declaration_specifier, NodePtr declarator);

    virtual ~Param_Declarator();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createParameterMap(context &context) const override;

    virtual void isPointer(context &context) const override;

};

class Param_List : public Node
{
public:

    Param_List(NodePtr parameter_list);

    virtual ~Param_List();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createParameterMap(context &context) const override;

    virtual void isPointer(context &context) const override;
};

class Param_List_Declarator : public Node
{
public:

    Param_List_Declarator(NodePtr parameter_list, NodePtr parameter_declaration);


    virtual ~Param_List_Declarator();


    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createParameterMap(context& context) const override;

    virtual void isPointer(context &context) const override;

};

#endif
