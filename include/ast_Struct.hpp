#ifndef ast_struct_hpp
#define ast_struct_hpp

#include "ast_Node.hpp"

#include <cmath>


class structDefinition : public Node
{
public:
    std::string identifier;
    NodePtr expression;

    structDefinition(std::string _identifier, NodePtr _expression)
    {
        branchList.insert(branchList.end() , _expression );
    }


    virtual ~structDefinition()
    {delete expression;;
    }

    virtual void print(std::ostream &dst, std::string indent ) const override
    {
        // std::cerr<<"compiling struct definition"<<std::endl;
        // dst<<"struct: "<<identifier<<std::endl;
        // if(expression == NULL){
        //     dst<<"finish struct def"<<std::endl;
        //     return;
        // }
        // for(int i = 0; i < expression->getSize(); i++){
        //     expression->print(dst, "    ");
        //     dst<<std::endl;
        // }
        // dst<<"finish struct def"<<std::endl;

    }


    int getSize() const override{
        return branchList[0]->getSize();
    }

    std::string Returnid() const override{
        return identifier; 
    }

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override{

        if(expression == NULL){
            return;
        }
        for( auto branch : branchList)
        {
            branch->EmitRISC(dst, context, destReg);
        }
        }

};

class structDeclaration : public Node
{
private:
protected:

public:
    NodePtr identifier;
    NodePtr expression;

    structDeclaration(NodePtr _identifier, NodePtr _expression) :identifier(_identifier), expression(_expression){}

    virtual ~structDeclaration()
    {delete expression;
    }

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        std::cerr<<"compiling struct declaration"<<std::endl;
        dst<<"struct member:"<<expression->Returnid();
    }

    int getSize() const override{
        return identifier->getSize();
    }

    std::string Returnid() const override{
        return identifier->Returnid();
    }

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override
    {


    }

};

class structMember : public Node
{
public:
    NodePtr identifier;
    std::string member;

    structMember(NodePtr _identifier, std::string _member) : identifier(_identifier) , member(_member) {}

    virtual ~structMember()
    {
        delete identifier;
    }

    virtual void print(std::ostream &dst, std::string indent) const override
    {
        std::cerr<<"calling struct member"<<std::endl;
        dst<<"member: "<<member;
    }

    int getSize() const override{
        return 4;
    }
    std::string Returnid() const override{
        return identifier->Returnid();
    }

    void EmitRISC(std::ostream &dst, context &context, int destReg) const override{
        identifier->EmitRISC(dst, context, destReg);
        dst<<"addi x"<<destReg<<", x"<<destReg<<", "<< 0 <<std::endl;
        dst<<"lw x"<<destReg<<", 0(x"<<destReg<<")"<<std::endl;
    }


};






#endif