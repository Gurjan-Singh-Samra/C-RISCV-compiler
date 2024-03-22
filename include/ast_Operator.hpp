#ifndef ast_Operator_hpp
#define ast_Operator_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>

#include "ast_Node.hpp"

enum OperatorType
{
    Add,
    Subtract,
    Divide,
    Multiply,
    Equal,
    BitwiseAnd,
    BitwiseOr,
    BitwiseXor,
    GreaterThan,
    GreaterThanEqual,
    LessThan,
    LessThanEqual,
    LogicalAnd,
    LogicalOr,
    Modulus,
    NotEqual,
    ShiftLeft,
    ShiftRight,
    ValueAssign
};

class Operator : public Node
{
public:
    OperatorType Type_;


    Operator(NodePtr left, NodePtr right, OperatorType type) 
    {    
        branchList.insert(branchList.end(), {left, right});
        Type_ = type;
    }
    virtual ~Operator()
    {
        for (auto branch : branchList) {
            delete branch;
        }
    }


    virtual void print(std::ostream &dst, std::string indent) const override;
    
    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual std::string Returnid() const override; 

    void Add(std::ostream &dst, context &context, int destReg) const;

    void BitwiseAnd(std::ostream &dst, context &context, int destReg) const;

    void BitwiseOr(std::ostream &dst, context &context, int destReg) const;

    void BitwiseXor(std::ostream &dst, context &context, int destReg) const;

    void Divide(std::ostream &dst, context &context, int destReg) const;

    void Equal(std::ostream &dst, context &context, int destReg) const;

    void GreaterThan(std::ostream &dst, context &context, int destReg) const;

    void GreaterThanEqual(std::ostream &dst, context &context, int destReg) const;

    void LessThan(std::ostream &dst, context &context, int destReg) const;

    void LessThanEqual(std::ostream &dst, context &context, int destReg) const;

    void LogicalAnd(std::ostream &dst, context &context, int destReg) const;

    void LogicalOr(std::ostream &dst, context &context, int destReg) const;

    void Modulus(std::ostream &dst, context &context, int destReg) const;

    void Multiply(std::ostream &dst, context &context, int destReg) const;

    void NotEqual(std::ostream &dst, context &context, int destReg) const;

    void ShiftLeft(std::ostream &dst, context &context, int destReg) const;

    void ShiftRight(std::ostream &dst, context &context, int destReg) const;

    void Subtract(std::ostream &dst, context &context, int destReg) const;

    void ValueAssign(std::ostream &dst, context &context, int destReg) const;

};

#endif