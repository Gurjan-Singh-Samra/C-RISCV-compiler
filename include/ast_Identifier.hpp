#ifndef ast_Identifier_hpp
#define ast_Identifier_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class Identifier : public Node
{
public:
    Identifier(std::string IDENTIFIER);

    std::string id;

    virtual ~Identifier();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual std::string Returnid() const override; 

    virtual int getSize() const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;

};

#endif