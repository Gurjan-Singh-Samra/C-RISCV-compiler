#include "ast_ArgDeclaration.hpp"
#include "ast_NameDeclarator.hpp"
#include "ast_ParamDeclaration.hpp"
#include "ast_VariableAssign.hpp"
#include "ast_VariableDeclarator.hpp"
#include "ast_Unary.hpp"
#include "ast_Pointer.hpp"
#include "ast_Multiline.hpp"
#include "ast_MultiStatement.hpp"
#include "ast_MultiFunction.hpp"
#include "ast_Declaration.hpp"
#include "ast_Declarator.hpp"
#include "ast_Functions.hpp"
#include "ast_EmptyNode.hpp"
#include "ast_Statement.hpp"
#include "ast_Array.hpp"
#include "ast_Operator.hpp"
#include "ast_Node.hpp"
#include "ast_Identifier.hpp"
#include "ast_Integer.hpp"
#include "ast_Types.hpp"
#include "ast_Struct.hpp"
#include "context.hpp"

typedef std::vector<NodePtr> Vect;
typedef Vect* VectPtr;

extern Node *ParseAST(std::string filename);
