#include "ast_Unary.hpp"

Unary::Unary(NodePtr unary_operator, NodePtr cast_expression)
{
    branchList.insert(branchList.end(), {unary_operator, cast_expression});
}

Unary::~Unary()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

//Print
void Unary::print(std::ostream &dst, std::string indent) const
{
  branchList[0]->print(dst, indent+"  ");
  branchList[1]->print(dst, indent+"  ");
}

void Unary::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
    branchList[1]->EmitRISC(dst, context, destReg);
    branchList[0]->EmitRISC(dst, context, destReg);

    if(branchList[0]->returnOp() == "&"){
      dst << "addi " << context.reg(destReg) << ",s0," << context.get_var_location(branchList[1]->Returnid()) << std::endl;
    }
}

int Unary::getSize() const{
  return branchList[0]->getSize() + branchList[1]->getSize();
}

void Unary::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
  branchList[1]->createVariableMap(context);
  
}

std::string Unary::Returnid() const{
  return branchList[0]->Returnid() + branchList[1]->Returnid();
}


void Unary::isFunctionCall(context &context) const{
  //std::cerr << "UnaryFunctionCallReached" << std::endl;
  branchList[0]->isFunctionCall(context);
  branchList[1]->isFunctionCall(context);
}

void  Unary::isPointer(context &context) const{
  branchList[0]->isPointer(context);
  branchList[1]->isPointer(context);
}
 
UnaryPostOp::UnaryPostOp(NodePtr postfix_expression, std::string operation)
    :op(operation)
{
    branchList.insert(branchList.end(), {postfix_expression});
}

UnaryPostOp::~UnaryPostOp()
{
    for (auto branch : branchList) {
        delete branch;
    }
}

//Print
void UnaryPostOp::print(std::ostream &dst, std::string indent) const
{
    branchList[0]->print(dst, indent+"  ");
    if (op == "--"){
        dst << "DECREMENT";
    }
    else if(op == "++"){
        dst << "INCREMENT";
    }
}

void UnaryPostOp::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
    branchList[0]->EmitRISC(dst, context, destReg);
    std::string var_name = branchList[0]->Returnid();
    int variableallocate = context.get_var_location(var_name);
    dst << "addi " << context.reg(destReg) << ", " << context.reg(destReg) << ", -1" << std::endl;
    dst << "sw " << context.reg(destReg) << ", " << variableallocate << "(s0)" <<std::endl;
}

int UnaryPostOp::getSize() const{
  return branchList[0]->getSize();
}

void UnaryPostOp::isFunctionCall(context &context) const{
}

void UnaryPostOp::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
}

std::string UnaryPostOp::Returnid() const{
    return "";
}

void  UnaryPostOp::isPointer(context &context) const{}
 
UnaryOp::UnaryOp(std::string operation)
    :op(operation)
{}

UnaryOp::~UnaryOp()
{}

void UnaryOp::print(std::ostream &dst, std::string indent) const
{
    if (op == "-"){
        dst << "MINUS SIGN";
    }
    else if (op == "&"){
        dst << "&";
    }
    else if (op == "*"){
        dst << "*";
    }
}

void UnaryOp::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
    if (op == "-"){
        dst << "neg " << context.reg(destReg) << "," << context.reg(destReg) << std::endl;
    }
    else if (op == "*"){
        dst << "lw " << context.reg(destReg) << ", 0("  << context.reg(destReg) << ")" << std::endl;
    }
    

    std::cerr << "UnaryOpFunctionCallReached" << std::endl;
}

int UnaryOp::getSize() const{
  return 0;
}

void UnaryOp::isFunctionCall(context &context) const{
}

void UnaryOp::createVariableMap(context &context) const{}

void  UnaryOp::isPointer(context &context) const{}

std::string UnaryOp::returnOp() const{
    return op;
}

std::string UnaryOp::Returnid() const{
    return "";
}
 
SizeOf::SizeOf(NodePtr value)
{
    branchList.insert(branchList.end(), {value});
}

SizeOf::~SizeOf()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void SizeOf::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "SizeOf [" << std::endl;
  branchList[0]->print(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

void SizeOf::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
    int size = branchList[0]->getSize();

    if (size==0){ //reached an Id
      std::string var_name = branchList[0]->Returnid();
      std::string type = context.returnVarType(var_name);
      if(type == "int"){
        size = 4;
      }
      else if(type == "char"){
        size = 1;
      }
    }

    branchList[0]->EmitRISC(dst, context, destReg);
    dst << "li " << context.reg(destReg) << "," << size << std::endl;
}

int SizeOf::getSize() const{
  return branchList[0]->getSize();
}