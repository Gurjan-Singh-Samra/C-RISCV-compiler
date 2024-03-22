#include "ast_Array.hpp"

Array::Array(NodePtr id , NodePtr index)
{
  id_ = id;
  index_ = index;
}
Array::~Array()
{
  delete branchList[0];
  delete branchList[1];
}

void Array::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "Array [" << std::endl;
  branchList[0]->print(dst, indent+"  ");
  branchList[1]->print(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

void Array::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
}


int Array::getSize() const{
  return branchList[0]->getSize() + branchList[1]->getSize();
}

void Array::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
  branchList[1]->createVariableMap(context);
}

