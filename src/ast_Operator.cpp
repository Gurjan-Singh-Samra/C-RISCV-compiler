#include "ast_Operator.hpp"

void Operator::print(std::ostream &dst, std::string indent) const
{
}

void Operator::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
    switch (Type_)
    {
    case OperatorType::Add:
        Add(dst, context, destReg);
        break;
    case OperatorType::Subtract:
        Subtract(dst, context, destReg);   
        break;  
    case OperatorType::Divide:
        Divide(dst, context, destReg);
        break; 
    case OperatorType::Multiply:
        Multiply(dst, context, destReg);
        break; 
    case OperatorType::Equal:
        Equal(dst, context, destReg);
        break; 
    case OperatorType::BitwiseAnd:
        BitwiseAnd(dst, context, destReg);
        break; 
    case OperatorType::BitwiseOr:
        BitwiseOr(dst, context, destReg);
        break; 
    case OperatorType::BitwiseXor:
        BitwiseXor(dst, context, destReg);
        break; 
    case OperatorType::GreaterThan:
        GreaterThan(dst, context, destReg);
        break; 
    case OperatorType::GreaterThanEqual:
        GreaterThanEqual(dst, context, destReg);
        break; 
    case OperatorType::LessThan:
        LessThan(dst, context, destReg);
        break; 
    case OperatorType::LessThanEqual:
        LessThanEqual(dst, context, destReg);
        break; 
    case OperatorType::LogicalAnd:
        LogicalAnd(dst, context, destReg);
        break; 
    case OperatorType::LogicalOr:
        LogicalOr(dst, context, destReg);
        break; 
    case OperatorType::Modulus:
        Modulus(dst, context, destReg);
        break; 
    case OperatorType::NotEqual:
        NotEqual(dst, context, destReg);
        break; 
    case OperatorType::ShiftLeft:
        ShiftLeft(dst, context, destReg);
        break; 
    case OperatorType::ShiftRight:
        ShiftRight(dst, context, destReg);
        break; 
    case OperatorType::ValueAssign:
        ValueAssign(dst, context, destReg);
        break; 
    default:
        ValueAssign(dst, context, destReg);
        break; 
    }
}

int Operator::getSize() const
{
    return branchList[0]->getSize() + branchList[1]->getSize();
}

void Operator::createVariableMap(context &context) const
{
    branchList[0]->createVariableMap(context);
    branchList[1]->createVariableMap(context);
}

std::string Operator::Returnid() const
{
    return branchList[0]->Returnid();
}

