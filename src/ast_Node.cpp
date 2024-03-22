#include "ast_Node.hpp"

Node::Node(std::vector<NodePtr> _branchList) //this is a case where you do [new Node(a list of pointers)]
  : branchList(_branchList)
{}

Node::Node() //this is a case where Node() is called with no parameters
  : Node(std::vector<NodePtr>{}) // you refer to the constructor above
  //carrying out "constructor delegation" where you reuse a constructor 
{}


Node::~Node() // Destructor
{
  for(unsigned i = 0; i < branchList.size(); i++){
    delete branchList[i];
  }
}

void Node::print(std::ostream &dst, std::string indent) const{
  dst << indent << "Node Class Reached. ERROR!!! (print)" << std::endl;
}

void Node::EmitRISC(std::ostream &dst, context &context, int destReg) const
{
  dst << "Node Class Reached. ERROR!!! (EmitRISC)" << std::endl;
}

std::string Node::Returnid() const{
  std::cerr << "Node Class Reached. ERROR!!! (ReturnId)" << std::endl;
  return "";
}

std::string Node::getType() const{
  std::cerr << "Node Class Reached. ERROR!!! (ReturnId)" << std::endl;
  return "";
}

int Node::getSize() const{
  std::cerr << "Node Class Reached. ERROR!!! (getSize)" << std::endl;
  return 0;
}

NodePtr Node::returnBranch(int index) const{
  std::cerr << "Node Class Reached. ERROR!!! (returnBranch)" << std::endl;
  return nullptr;
}

void Node::createParameterMap(context &context) const{
  std::cerr << "Node Class Reached. ERROR!!! (createParameterMap)" << std::endl;
}

void Node::createVariableMap(context &context) const{
  std::cerr << "Node Class Reached. ERROR!!! (createVariableMap)" << std::endl;
}

void Node::isFunctionCall(context &context) const{
  std::cerr << "Node Class Reached. ERROR!!! (isFunctionCall)" << std::endl;
}

int Node::GetArgLocation() const{
  std::cerr << "Node Class Reached. ERROR!!! (GetArgLocation)" << std::endl;
  return 0;
}

void Node::isPointer(context &context) const{
  std::cerr << "Node Class Reached. ERROR!!! (isPointer)" << std::endl;
}

 int Node::returnInt() const{
  std::cerr << "Node Class Reached. ERROR!!! (returnInt)" << std::endl;
  return 0;
}

std::string Node::returnOp() const{
    std::cerr << "Node Class Reached. ERROR!!! (returnOp)" << std::endl;
    return "";
}
