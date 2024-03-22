#include "ast_Declaration.hpp"


MultiDeclaration::MultiDeclaration(NodePtr MultiDeclaration_list, NodePtr MultiDeclaration)
{
    branchList.insert(branchList.end(), {MultiDeclaration_list, MultiDeclaration});
}

MultiDeclaration::~MultiDeclaration()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void MultiDeclaration::print(std::ostream &dst, std::string indent) const
{
    branchList[0]->print(dst, indent);
    branchList[1]->print(dst, indent);
}

void MultiDeclaration::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  branchList[0]->EmitRISC(dst, context ,destReg);
  branchList[1]->EmitRISC(dst, context ,destReg);
}

int MultiDeclaration::getSize() const{
  return branchList[0]->getSize() + branchList[1]->getSize();
}

void MultiDeclaration::createVariableMap(context &context) const{
    branchList[0]->createVariableMap(context);
    branchList[1]->createVariableMap(context);
}

void MultiDeclaration::isFunctionCall(context &context) const{
  branchList[0]->isFunctionCall(context);
  branchList[1]->isFunctionCall(context);

}

void  MultiDeclaration::isPointer(context &context) const{
  branchList[0]->isPointer(context);
  branchList[1]->isPointer(context);
}