void Operator::Add(std::ostream &dst, context &context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    std::string id = branchList[0]->Returnid();
    std::string type;

  
    if (id == "int") {
      type = "int";
    }
    else{
      type = context.returnVarType(id); 
    } 

    int multiplier;
    if (type == "int"){
      multiplier = 4;
    }
    else if (type == "float"){
      multiplier = 8;
    }
    else if(type == "double"){
      multiplier = 8;
    }

    if(context.pointer_exists(id) == 1){
      int val = branchList[1]->returnInt();
      dst << "li "<< context.reg(right_reg) << "," << val*multiplier << std::endl;
    }

    //std::cerr << type << std::endl; //check if it works

    if (type == "int"){
      dst << "add " << context.reg(destReg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;
    }
    else if (type == "double"){
      dst << "fadd.d f" << context.reg(destReg) << ", f" << context.reg(left_reg) << ", f" << context.reg(right_reg) << std::endl;
    }
    else if (type == "float"){
      dst << "fadd.s f" << context.reg(destReg) << ", f" << context.reg(left_reg) << ", f" << context.reg(right_reg) << std::endl;
    }

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::BitwiseAnd(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    dst << "and " << context.reg(destReg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::BitwiseOr(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    dst << "or " << context.reg(destReg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::BitwiseXor(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    dst << "xor " << context.reg(destReg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::Divide(std::ostream & dst, context & context, int destReg) const
{
     int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);
    std::string id = branchList[0]->Returnid();
    std::string type;
    
    if (id == "int") { //if left branch is a constant int instead of a variable int
      type = "int";
    }
    else{
      type = context.returnVarType(id); 
    } 

    //std::cerr << type << std::endl; //check if it works

    if (type == "int"){
       dst << "div " << context.reg(destReg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;
    }
    else if (type == "double"){
      dst << "fdiv.d f" << context.reg(destReg) << ", f" << context.reg(left_reg) << ", f" << context.reg(right_reg) << std::endl;
    }
    else if (type == "float"){
      dst << "fdiv.s f" << context.reg(destReg) << ", f" << context.reg(left_reg) << ", f" << context.reg(right_reg) << std::endl;
    }

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::Equal(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

       dst << "sub " << context.reg(right_reg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;
       dst << "seqz " << context.reg(right_reg) << ", " << context.reg(right_reg) << std::endl;
       dst << "andi " << context.reg(destReg) << ", " << context.reg(right_reg) << ", " << "0xff" << std::endl;
  
    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::GreaterThan(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    dst << "sgt " << context.reg(right_reg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;
    dst << "andi " << context.reg(destReg) << ", " << context.reg(right_reg) << ", " << "0xff" << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::GreaterThanEqual(std::ostream & dst, context & context, int destReg) const
{
     int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    dst << "slt " << context.reg(right_reg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;
    dst << "xori " << context.reg(right_reg) << ", " << context.reg(right_reg) << ",1" << std::endl;
    dst << "andi " << context.reg(destReg) << ", " << context.reg(right_reg) << ", " << "0xff" << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::LessThan(std::ostream &dst, context &context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    dst << "slt " << context.reg(right_reg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;
    dst << "andi " << context.reg(destReg) << ", " << context.reg(right_reg) << ", " << "0xff" << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::LessThanEqual(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    dst << "sgt " << context.reg(right_reg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;
    dst << "xori " << context.reg(right_reg) << ", " << context.reg(right_reg) << ",1" << std::endl;
    dst << "andi " << context.reg(destReg) << ", " << context.reg(right_reg) << ", " << "0xff" << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::LogicalAnd(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    std::string leftNode = branchList[0]->Returnid();
    int stackOfLHS = context.get_var_location(leftNode);
    std::string rightNode = branchList[1]->Returnid();
    int stackOfRHS = context.get_var_location(rightNode);

    std::string branch1 = context.allocateJumpBranch();
    std::string branch2 = context.allocateJumpBranch();

    dst << "lw " << context.reg(destReg) << ", " << stackOfLHS << "(s0)" << std::endl;
    dst << "beq " << context.reg(destReg) << ", " << "zero, ." << branch1 << std::endl;
    dst << "lw " << context.reg(destReg) << ", " << stackOfRHS << "(s0)" << std::endl;
    dst << "beq " << context.reg(destReg) << ", " << "zero, ." << branch2 << std::endl;
    dst << "li " << context.reg(destReg) << ", 1" << std::endl;
    dst << "j ." << branch2 << std::endl;
    dst << "." << branch1 << ":" << std::endl;
    dst << "li " << context.reg(destReg) << ", 0" << std::endl;
    dst << "." << branch2 << ":" << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::LogicalOr(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    std::string leftNode = branchList[0]->Returnid();
    int stackOfLHS = context.get_var_location(leftNode);
    std::string rightNode = branchList[1]->Returnid();
    int stackOfRHS = context.get_var_location(rightNode);

    std::string branch1 = context.allocateJumpBranch();
    std::string branch2 = context.allocateJumpBranch();
    std::string branch3 = context.allocateJumpBranch();

    dst << "lw " << context.reg(destReg) << ", " << stackOfLHS << "(s0)" << std::endl;
    dst << "bne " << context.reg(destReg) << ", " << "zero, ." << branch1 << std::endl;
    dst << "lw " << context.reg(destReg) << ", " << stackOfRHS << "(s0)" << std::endl;
    dst << "beq " << context.reg(destReg) << ", " << "zero, ." << branch2 << std::endl;
    dst << "." << branch1 << ":" << std::endl;
    dst << "li " << context.reg(destReg) << ", 1" << std::endl;
    dst << "j ." << branch3 << std::endl;
    dst << "." << branch2 << ":" << std::endl;
    dst << "li " << context.reg(destReg) << ", 0" << std::endl;
    dst << "." << branch3 << ":" << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::Modulus(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    dst << "rem " << context.reg(destReg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::Multiply(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);
    std::string id = branchList[0]->Returnid();
    std::string type;
    
    if (id == "int") { //if left branch is a constant int instead of a variable int
      type = "int";
    }
    else{
      type = context.returnVarType(id); 
    } 

   // std::cerr << type << std::endl; //check if it works

    if (type == "int"){
       dst << "mul " << context.reg(destReg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;
    }
    else if (type == "double"){
      dst << "fmul.d f" << context.reg(destReg) << ", f" << context.reg(left_reg) << ", f" << context.reg(right_reg) << std::endl;
    }
    else if (type == "float"){
      dst << "fmul.s f" << context.reg(destReg) << ", f" << context.reg(left_reg) << ", f" << context.reg(right_reg) << std::endl;
    }

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::NotEqual(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    dst << "sub " << context.reg(right_reg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;
    dst << "snez " << context.reg(right_reg) << ", " << context.reg(right_reg) << std::endl;
    dst << "andi " << context.reg(destReg) << ", " << context.reg(right_reg) << ", " << "0xff" << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::ShiftLeft(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
  int right_reg = context.allocateRegister();

  branchList[0]->EmitRISC(dst, context, left_reg);
  branchList[1]->EmitRISC(dst, context, right_reg);

  std::string right = context.reg(right_reg);
  std::string left = context.reg(left_reg);

  dst << "sll " << context.reg(destReg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;

  context.freedReg(left_reg);
  context.freedReg(right_reg);
}

void Operator::ShiftRight(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    dst << "sra " << context.reg(destReg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::Subtract(std::ostream & dst, context & context, int destReg) const
{
    int left_reg = context.allocateRegister();
    int right_reg = context.allocateRegister();

    branchList[0]->EmitRISC(dst, context, left_reg);
    branchList[1]->EmitRISC(dst, context, right_reg);

    std::string right = context.reg(right_reg);
    std::string left = context.reg(left_reg);

    std::string id = branchList[0]->Returnid();
    std::string type;
    
    if (id == "int") { //if left branch is a constant int instead of a variable int
      type = "int";
    }
    else{
      type = context.returnVarType(id); 
    } 

    int multiplier;
    if (type == "int"){
      multiplier = 4;
    }
    else if (type == "float"){
      multiplier = 8;
    }
    else if(type == "double"){
      multiplier = 8;
    }

    if(context.pointer_exists(id) == 1){
      int val = branchList[1]->returnInt();
      dst << "li "<< context.reg(right_reg) << "," << val*multiplier << std::endl;
    }

    if (type == "int"){
      dst << "sub " << context.reg(destReg) << ", " << context.reg(left_reg) << ", " << context.reg(right_reg) << std::endl;
    }
    else if (type == "double"){
      dst << "fsub.d f" << context.reg(destReg) << ", f" << context.reg(left_reg) << ", f" << context.reg(right_reg) << std::endl;
    }
    else if (type == "float"){
      dst << "fsub.s f" << context.reg(destReg) << ", f" << context.reg(left_reg) << ", f" << context.reg(right_reg) << std::endl;
    }

    context.freedReg(left_reg);
    context.freedReg(right_reg);
}

void Operator::ValueAssign(std::ostream &dst, context &context, int destReg) const
{
     branchList[0]->EmitRISC(dst, context, destReg);
    branchList[1]->EmitRISC(dst, context, destReg);
    std::string id = branchList[0]->Returnid();
    std::string type = context.returnVarType(id);

    if (context.get_var_location(id)== -1){
      int variableallocate = context.implement_var_binding(id, type);
      dst << "sw " << context.reg(destReg) <<  ", " << variableallocate << "(s0)" <<std::endl;
    }
    else {
      int variableallocate = context.get_var_location(id);
      dst << "sw " << context.reg(destReg) <<  ", " << variableallocate << "(s0)" <<std::endl;
    }
}
