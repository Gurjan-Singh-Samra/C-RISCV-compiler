#ifndef ast_EmptyNode_hpp
#define ast_EmptyNode_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class EmptyNode : public Node
{
public:
    EmptyNode();

    virtual ~EmptyNode();

    virtual void print(std::ostream &dst, std::string indent) const override;
    
    void EmitRISC(std::ostream &dst, context &context, int destReg) const override;

    virtual int getSize() const override;

    virtual void isFunctionCall(context &context) const override;
    
    virtual void isPointer(context &context) const override;

};

#endif