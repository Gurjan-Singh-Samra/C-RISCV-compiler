#include "ast_Multiline.hpp"


Multiline::Multiline(NodePtr declaration_list, NodePtr statement_list)
{
    branchList.insert(branchList.end(), {declaration_list, statement_list});
}

Multiline::~Multiline()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void Multiline::print(std::ostream &dst, std::string indent) const
{
    dst << indent << "Compound Statements [" << std::endl;
    branchList[0]->print(dst, indent+"  ");
    branchList[1]->print(dst, indent+"  ");
    dst << indent << "]" << std::endl;
}

void Multiline::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  branchList[0]->EmitRISC(dst, context ,destReg);
  branchList[1]->EmitRISC(dst, context ,destReg);
}

int Multiline::getSize() const{
  return branchList[0]->getSize() + branchList[1]->getSize();
}

void Multiline::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
  branchList[1]->createVariableMap(context);
}

void Multiline::isFunctionCall(context &context) const{
  std::cerr << "BFunctionCall" << std::endl;
  branchList[0]->isFunctionCall(context);
  branchList[1]->isFunctionCall(context);

}

void Multiline::isPointer(context &context) const{
  branchList[0]->isPointer(context);
  branchList[1]->isPointer(context);
}
