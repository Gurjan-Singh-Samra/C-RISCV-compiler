#ifndef ast_NameDeclarator_hpp
#define ast_NameDeclarator_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class Name_Declarator : public Node
{
public:
    Name_Declarator(std::string IDENTIFIER);

    std::string id;

    virtual ~Name_Declarator();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual std::string Returnid() const override;

    virtual void createVariableMap(context &context) const override;


};

#endif
