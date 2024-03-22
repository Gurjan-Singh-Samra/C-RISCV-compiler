#include "ast_ParamDeclaration.hpp"


Param_Declarator::Param_Declarator(NodePtr declaration_specifier, NodePtr declarator)
{
    branchList.insert(branchList.end(), {declaration_specifier, declarator});
}

Param_Declarator::~Param_Declarator()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void Param_Declarator::print(std::ostream &dst, std::string indent) const
{
    branchList[0]->print(dst, indent);
    branchList[1]->print(dst, indent);
}

void Param_Declarator::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  std::string var_id = branchList[1]->Returnid();
  std::string var_type = branchList[0]->getType();

  //context.addParameterName(var_id);
  //context.addParameterType(var_type);

  int var_addr = context.implement_var_binding(var_id, var_type);
  int param_reg = context.parameterAllocateRegister();

  branchList[0]->EmitRISC(dst, context ,destReg);
  branchList[1]->EmitRISC(dst, context ,destReg);


  if (var_type == "float"){
    dst << "fsw f" << context.reg(param_reg) << ", " << var_addr << "(s0)" <<std::endl;
  }
  else if (var_type == "double"){
    dst << "fsd f" << context.reg(param_reg) << ", " << var_addr << "(s0)" <<std::endl;
  }
  else{
    dst << "sw " << context.reg(param_reg) << ", " << var_addr << "(s0)" <<std::endl;
  }

}

int Param_Declarator::getSize() const{
  return branchList[0]->getSize() + branchList[1]->getSize();
}

void Param_Declarator::createParameterMap(context& context) const{
    std::string var_id = branchList[1]->Returnid();
    std::string var_type = branchList[0]->getType();

    context.addParameterName(var_id);
    context.addParameterType(var_type);
}

void Param_Declarator::isPointer(context &context) const{
  branchList[0]->isPointer(context);
  branchList[1]->isPointer(context);
}

Param_List::Param_List(NodePtr parameter_list)
{
    branchList.insert(branchList.end(), {parameter_list});
}

Param_List::~Param_List()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void Param_List::print(std::ostream &dst, std::string indent) const
{
    dst << indent << "Function Parameters [" << std::endl;
    branchList[0]->print(dst, indent+"  ");
    dst << indent << "]" << std::endl;
}

void Param_List::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  branchList[0]->EmitRISC(dst, context ,destReg);
}

int Param_List::getSize() const{
  return branchList[0]->getSize();
}

void Param_List::createParameterMap(context &context) const{
  branchList[0]->createParameterMap(context);
}

void Param_List::isPointer(context &context) const{
  branchList[0]->isPointer(context);
}

Param_List_Declarator::Param_List_Declarator(NodePtr parameter_list, NodePtr parameter_declaration)
{
    branchList.insert(branchList.end(), {parameter_list, parameter_declaration});
}

Param_List_Declarator::~Param_List_Declarator()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void Param_List_Declarator::print(std::ostream &dst, std::string indent) const
{
    branchList[0]->print(dst, indent);
    branchList[1]->print(dst, indent);
}

void Param_List_Declarator::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  branchList[0]->EmitRISC(dst, context ,destReg);
  branchList[1]->EmitRISC(dst, context ,destReg);
}

int Param_List_Declarator::getSize() const{
  return branchList[0]->getSize() + branchList[1]->getSize();
}

void Param_List_Declarator::createParameterMap(context &context) const{
  branchList[0]->createParameterMap(context);
  branchList[1]->createParameterMap(context);
}

void Param_List_Declarator::isPointer(context &context) const{
  branchList[0]->isPointer(context);
  branchList[1]->isPointer(context);
}
