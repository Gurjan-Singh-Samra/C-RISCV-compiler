#ifndef ast_Functions_hpp
#define ast_Functions_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class Function_Declarator : public Node
{
public:
    Function_Declarator(NodePtr direct_declarator, NodePtr parameter_type_list);

    virtual ~Function_Declarator();

    virtual void print(std::ostream &dst, std::string indent) const override;
    
    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual NodePtr returnBranch(int index) const override;

    virtual std::string Returnid() const override;

    virtual void createParameterMap(context &context) const override;

    virtual void isPointer(context &context) const override;

};

class Function_Definition : public Node
{
public:
    Function_Definition(NodePtr declaration_specifier, NodePtr declarator, NodePtr compound_statement);
    
    virtual ~Function_Definition();

    virtual void print(std::ostream &dst, std::string indent) const override;
    
    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual NodePtr returnBranch(int index) const override;

};

class Function_Call_With_Arguments
 : public Node
{
public:
    
    Function_Call_With_Arguments(NodePtr postfix_expression, NodePtr argument_expression_list);

    
    virtual ~Function_Call_With_Arguments();

    
    virtual void print(std::ostream &dst, std::string indent) const override;
    
    
    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

     
    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;

};

class Function_Call_With_NoArguments : public Node
{
public:
    
    Function_Call_With_NoArguments(NodePtr postfix_expression);

    
    virtual ~Function_Call_With_NoArguments();

    
    virtual void print(std::ostream &dst, std::string indent) const override;
    
    
    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

     
    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;


};


#endif