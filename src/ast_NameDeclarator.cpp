#include "ast_NameDeclarator.hpp"


Name_Declarator::Name_Declarator(std::string IDENTIFIER)
  :id(IDENTIFIER)
{}

Name_Declarator::~Name_Declarator()
{
}

//Print
void Name_Declarator::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "IDENTIFIER " << id << std::endl;
}

void Name_Declarator::EmitRISC(std::ostream &dst, context &context, int destReg) const
{//leaf node
}

std::string Name_Declarator::Returnid() const{
  return id;
}

int Name_Declarator::getSize() const{
  return 0;
}

void Name_Declarator::createVariableMap(context &context) const{
}
