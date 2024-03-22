#include "ast_Functions.hpp"
 
Function_Declarator::Function_Declarator(NodePtr direct_declarator, NodePtr parameter_type_list)
{
    branchList.insert(branchList.end(), {direct_declarator, parameter_type_list});
}

Function_Declarator::~Function_Declarator()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void Function_Declarator::print(std::ostream &dst, std::string indent) const
{
    branchList[0]->print(dst, indent+"  ");
    branchList[1]->print(dst, indent+"  ");
}

void Function_Declarator::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  branchList[0]->EmitRISC(dst, context ,destReg);
  branchList[1]->EmitRISC(dst, context ,destReg);
}

int Function_Declarator::getSize() const{
   return branchList[0]->getSize() + branchList[1]->getSize();
}

NodePtr Function_Declarator::returnBranch(int index) const{
  return branchList[index];
}

std::string Function_Declarator::Returnid() const{
  return branchList[0]->Returnid();
}

void Function_Declarator::createParameterMap(context &context) const{
  branchList[1]->createParameterMap(context);
}

void Function_Declarator::isPointer(context &context) const{
  branchList[0]->isPointer(context);
  branchList[1]->isPointer(context);
}
 
Function_Definition::Function_Definition(NodePtr declaration_specifier, NodePtr declarator, NodePtr compound_statement)
{
    branchList.insert(branchList.end(), {declaration_specifier, declarator, compound_statement});
}

Function_Definition::~Function_Definition()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

//Print
void Function_Definition::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "Function Definition [" << std::endl;
  branchList[0]->print(dst, indent+"  ");
  branchList[1]->print(dst, indent+"  ");
  branchList[2]->print(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

NodePtr Function_Definition::returnBranch(int index) const{
  return branchList[index];
}

void Function_Definition::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  int stacksize = context.rounding(getSize()); 
  
  std::string endFunctionLabel = context.createLabel();
  std::string function_id = branchList[1]->Returnid();
  context.set_function_type(function_id, branchList[0]->getType());
  std::string function_type = context.returnFunctionType(function_id);

  branchList[1]->isPointer(context);
  branchList[2]->isPointer(context);

  branchList[1]->createParameterMap(context); 
  context.addToFunctionParameters(function_id); 
  context.clearParameterVectors(); 

  
  branchList[2]->createVariableMap(context);
  context.addToFunctionVariables(function_id);
  context.clearVariableVectors();

  //check for function calls:
  int functionCall = 0;
  branchList[2]->isFunctionCall(context);
  functionCall = context.ReturnFunctionCallValue();
  //dst << functionCall << std::endl;

  
  dst << ".globl "<< function_id << std::endl; 
  dst << function_id << ":" << std::endl;
  
  dst << "addi sp,sp,-" << stacksize << std::endl;

  if(functionCall == 1){
    dst << "sw ra," << stacksize - 4 <<"(sp)" << std::endl;
  }
  else{
    functionCall = 0;
  }
  
  if (function_type == "double"){
    dst << "sw s0,"<< stacksize - (functionCall*4) - 8 <<"(sp)" << std::endl;
  }
  else if (function_type == "float"){
    dst << "sw s0,"<< stacksize - (functionCall*4)- 8 <<"(sp)" << std::endl;
  }
  else{
    dst << "sw s0,"<< stacksize - (functionCall*4) - 4 <<"(sp)" << std::endl;
  }

  
  dst << "addi s0,sp," << stacksize << std::endl; 
  
  int newReg = context.allocateRegister();

  branchList[1]->EmitRISC(dst, context ,newReg);
  branchList[2]->EmitRISC(dst, context ,newReg);

  dst << "." << endFunctionLabel << ":" << std::endl;

  if(functionCall == 1){
    dst << "lw ra," << stacksize - 4 <<"(sp)" << std::endl;
  }

  if (function_type == "double"){
    dst << "fmv.d fa0, f" << context.reg(newReg) << std::endl;
    dst << "lw s0,"<< stacksize - (functionCall*4) - 8 <<"(sp)" << std::endl;
  }
  else if (function_type == "float"){
    dst << "fmv.s fa0, f" << context.reg(newReg) << std::endl;
    dst << "lw s0,"<< stacksize - (functionCall*4) - 8 <<"(sp)" << std::endl;
  }
  else{
    dst << "mv a0," << context.reg(newReg) << std::endl;
    dst << "lw s0,"<< stacksize - (functionCall*4) - 4 <<"(sp)" << std::endl;
  }
  
  dst << "addi sp,sp," << stacksize << std::endl;
  dst << "jr ra" << std::endl;
  
}

int Function_Definition::getSize() const
{
  return branchList[1]->getSize() + branchList[2]->getSize();
}
 
Function_Call_With_Arguments::Function_Call_With_Arguments(NodePtr postfix_expression, NodePtr argument_expression_list)
{
    branchList.insert(branchList.end(), {postfix_expression, argument_expression_list});
}

Function_Call_With_Arguments::~Function_Call_With_Arguments()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void Function_Call_With_Arguments::print(std::ostream &dst, std::string indent) const
{
    dst << indent << "Function Call With Arguments [" << std::endl;
    dst << indent << "Function Name = ";
    branchList[0]->print(dst, indent+"  ");
    dst << indent << "Arguments = ";
    branchList[1]->print(dst, indent+"  ");
    dst << indent << "]" << std::endl;
}

void Function_Call_With_Arguments::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  //branchList[0]->EmitRISC(dst, context ,destReg);
  branchList[1]->EmitRISC(dst, context ,destReg);
  dst << "call " << branchList[0]->Returnid() << std::endl;
  dst << "mv " <<  context.reg(destReg) << ", a0" << std::endl;
}

int Function_Call_With_Arguments::getSize() const{
   return branchList[0]->getSize() + branchList[1]->getSize();
}

void Function_Call_With_Arguments::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
  branchList[1]->createVariableMap(context);
}

void Function_Call_With_Arguments::isFunctionCall(context &context) const{
  std::cerr << "REACHED Function_Call_With_Arguments" << std::endl; 
  context.FunctionCallOccurs();
}

void Function_Call_With_Arguments::isPointer(context &context) const{

}
 
Function_Call_With_NoArguments::Function_Call_With_NoArguments(NodePtr postfix_expression)
{
    branchList.insert(branchList.end(), {postfix_expression});
}

Function_Call_With_NoArguments::~Function_Call_With_NoArguments()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void Function_Call_With_NoArguments::print(std::ostream &dst, std::string indent) const
{
    dst << indent << "Function Call With NoArguments [" << std::endl;
    dst << indent << "Function Name = ";
    branchList[0]->print(dst, indent+"  ");
    dst << indent << "]" << std::endl;
}

void Function_Call_With_NoArguments::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  dst << "call " << branchList[0]->Returnid() << std::endl;
  dst << "mv " <<  context.reg(destReg) << ", a0" << std::endl;
}

int Function_Call_With_NoArguments::getSize() const{
   return branchList[0]->getSize();
}

void Function_Call_With_NoArguments::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
}

void Function_Call_With_NoArguments::isFunctionCall(context &context) const{
  std::cerr << "REACHED Function_Call_With_NoArguments" << std::endl; 
  context.FunctionCallOccurs();
}

