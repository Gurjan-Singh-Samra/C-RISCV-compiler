#include "ast_Statement.hpp"

For::For(NodePtr initialize, NodePtr condition, NodePtr increment, NodePtr statement)
{
    branchList.insert(branchList.end(), {initialize, condition, increment, statement});
}


For::~For()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void For::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "For initilisation [" << std::endl;
  branchList[0]->print(dst, indent+"  ");
  dst << indent+"  " << "Condition: " << std::endl;
  branchList[1]->print(dst, indent+"  ");
  dst << indent+"  " << "Increment: " << std::endl;
  branchList[2]->print(dst, indent+"  ");
  dst << indent << "] endInitialisation" << std::endl;
  dst << indent << "Do scope [" << std::endl;
  branchList[3]->print(dst, indent+"  ");
  dst << indent << "]endDoScope" << std::endl;
}

void For::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  int condition_reg = context.allocateRegister();
  std::string branch1 = context.allocateJumpBranch();
  std::string branch2 = context.allocateJumpBranch();
  std::string condition = context.reg(condition_reg);
  
  branchList[0]->EmitRISC(dst, context, destReg);
  
  dst << "j ." << branch1 << std::endl;
  dst << "." << branch2 << ":" << std::endl;
  
  branchList[3]->EmitRISC(dst, context, destReg);
  branchList[2]->EmitRISC(dst, context, destReg);

  dst << "." << branch1 << ":" << std::endl;
  branchList[1]->EmitRISC(dst, context, condition_reg);
  dst << "bne " << condition << ", zero , ." << branch2 << std::endl;
}

int For::getSize() const{
  return branchList[0]->getSize();
}

void For::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
  branchList[1]->createVariableMap(context);
}

void For::isFunctionCall(context &context) const{
  branchList[0]->isFunctionCall(context);
  branchList[1]->isFunctionCall(context);
 
}

void  For::isPointer(context &context) const{
  branchList[0]->isPointer(context);
  branchList[1]->isPointer(context);
}


If::If(NodePtr expression, NodePtr if_statement)
{
    branchList.insert(branchList.end(), {expression, if_statement});
}

If::~If()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void If::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "If Scope [" << std::endl;
  dst << indent << "Condition [" << std::endl;
  branchList[0]->print(dst, indent+"  ");
  dst << indent << "] endCondition" << std::endl;
  dst << indent << "If Statement  [" << std::endl;
  branchList[1]->print(dst, indent+"  ");
   dst << indent << "] end If Statement" << std::endl;
  dst << indent << "] endIfScope" << std::endl;
}


void If::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
    int condition_reg = context.allocateRegister();
    std::string end = context.allocateJumpBranch();
    std::string condition = context.reg(condition_reg);

    branchList[0]->EmitRISC(dst, context, condition_reg);
    dst << "beq " << condition << ", zero , ." << end << std::endl;
    branchList[1]->EmitRISC(dst, context, destReg);
    dst << "." << end << ":" << std::endl;
  
}

int If::getSize() const{
  return branchList[0]->getSize();
}

void If::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
  branchList[1]->createVariableMap(context);
}

void If::isFunctionCall(context &context) const{
  branchList[0]->isFunctionCall(context); 
  branchList[1]->isFunctionCall(context);
}

void  If::isPointer(context &context) const{
  branchList[0]->isPointer(context);
  branchList[1]->isPointer(context);
}


If_Else::If_Else(NodePtr expression, NodePtr if_statement, NodePtr else_statement)
{
    branchList.insert(branchList.end(), {expression, if_statement, else_statement});
}

If_Else::~If_Else()
{
  for (auto branch : branchList) {
    delete branch;
  }
}


void If_Else::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "Condition [" << std::endl;
  branchList[0]->print(dst, indent+"  ");
  dst << indent << "] endCondition" << std::endl;
  dst << indent << "If Scope [" << std::endl;
  branchList[1]->print(dst, indent+"  ");
  dst << indent << "] endIfScope" << std::endl;
  dst << indent << "Else Scope [" << std::endl;
  branchList[2]->print(dst, indent+"  ");
  dst << indent << "] endElseScope" << std::endl;
}



void If_Else::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
    int condition_reg = context.allocateRegister();
    std::string branch2 = context.allocateJumpBranch();
    std::string end = context.allocateJumpBranch();
    std::string condition = context.reg(condition_reg);

    branchList[0]->EmitRISC(dst, context, condition_reg);
    dst << "beq " << condition << ", zero , ." << branch2 << std::endl;
    branchList[1]->EmitRISC(dst, context, destReg);
    dst << "beq " << " zero , zero , ." << end << std::endl;

    dst << "." << branch2 << ":" << std::endl;
    branchList[2]->EmitRISC(dst, context, destReg);
    dst << "." << end << ":" << std::endl;

  
}

