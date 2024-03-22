#include "ast_VariableDeclarator.hpp"

VariableDeclarator::VariableDeclarator(NodePtr declaration)
{
    branchList.insert(branchList.end(), {declaration});
}
VariableDeclarator::~VariableDeclarator()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void VariableDeclarator::print(std::ostream &dst, std::string indent) const
{
    dst << indent << "Variable Declaration [" << std::endl;
    branchList[0]->print(dst, indent);
    dst << indent << "]" << std::endl;
}

void VariableDeclarator::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  branchList[0]->EmitRISC(dst, context ,destReg);
  std::string var_name = branchList[0]->Returnid();
  std::string var_type = context.returnVarType(var_name);
  int variableallocate = context.implement_var_binding(var_name, var_type);
}

int VariableDeclarator::getSize() const{
  return branchList[0]->getSize();
}


std::string VariableDeclarator::Returnid() const{
  return branchList[0]->Returnid();
}


void VariableDeclarator::isPointer(context &context) const{
  branchList[0]->isPointer(context);
}
