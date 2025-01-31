#include "ast_VariableAssign.hpp"


VariableAssign::VariableAssign(NodePtr declaration, NodePtr initializer)
{
    branchList.insert(branchList.end(), {declaration, initializer});
}

VariableAssign::~VariableAssign()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void VariableAssign::print(std::ostream &dst, std::string indent) const
{
    dst << indent << "Variable Assign [" << std::endl;
    branchList[0]->print(dst, indent);
    branchList[1]->print(dst, indent);
    dst << indent << "]" << std::endl;
}

void VariableAssign::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  branchList[0]->EmitRISC(dst, context ,destReg);
  branchList[1]->EmitRISC(dst, context ,destReg);
  std::string var_name = branchList[0]->Returnid();
  std::string var_type = context.returnVarType(var_name);
  int variableallocate = context.implement_var_binding(var_name, var_type);
  dst << "sw " << context.reg(destReg) <<  ", " << variableallocate << "(s0)" <<std::endl;
}

int VariableAssign::getSize() const{
  return branchList[0]->getSize() + branchList[1]->getSize();
}

std::string VariableAssign::Returnid() const{
  return branchList[0]->Returnid();
}


void VariableAssign::isPointer(context &context) const{
  branchList[0]->isPointer(context);
}
