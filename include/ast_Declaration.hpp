#ifndef ast_Declaration_hpp
#define ast_Declaration_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class MultiDeclaration : public Node
{
public:
    MultiDeclaration(NodePtr translation_unit, NodePtr external_declaration);

    virtual ~MultiDeclaration();

    virtual void print(std::ostream &dst, std::string indent) const override;

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void createVariableMap(context &context) const override;

    virtual void isFunctionCall(context &context) const override;

    virtual void isPointer(context &context) const override;

};

#endif
