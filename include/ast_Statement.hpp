#ifndef ast_Statement_hpp
#define ast_Statement_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"


class For : public Node
{
public:
    For(NodePtr initialize, NodePtr condition, NodePtr increment, NodePtr statement);

    virtual ~For();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;


};

class If : public Node
{
public:
    If(NodePtr expression, NodePtr if_statement);

    virtual ~If();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;


};

class If_Else : public Node
{
public:
    If_Else(NodePtr expression, NodePtr if_statement, NodePtr else_statement);

    virtual ~If_Else();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;


};

class Return_Statement : public Node
{
public:
    Return_Statement(NodePtr expression);

    virtual ~Return_Statement();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    /*virtual void createParameterMap(context &context) const override;*/

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;

};

class Switch : public Node
{
public:
    Switch(NodePtr expression, NodePtr statement);

    virtual ~Switch();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;



};

class While : public Node
{
public:
    While(NodePtr expression, NodePtr statement);

    virtual ~While();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;


};

#endif