#include "ast_ArgDeclaration.hpp"


Arg_Declarator::Arg_Declarator(NodePtr assignment_expression)
{
    branchList.insert(branchList.end(), {assignment_expression});
}

Arg_Declarator::~Arg_Declarator()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void Arg_Declarator::print(std::ostream &dst, std::string indent) const
{
    branchList[0]->print(dst, indent);
}

void Arg_Declarator::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  branchList[0]->EmitRISC(dst, context , 10);
}

int Arg_Declarator::getSize() const
{
  return branchList[0]->getSize();
}

void Arg_Declarator::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
}

int Arg_Declarator::GetArgLocation() const{
  return 10;
}

std::string Arg_Declarator::Returnid() const{
  return branchList[0]->Returnid();
}

Arg_List_Declarator::Arg_List_Declarator(NodePtr argument_expression_list, NodePtr assignment_expression)
{
    branchList.insert(branchList.end(), {argument_expression_list, assignment_expression});
}

Arg_List_Declarator::~Arg_List_Declarator()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void Arg_List_Declarator::print(std::ostream &dst, std::string indent) const
{
    branchList[0]->print(dst, indent);
    branchList[1]->print(dst, indent);
}

void Arg_List_Declarator::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  branchList[0]->EmitRISC(dst, context ,destReg);
  branchList[1]->EmitRISC(dst, context , GetArgLocation());
}

int Arg_List_Declarator::getSize() const
{
  return branchList[0]->getSize() + branchList[1]->getSize();
}

void Arg_List_Declarator::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
  branchList[1]->createVariableMap(context);
}

int Arg_List_Declarator::GetArgLocation() const{
  return branchList[0]->GetArgLocation()+1;
}

std::string Arg_List_Declarator::Returnid() const{
  return branchList[0]->Returnid() + branchList[1]->Returnid();
}