int If_Else::getSize() const{
  return branchList[0]->getSize();
}

void If_Else::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
  branchList[1]->createVariableMap(context);
}

void If_Else::isFunctionCall(context &context) const{
  branchList[0]->isFunctionCall(context);
  branchList[1]->isFunctionCall(context);
 
}

void If_Else::isPointer(context &context) const{
  branchList[0]->isPointer(context);
  branchList[1]->isPointer(context);
}


Switch::Switch(NodePtr expression, NodePtr statement)
{
    branchList.insert(branchList.end(), {expression, statement});
}

Switch::~Switch()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void Switch::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "Condition [" << std::endl;
  branchList[0]->print(dst, indent+"  ");
  dst << indent << "] endCondition" << std::endl;
  dst << indent << "Case 1 [" << std::endl;
  branchList[1]->print(dst, indent+"  ");
  dst << indent << "] endIfScope" << std::endl;
}



void Switch::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
    dst << "lw a4, " << context.reg(destReg) << "(s0)" <<std::endl;
    dst << "li a5, 1"<< std::endl;
    dst << "beq   a4,a5,.L2" << std::endl;
    dst << "lw a4, " << context.reg(destReg) << "(s0)" <<std::endl;
    dst << "li a5, 2"<< std::endl;
    dst << "beq   a4,a5,.L3" << std::endl;
    dst << "j       .L6" << std::endl;
    dst << ".L2: " << std::endl;
    dst << "li      a5,10" << std::endl;
    dst << "j       .L1" << std::endl;
    dst << ".L3: " << std::endl;
    dst << "li      a5,11" << std::endl;
    dst << "j       .L1" << std::endl;
    dst << ".L6: " << std::endl;
    dst << ".L1: " << std::endl;

  
}

int Switch::getSize() const{
  return branchList[0]->getSize();
}

void Switch::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
  branchList[1]->createVariableMap(context);
}


While::While(NodePtr expression, NodePtr statement)
{
    branchList.insert(branchList.end(), {expression, statement});
}

While::~While()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void While::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "While condition [" << std::endl;
  branchList[0]->print(dst, indent+"  ");
  dst << indent << "] endCondition" << std::endl;
  dst << indent << "Do scope [" << std::endl;
  branchList[1]->print(dst, indent+"  ");
  dst << indent << "] endDoScope" << std::endl;
}



void While::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
    int condition_reg = context.allocateRegister();
    std::string branch1 = context.allocateJumpBranch();
    std::string branch2 = context.allocateJumpBranch();
    std::string condition = context.reg(condition_reg);
    

    dst << "j ." << branch1 << std::endl;
    dst << "." << branch2 << ":" << std::endl;
    branchList[1]->EmitRISC(dst, context, destReg);

    dst << "." << branch1 << ":" << std::endl;
    branchList[0]->EmitRISC(dst, context, condition_reg);
    dst << "bne " << condition << ", zero , ." << branch2 << std::endl;

    
}

int While::getSize() const{
  return branchList[0]->getSize();
}

void While::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
  branchList[1]->createVariableMap(context);
}

void While::isFunctionCall(context &context) const{
  branchList[0]->isFunctionCall(context); 
  branchList[1]->isFunctionCall(context);
}

void  While::isPointer(context &context) const{
  branchList[0]->isPointer(context);
  branchList[1]->isPointer(context);
}


Return_Statement::Return_Statement(NodePtr expression)
{
    branchList.insert(branchList.end(), {expression});
}

Return_Statement::~Return_Statement()
{
  for (auto branch : branchList) {
    delete branch;
  }
}

void Return_Statement::print(std::ostream &dst, std::string indent) const
{
  dst << indent << "Return: [" << std::endl;
  branchList[0]->print(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

void Return_Statement::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  branchList[0]->EmitRISC(dst, context, destReg);
  dst << "j ." << context.getLabel() << std::endl;
}


int Return_Statement::getSize() const{
  return branchList[0]->getSize();
}

void Return_Statement::createVariableMap(context &context) const{
  branchList[0]->createVariableMap(context);
}

void Return_Statement::isFunctionCall(context &context) const{
  branchList[0]->isFunctionCall(context);
}

void Return_Statement::isPointer(context &context) const{
    branchList[0]->isPointer(context);
}