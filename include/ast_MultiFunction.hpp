#ifndef ast_MultiFunction_hpp
#define ast_MultiFunction_hpp
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <memory>
#include "ast_Node.hpp"

class MultiFunction : public Node
{
public:
    MultiFunction(NodePtr translation_unit, NodePtr external_declaration)
    {
        branchList.insert(branchList.end(), {translation_unit, external_declaration});
    }

    virtual ~MultiFunction()
    {
        for (auto branch : branchList) {
        delete branch;
  }
    }

    virtual void print(std::ostream &dst, std::string indent) const override {

    }

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override{
        branchList[0]->EmitRISC(dst, context ,destReg);
        branchList[1]->EmitRISC(dst, context ,destReg);
    }

    virtual int getSize() const override
    {
        return branchList[0]->getSize() + branchList[1]->getSize();
    }

    virtual void isFunctionCall(context &context) const override
    {
        branchList[0]->isFunctionCall(context);
        branchList[1]->isFunctionCall(context);
    }

    virtual void isPointer(context &context) const override{
        branchList[0]->isPointer(context);
        branchList[1]->isPointer(context);
    }

};

#endif
