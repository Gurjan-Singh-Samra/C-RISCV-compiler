#ifndef ast_Node_hpp
#define ast_Node_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include "context.hpp" //don't need this yet

class Node;
typedef Node* NodePtr;

class Node
{
protected:
  std::vector<NodePtr> branchList;

public:
  Node(std::vector<NodePtr> _branchList); 
  Node();

  virtual void print(std::ostream &dst, std::string indent) const;

  virtual ~Node();
  
  virtual void EmitRISC(std::ostream &dst, context &context, int destReg) const;

  virtual int getSize() const;

  virtual std::string getType() const;

  virtual std::string Returnid() const;

  virtual NodePtr returnBranch(int index) const;

  virtual void createParameterMap(context &context) const;

  virtual void createVariableMap(context &context) const;

  virtual void isFunctionCall(context &context) const;

  virtual int GetArgLocation() const;

  virtual void isPointer(context &context) const;

  virtual int returnInt() const;

  virtual std::string returnOp() const;
};


#endif