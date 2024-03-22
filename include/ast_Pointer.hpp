#ifndef ast_Pointer_hpp
#define ast_Pointer_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class Pointer : public Node
{
public:
    Pointer();

    virtual ~Pointer();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;

};

class PointerDeclarator : public Node
{
public:
    PointerDeclarator(NodePtr pointer, NodePtr direct_declarator);

    virtual ~PointerDeclarator();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual std::string Returnid() const override;

    virtual void isPointer(context &context) const override;

};

#endif
