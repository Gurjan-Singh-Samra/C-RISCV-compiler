#ifndef ast_Unary_hpp
#define ast_Unary_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class Unary : public Node
{
public:

    Unary(NodePtr unary_operator, NodePtr cast_expression);


    virtual ~Unary();


    virtual void print(std::ostream &dst, std::string indent) const override;


    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;


    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;

    virtual std::string Returnid() const override;

};

class UnaryOp : public Node
{
public:

    UnaryOp(std::string operation);


    virtual ~UnaryOp();


    virtual void print(std::ostream &dst, std::string indent) const override;


    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;


    virtual int getSize() const override;

    std::string op;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;

    virtual std::string returnOp() const override;

    virtual std::string Returnid() const override;


};

class UnaryPostOp : public Node
{
public:

    UnaryPostOp(NodePtr postfix_expression, std::string operation);


    virtual ~UnaryPostOp();


    virtual void print(std::ostream &dst, std::string indent) const override;


    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;


    virtual int getSize() const override;

    std::string op;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;
    virtual std::string Returnid() const override;
};

class SizeOf : public Node
{
public:

    SizeOf(NodePtr value);


    virtual ~SizeOf();


    virtual void print(std::ostream &dst, std::string indent) const override;


    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;


    virtual int getSize() const override;

    /*virtual void createParameterMap(context &context) const override;*/

};

#endif
