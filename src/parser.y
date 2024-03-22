// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

// TODO: you can either continue adding to this grammar file or
// rename parser_full.y to parser.y once you're happy with
// how this example works.

%code requires{
  #include "ast.hpp"

  //#include <cassert>
  extern Node *g_root;
  extern FILE *yyin;
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of AST node.
%union{
  NodePtr 		Node;
  //NodeList      *nodes;
  int 			number_int;
  double 		number_float;
  std::string 	*string;
  yytokentype 	token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL SIZEOF CONSTANT
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN
%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <Node> primary_expression unary_expression postfix_expression
%type <Node> multiplicative_expression additive_expression shift_expression
%type <Node> relational_expression equality_expression and_expression
%type <Node> exclusive_or_expression inclusive_or_expression logical_and_expression
%type <Node> logical_or_expression conditional_expression assignment_expression
%type <Node> expression constant_expression
%type <Node> declaration declaration_specifiers init_declarator
%type <Node> type_specifier struct_specifier struct_declaration struct_or_union_specifier
%type <Node> struct_declarator declarator enum_specifier enumerator
%type <Node> pointer direct_declarator abstract_declarator direct_abstract_declarator
%type <Node> parameter_declaration type_name initializer
%type <Node> statement labeled_statement compound_statement expression_statement
%type <Node> selection_statement iteration_statement jump_statement external_declaration
%type <Node> function_definition cast_expression
%type <Node> translation_unit declaration_list specifier_qualifier_list
%type <Node> struct_declaration_list struct_declarator_list enumerator_list
%type <Node> argument_expression_list IDENTIFIER_list initializer_list
%type <Node> statement_list parameter_type_list parameter_list init_declarator_list unary_operator

%type <number_float> FLOAT_CONSTANT
%type <number_int> STRING_LITERAL CONSTANT INT_CONSTANT
%type <string> IDENTIFIER
%start ROOT
%%
ROOT
	: translation_unit {g_root = $1; }
	;

translation_unit
	: external_declaration { $$ = $1; }
	| translation_unit external_declaration { $$ = new  MultiFunction($1, $2);}
	;
external_declaration
	: function_definition { $$ = $1; }
	| declaration { $$ = $1;}
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement {$$ = new Function_Definition($1, $2, $3);}
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;


declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier {$$ = $1;}
	| type_specifier declaration_specifiers
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

declarator
	: pointer direct_declarator  {$$ = new PointerDeclarator($1, $2);}
	| direct_declarator {$$ = $1;}
	;

direct_declarator
	: IDENTIFIER  {$$ = new Name_Declarator(*$1); delete $1;}
	| '(' declarator ')' {$$ = $2;}
	| direct_declarator '[' constant_expression ']' {$$ = new Array($1, $3);}
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')' {$$ = new Function_Declarator($1, $3);}
	| direct_declarator '(' IDENTIFIER_list ')'
	| direct_declarator '(' ')'{$$ = $1;}
	;

compound_statement
	: '{' '}' {$$ = new EmptyNode();}
	| '{' statement_list '}' {$$ = $2;}
	| '{' declaration_list '}' {$$ = $2;}
	| '{' declaration_list statement_list '}' {$$ = new Multiline($2, $3);}
	;

type_specifier
	: VOID { $$ = new Types("void");}
	| CHAR { $$ = new Types("char");}
	| SHORT { $$ = new Types("short");}
	| INT { $$ = new Types("int");}
	| LONG { $$ = new Types("long");}
	| FLOAT { $$ = new Types("float");}
	| DOUBLE { $$ = new Types("double");}
	| SIGNED { $$ = new Types("signed");}
	| UNSIGNED { $$ = new Types("unsigned");}
	| struct_or_union_specifier
	| enum_specifier
	| type_name
	;

statement_list
	: statement {$$ = $1;}
	| statement_list statement {$$ = new MultiStatement($1, $2);}
	;

statement
	: labeled_statement
	| compound_statement {$$ = $1;}
	| expression_statement {$$ = $1;}
	| selection_statement {$$ = $1;}
	| iteration_statement {$$ = $1;}
	| jump_statement {$$ = $1;}
	;

expression_statement
	: ';'
	| expression ';' {$$ = $1;}
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';' {$$ = new Return_Statement(new Int());}
	| RETURN expression ';' {$$ = new Return_Statement($2);}
	;

expression
	: assignment_expression {$$ = $1;}
	| expression ',' assignment_expression
	;

assignment_expression
	: conditional_expression {$$ = $1;}
	| unary_expression '=' assignment_expression { $$ = new Operator($1, $3, OperatorType::ValueAssign);}
	| unary_expression ADD_ASSIGN assignment_expression { $$ = new Operator($1, new Operator($1, $3, OperatorType::Add), OperatorType::ValueAssign); }
	| unary_expression MUL_ASSIGN assignment_expression { $$ = new Operator($1, new Operator($1, $3, OperatorType::Multiply), OperatorType::ValueAssign); }
	| unary_expression DIV_ASSIGN assignment_expression { $$ = new Operator($1, new Operator($1, $3, OperatorType::Divide), OperatorType::ValueAssign); }
	| unary_expression MOD_ASSIGN assignment_expression { $$ = new Operator($1, new Operator($1, $3, OperatorType::Modulus), OperatorType::ValueAssign); }
	| unary_expression SUB_ASSIGN assignment_expression { $$ = new Operator($1, new Operator($1, $3, OperatorType::Subtract), OperatorType::ValueAssign); }
	| unary_expression LEFT_ASSIGN assignment_expression { $$ = new Operator($1, new Operator($1, $3, OperatorType::ShiftLeft), OperatorType::ValueAssign); }
	| unary_expression RIGHT_ASSIGN assignment_expression { $$ = new Operator($1, new Operator($1, $3, OperatorType::ShiftRight), OperatorType::ValueAssign); }
	| unary_expression AND_ASSIGN assignment_expression { $$ = new Operator($1, new Operator($1, $3, OperatorType::BitwiseAnd), OperatorType::ValueAssign); }
	| unary_expression XOR_ASSIGN assignment_expression { $$ = new Operator($1, new Operator($1, $3, OperatorType::BitwiseXor), OperatorType::ValueAssign); }
	| unary_expression OR_ASSIGN assignment_expression { $$ = new Operator($1, new Operator($1, $3, OperatorType::BitwiseOr), OperatorType::ValueAssign); }
	;

conditional_expression
	: logical_or_expression {$$ = $1;}
	| logical_or_expression '?' expression ':' conditional_expression
	;

logical_or_expression
	: logical_and_expression {$$ = $1;}
	| logical_or_expression OR_OP logical_and_expression {$$ = new Operator($1, $3, OperatorType::LogicalOr);}
	;

logical_and_expression
	: inclusive_or_expression {$$ = $1;}
	| logical_and_expression AND_OP inclusive_or_expression {$$ = new Operator($1, $3, OperatorType::LogicalAnd);}
	;

inclusive_or_expression
	: exclusive_or_expression {$$ = $1;}
	| inclusive_or_expression '|' exclusive_or_expression {$$ = new Operator($1, $3, OperatorType::BitwiseOr);}
	;

exclusive_or_expression
	: and_expression {$$ = $1;}
	| exclusive_or_expression '^' and_expression {$$ = new Operator($1, $3, OperatorType::BitwiseXor);}
	;

and_expression
	: equality_expression {$$ = $1;}
	| and_expression '&' equality_expression  {$$ = new Operator($1, $3, OperatorType::BitwiseAnd);}
	;

equality_expression
	: relational_expression {$$ = $1;}
	| equality_expression EQ_OP relational_expression  {$$ = new Operator($1, $3, OperatorType::Equal);}
	| equality_expression NE_OP relational_expression {$$ = new Operator($1, $3, OperatorType::NotEqual);}
	;

relational_expression
	: shift_expression {$$ = $1;}
	| relational_expression '<' shift_expression {$$ = new Operator($1, $3, OperatorType::LessThan);}
	| relational_expression '>' shift_expression {$$ = new Operator($1, $3, OperatorType::GreaterThan);}
	| relational_expression LE_OP shift_expression {$$ = new Operator($1, $3, OperatorType::LessThanEqual);}
	| relational_expression GE_OP shift_expression {$$ = new Operator($1, $3, OperatorType::GreaterThanEqual);}
	;

shift_expression
	: additive_expression {$$ = $1;}
	| shift_expression LEFT_OP additive_expression {$$ = new Operator($1, $3, OperatorType::ShiftLeft);}
	| shift_expression RIGHT_OP additive_expression {$$ = new Operator($1, $3, OperatorType::ShiftRight);}
	;

additive_expression
	: multiplicative_expression {$$ = $1;}
	| additive_expression '+' multiplicative_expression {$$ = new Operator($1, $3, OperatorType::Add);}
	| additive_expression '-' multiplicative_expression {$$ = new Operator($1, $3, OperatorType::Subtract);}
	;

multiplicative_expression
	: cast_expression {$$ = $1;}
	| multiplicative_expression '*' cast_expression {$$ = new Operator($1, $3, OperatorType::Multiply);}
	| multiplicative_expression '/' cast_expression {$$ = new Operator($1, $3, OperatorType::Divide);}
	| multiplicative_expression '%' cast_expression {$$ = new Operator($1, $3, OperatorType::Modulus);}
	;

cast_expression
	: unary_expression {$$ = $1;}
	| '(' type_name ')' cast_expression
	;

unary_expression
	: postfix_expression {$$ = $1;}
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression {$$ = new Unary($1, $2); }
	| SIZEOF unary_expression {$$ = new SizeOf($2); }
	| SIZEOF '(' type_name ')' {$$ = new SizeOf($3); }
	;

postfix_expression
	: primary_expression {$$ = $1;}
	| postfix_expression '[' expression ']'  {$$ = new Array($1, $3);}
	| postfix_expression '(' ')'  {$$ = new Function_Call_With_NoArguments($1);}
	| postfix_expression '(' argument_expression_list ')' {$$ = new Function_Call_With_Arguments($1, $3);}
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP {$$ = new UnaryPostOp($1, "++");}
	| postfix_expression DEC_OP {$$ = new UnaryPostOp($1, "--");}
	;

primary_expression
	: IDENTIFIER {$$ = new Identifier(*$1);}
	| CONSTANT  {$$ = new Int($1);}
	| INT_CONSTANT { $$ = new Int($1);}
	| STRING_LITERAL { $$ = new Int($1);}
	| '(' expression ')' {$$ = $2;}
	;

parameter_type_list
	: parameter_list {$$ = new Param_List($1);}
	;

parameter_list
	: parameter_declaration {$$ = $1;}
	| parameter_list ',' parameter_declaration {$$ = new Param_List_Declarator($1, $3);}
	;

parameter_declaration
	: declaration_specifiers declarator {$$ = new Param_Declarator($1, $2);}
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

declaration_list
	: declaration {$$ = $1;}
	| declaration_list declaration  {$$ = new MultiDeclaration($1, $2);}
	;

declaration
	: declaration_specifiers ';'  {$$ = $1;}
	| declaration_specifiers init_declarator_list ';'  {$$ = new MultiDec($1, $2);}
	;

argument_expression_list
	: assignment_expression {$$ = new Arg_Declarator($1);}
	| argument_expression_list ',' assignment_expression {$$ = new Arg_List_Declarator($1, $3);}
	;

unary_operator
	: '&' {$$ = new UnaryOp("&");}
	| '*' {$$ = new UnaryOp("*");}
	| '+' {$$ = new UnaryOp("+");}
	| '-' {$$ = new UnaryOp("-");}
	| '~' {$$ = new UnaryOp("~");}
	| '!' {$$ = new UnaryOp("!");}
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

constant_expression
	: conditional_expression {$$ = $1;}
	;

init_declarator_list
	: init_declarator {$$ = $1;}
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator {$$ = new VariableDeclarator($1);}
	| declarator '=' initializer {$$ = new VariableAssign($1, $3);}
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}' {$$ = new structDefinition(*$2, $4);}
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER {$$ = new structDefinition(*$2,NULL);}
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';' {$$ = new structDeclaration($1, $2); }
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier {$$ = $1;}
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
	: CONST
	| VOLATILE
	;


pointer
	: '*' {$$ = new Pointer();}
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


IDENTIFIER_list
	: IDENTIFIER
	| IDENTIFIER_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list {$$ = $1;}
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression {$$ = $1;}
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;


labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

selection_statement
	: IF '(' expression ')' statement  { $$ = new If($3, $5); }
	| IF '(' expression ')' statement ELSE statement { $$ = new If_Else($3, $5, $7); }
	| SWITCH '(' expression ')' statement { $$ = new Switch($3, $5); }
	;

iteration_statement
	: WHILE '(' expression ')' statement { $$ = new While($3, $5); }
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement  { $$ = new For($3, $4, $5, $7); }
	;

%%

Node *g_root;

Node *ParseAST(std::string filename)
{
  yyin = fopen(filename.c_str(), "r");

  if(yyin == NULL){
    std::cerr << "Couldn't open input file: " << filename << std::endl;
    exit(1);
  }

  g_root=NULL;
  yyparse();
  return g_root;
}
