#ifndef ast_Types_hpp
#define ast_Types_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class Types : public Node
{
public:
    Types(std::string dataType);

    virtual ~Types();

    virtual void print(std::ostream &dst, std::string indent) const override;

    std::string type;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual std::string getType() const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;

};

#endif