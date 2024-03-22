#include "ast_Declarator.hpp"

MultiDec::MultiDec(NodePtr declaration_specifiers, NodePtr init_MultiDec_list)
{
    branchList.insert(branchList.end(), {declaration_specifiers, init_MultiDec_list});
}

MultiDec::~MultiDec()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void MultiDec::print(std::ostream &dst, std::string indent) const
{
    branchList[0]->print(dst, indent);
    branchList[1]->print(dst, indent);
}

void MultiDec::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  branchList[0]->EmitRISC(dst, context ,destReg);
  branchList[1]->EmitRISC(dst, context ,destReg);
}

int MultiDec::getSize() const{
  return branchList[0]->getSize() + branchList[1]->getSize();
}

void MultiDec::createVariableMap(context &context) const{
    std::string var_type = branchList[0]->getType();
    std::string var_id = branchList[1]->Returnid();

    context.addVariableName(var_id);
    context.addVariableType(var_type);
}

void MultiDec::isFunctionCall(context &context) const{
  branchList[0]->isFunctionCall(context);
  branchList[1]->isFunctionCall(context);
}

void MultiDec::isPointer(context &context) const{
  branchList[0]->isPointer(context);
  branchList[1]->isPointer(context);
}
