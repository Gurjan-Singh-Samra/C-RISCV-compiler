#ifndef ast_Integer_hpp
#define ast_Integer_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class Int : public Node
{
private:
    int int_value;
public:
    Int(int val);
    Int();

    ~Int();

    void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual std::string Returnid() const override;

    virtual int getSize() const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;

    virtual int returnInt() const override;


};

#endif
