#ifndef ast_Array_hpp
#define ast_Array_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class Array : public Node
{
public:
    NodePtr id_;
    NodePtr index_;

    Array(NodePtr id, NodePtr index);

    virtual ~Array();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

};

class ArrayIndex : public Node
{
public:
    ArrayIndex(NodePtr id, NodePtr index);

    virtual ~ArrayIndex();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;
};

#endif
