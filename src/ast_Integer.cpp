#include "ast_Integer.hpp"

// Constructor
Int::Int(int val)
  : int_value(val)
{}

Int::Int() // Default initializer
  : Int(0)
{}


Int::~Int()
{}

// Visualising
void Int::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "Integer : " << int_value << std::endl;
}

void Int::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  dst << "li "<< context.reg(destReg) << "," << int_value << std::endl;
}

std::string Int::Returnid() const{ //hacky solution
  return "int";
}

int Int::getSize() const{
  return 0;
}

void Int::isFunctionCall(context &context) const{
  std::cerr << "IntFunctionCall" << std::endl;
}

void Int::isPointer(context &context) const{

}

int Int::returnInt() const{
  return int_value;
}
