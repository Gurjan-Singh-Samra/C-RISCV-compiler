#include "ast_Identifier.hpp"


Identifier::Identifier(std::string IDENTIFIER)
  :id(IDENTIFIER)
{}

Identifier::~Identifier()
{}

//Print
void Identifier::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "IDENTIFIER " << id << std::endl;
}

//Codegen
void Identifier::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  std::string type = context.returnVarType(id);
  if (type == "double"){
    dst << "fld f" << context.reg(destReg) <<  ", " << context.get_var_location(id) << "(s0)" <<std::endl;
  }
  else if (type == "float"){
    dst << "flw f" << context.reg(destReg) <<  ", " << context.get_var_location(id) << "(s0)" <<std::endl;
  }
  else{
    dst << "lw " << context.reg(destReg) <<  ", " << context.get_var_location(id) << "(s0)" <<std::endl;
    //dst << id << std::endl;
  }

}

std::string Identifier::Returnid() const{
  return id;
}

int Identifier::getSize() const{
  return 0;
}

void Identifier::isFunctionCall(context &context) const{
  std::cerr << "IdentifierFunctionCall" << std::endl;
}

void Identifier::isPointer(context &context) const{

}



