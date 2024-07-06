
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "test.y"

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

extern FILE* yyin;
extern char *yytext;

char* expected_type;

typedef struct
{
    char *name;
    char *type;
    char *value;
    int size[16];
} symbol;

typedef struct{
    char *type;
    char *value;
}sym;

int arraySize[16];
int arrLen = 0;

int variableArraySize[16];
int variableArrLen = 0;

int symbolPosition = -1;

char * symbolType;
char * symbolValue;

typedef struct{
    char *type;
    char *name;
    char *signature[];
}funcsymbol;


symbol symbol_table[1024];
funcsymbol funcsymbol_table[128];
int symbol_count = 0;

void printTable(){
    printf("Symbol Table is:\n");
    for (int i = 0; i < symbol_count; i++)
    {
        printf("[%d] Name:%s Type:%s Value:%s Size:",
        i,
        symbol_table[i].name,
        symbol_table[i].type,
        symbol_table[i].value);
        int j = 0;
        while (j < 16)
        {
            if (symbol_table[i].size[j] == 0)
            {
                break;
            }
            printf("%d ",symbol_table[i].size[j]);
            j++;
        }
        printf("\n");
    }
    printf("Symbol Table ended\n");
}


bool string_to_bool(char *string)
{
    if (strcmp(string, "true") == 0)
    {
        return true;
    }
    return false;
}

char *bool_to_string(bool boolean)
{
    if (boolean)
    {
        return strdup("true");
    }
    return strdup("false");
}

int string_to_int(char *string)
{
    return atoi(string);
}

char *int_to_string(int integer)
{
    char *string = malloc(sizeof(char) * 100);
    sprintf(string, "%d", integer);
    return string;
}

float string_to_float(char *string)
{
    return atof(string);
}

char *float_to_string(float real)
{
    char *string = malloc(sizeof(char) * 100);
    sprintf(string, "%f", real);
    return string;
}

typedef struct ASTNode
{
    char* type;
    char* value;
    struct ASTNode* left;
    struct ASTNode* right;
}ASTNode;


ASTNode* buildAST(char* root, ASTNode* left, ASTNode* right, char *type)
{
    // printf("BUILDAST:  %s\n", root);
    ASTNode* newnode = (ASTNode*)malloc(sizeof(ASTNode));
    newnode->type = strdup(type);

    if(left == NULL)
    {
        if(right != NULL)
            yyerror("stanga null, dreapta nu");
        newnode->left = NULL;
        newnode->right = NULL;
    }
    else if(right == NULL)
        yyerror("dreapta null, stanga nu");
    else
    {
        newnode->left = left;
        newnode->right = right;
    }
    newnode->value = strdup(root);  

    if(strcmp(type, "op") == 0 || strcmp(type, "opb") == 0)
    {
        printf("OP ESTE OK IAR TYPEURILE: %s %s\n", left->type, right->type);
        if(strcmp(left->type, "null") == 0 || strcmp(right->type, "null") == 0 || strcmp(left->type, right->type) != 0)
            newnode->type = strdup("null"), yyerror("IN AN EXPRESSION ALL MEMBERS MUST HAVE THE SAME TYPE"), exit(1);
        else
            newnode->type = strdup(left->type);
    }
    printf("newnode: %s %s\n", newnode->value, newnode->type);
    if (newnode->left != NULL)
        printf("ROOT LEFT ESTE: %s\n", newnode->left->value);
    if (newnode->right != NULL)
    {
        printf("RIFGT NU ESTE NULL\n");
        printf("ROOT RIGHT ESTE: %s\n", newnode->right->value);
    }
    printf("AM TRECUT DE VERIFICARI\n");
    return newnode;
}

char* typeofnode(ASTNode* root)
{
    if(root == NULL)
        return strdup("null\0");
    return strdup(root->type);
}

char* evalAST(ASTNode* root)
{
    // printf("APACHE")
    printf("%s %s", root->type, root->value);
    printf("AM AJUNS LA EVALUARE\n");
    bool isint = (strcmp(root->type, "int") == 0);
    bool isbool = (strcmp(root->type, "bool") == 0);
    bool isfloat = (strcmp(root->type, "float") == 0);
    // printf("TIP: %s VALOARE %s STANGA %s DREAPTA %s\n", root->type, root->value, ((ASTNode*)root->left)->value, ((ASTNode*)root->right)->value);
    // if(!isbool)
    if (isint || isfloat)
    {
        // printf("nu e bool. de ce??\n");
        printf("TIP: %s VALUE: %s\n", root->type, root->value);
        if(root == NULL)
            return 0;
        if(isint && isdigit(root->value[0]))
        {
            // printf("AM RETURNAT\n");
            // printf("root->value: %s\n", root->value);
            return root->value;
        }
        if(isdigit(root->value[0]))
            return root->value;
        if(strcmp(root->value, "+") == 0)
            if(isint)
            {
                // evalAST(root->left);
                // printf("AM AJUNS LA PLUS\n");
                // printf("BAAAAAAAAAAAAAAAAAAAAAAAAAAAAA: %s", evalAST(root->right));
                // return NULL;
                // printf("DUPA PLUS:, %s\n", ((ASTNode*)(root->right))->value);

                // printf("%s", root->right->value);
                // char* verif = strdup(int_to_string(atoi(evalAST(root->left)) + atoi(evalAST(root->right))));
                // printf("AM TRECUT PESTE, [%s]\n", verif);
                // if (strcmp(evalAST(root->left), "2") == 0)
                // {
                //     printf("ACILISA, %s\n", ((ASTNode*)(root->right))->value);
                //     printf("ACILISA, %s\n", evalAST(root->right));

                // }
                // return verif;
                return int_to_string(atoi(evalAST(root->left)) + atoi(evalAST(root->right)));

            }
            else
                return float_to_string(atof(evalAST(root->left)) + atof(evalAST(root->right)));
        if(strcmp(root->value, "-") == 0)
            if(isint)
                return int_to_string(atoi(evalAST(root->left)) - atoi(evalAST(root->right)));
            else
                return float_to_string(atof(evalAST(root->left)) - atof(evalAST(root->right)));
        if(strcmp(root->value, "*") == 0)
            if(isint)
            {
                // printf("INMULTIRE\n");
                return int_to_string(atoi(evalAST(root->left)) * atoi(evalAST(root->right)));   
            }
            else
                return float_to_string(atof(evalAST(root->left)) * atof(evalAST(root->right)));
        if(strcmp(root->value, "/") == 0)
            if(isint)
                return int_to_string(atoi(evalAST(root->left)) / atoi(evalAST(root->right)));
            else
                return float_to_string(atof(evalAST(root->left)) / atof(evalAST(root->right)));
        if(root->value[0] == '-' || isdigit(root->value[0]))   //este int :O
            return strdup(root->value);
    }
    else if (isbool)
    {
        printf("FAC COMPARATIE INTRE BOOL\n");
        if(strcmp(root->value, "||") == 0) 
        {
            return bool_to_string(string_to_bool(evalAST(root->left)) || string_to_bool(evalAST(root->right)));
        }
        else if(strcmp(root->value, "&&") == 0) 
        {
            // printf("APCHE\n");
            // evalAST(root->left);
            // printf("AM INTRAT IN SI. %s, %s\n", ((ASTNode*)(root->left))->type, ((ASTNode*)(root->right))->type);
            // printf("%s", bool_to_string(string_to_bool(evalAST(root->left)) && string_to_bool(evalAST(root->right))));
            // if (((ASTNode*)(root->left))->value == NULL || ((ASTNode*)(root->right))->value == NULL)
            if (root->left == NULL || root->right == NULL)
                printf("ESTE NULL NU ESTE BINE\n");
            else
            {
                printf("NIICUNUL DINTRE ELE NU ESTE NULL\n");
                // if (((ASTNode*)(root->left)->value) == NULL)
                //    printf("ROOT LEFT VALUE ESTE NULL\n");
                // else if (((ASTNode*)(root->right)->value) == NULL)
                //     printf("ROOT RIGHT VALUE ESTE NULL\n");
                printf("AM TRECUT DE IFURI\n");
            }
            char v[100] = "abcd";
            root->left->value = strdup(v);
            root->right->value = strdup(v);
            printf("ROOT LEFT: %s, ROOT RIGHT: %s\n", root->left->value, root->right->value);
            // printf("AM AJUNS AICI ASDASDASDASDASDASD\n");
            return bool_to_string(string_to_bool(evalAST(root->left)) && string_to_bool(evalAST(root->right)));
        }
           
        // printf("ASIGNARE");
        return root->value;
    }
    else
    {
        printf("AM AJUNS LA STRING\n");
        return root->value;
    }
    //identifier
    for(int i = 0; i < symbol_count; i ++)
        if(strcmp(root->value, symbol_table[i].name) == 0)
            return symbol_table[i].value;
}



char* get_type_of_value(ASTNode* value)
{
    printf("valoare type: %s\n", value->type);
    if(strcmp("true", value->type) == 0 || strcmp("false", value->type) == 0)
        return strdup("bool");
    if(strchr(value->type, ".") == 0)
        return strdup("float");
    if(value->type[0] == '\"')
        return strdup("string");
    if(isdigit(value->type[0]) || (value->type[0] == '-' || value->type[0] == '+') && isdigit(value->type[1]))
        return strdup("int");
    return strdup("null");
}

char *get_type(char *name)
{

    int i;
    for (i = 0; i < symbol_count; i++)
    {

        if (strcmp(symbol_table[i].name, name) == 0)
        {
            return strdup(symbol_table[i].type);
        }
    }
    yyerror("variable not declared");
    exit(1);
    // return strdup("");
}

char *check_type(ASTNode *value1, ASTNode *value2)
{
    printf("CHECKING TYPES: %s and %s\n", value1->type, value2->type);
    if (strcmp(value1->type, value2->type) == 0)
    {
        return strdup(value1);
    }
    yyerror("members of expresion don't have the same type\n");
    return strdup("null");
}

char *get_value(char *name)
{
    int i;
    for (i = 0; i < symbol_count; i++)
    {
        if (strcmp(symbol_table[i].name, name) == 0)
        {
            if(symbol_table[i].size[0] == 0)
            {
                symbolPosition = i;
                return strdup(symbol_table[i].value);
            }
            
            //check array

            int step = 1;
            int distanceFromOrigin = 0;

            int length = 1;
            while(symbol_table[i].size[step]){
                length *= variableArraySize[step];
                step++;
            }

            step=0;
            while(symbol_table[i].size[step + 1]){
                if(symbol_table[i].size[step] <= variableArraySize[step]){
                    printf("Size missmatch in array variable!\n");
                    exit(1);
                }

                distanceFromOrigin += length * variableArraySize[step];
                length/=variableArraySize[step];
                length/=symbol_table[i].size[step + 1];
                
                step++;
            }

            if(step + 1 != variableArrLen){
                printf("Too many dimensions for provided array!\n");
                exit(1);
            }
            
            if(symbol_table[i].size[step] < variableArraySize[step]){
                printf("Size missmatch in array variable!\n");
                exit(1);
            }
            distanceFromOrigin+=variableArraySize[step];
            
            symbolPosition = i + distanceFromOrigin;
            
            return symbol_table[i + distanceFromOrigin].value;
            
        }
    }
    yyerror("variable not declared");
    exit(1);
    // return strdup("");
}

void returnVariable(char *name){

    symbolType = strdup(get_type(name));
    symbolValue = strdup(get_value(name));

    for(int i = 0; i < variableArrLen; i++)
    {
        variableArraySize[i] = 0;
    }
    variableArrLen = 0;    

}

/*void set_type(char *name, char *type)
{
    int i;
    for (i = 0; i < symbol_count; i++)
    {
        if (strcmp(symbol_table[i].name, name) == 0)
        {
            symbol_table[i].type = strdup(type);
            return;
        }
    }
    symbol_table[symbol_count].name = strdup(name);
    symbol_table[symbol_count].type = strdup(type);
    //symbol_table[symbol_count].value = strdup(value);
}*/

void setExistingValue(char* name, char* value)
{
    // if( symbolPosition == -1){
    //     printf("Error setting existing value!\n");
    //     exit(0);
    // }
    char* type;
    printf("AM AJUNS LA SET EXISTING VALUE CU: name: %s, value: %s\n", name, value);
    printf("AVEM %d SIMBOLURI\n", symbol_count);
    for (int i = 0; i < symbol_count; i++)
        if (strcmp(name, symbol_table[i].name) == 0)
            type = symbol_table[i].type;
    if (!check_correct_type(type, value))
        exit(1);
    for (int i = 0; i < symbol_count; i++)
    {
        // printf("NUME IN TABEL: %s, NUME PRIMIT: %s\n", symbol_table[i].name, name);
        if (strcmp(name, symbol_table[i].name) == 0)
        {
            printf("AM GASIT IN TABEL\n");
            printf("NAME: %s, SYMBOL TABLE NAME: %s\n", name, symbol_table[i].name);

            if (symbol_table[i].size[0])
            {
                printf("ESTE VECTOR\n");
                for (int j = 0; j < variableArrLen; j++)
                    printf("var array: %d", variableArraySize[j]);
                symbol_table[i + variableArraySize[0]].value = value;
                returnVariable(name);
                return;
            }

            symbol_table[i].value = value;

        }
    }
}

void set_value(char *name, char *value, char *type)
{
    printf("AM INTRAT IN SET VALUE\n");
    if(check_existing_variable(name)){
        printf("Variable already declared.");
        exit(1);
    }
    printf("AM TRECUT DE CHECK\n");
    if(symbol_count == 1024){
        printf("Cannot declare anymore variables!\n");
        exit(1);
    }
    printf("val: [%s]\n", value);


    if(arraySize[0]){
        if(arrLen > 15){
            printf("Too many array dimensions!\n");
            exit(1);
        }

        int lengthOfArray = 1;
        int sizePos = 0;
        while(arraySize[sizePos])
        {
            symbol_table[symbol_count].size[sizePos] = arraySize[sizePos];
            lengthOfArray *= arraySize[sizePos];
            sizePos++;
        }

        if(symbol_count + lengthOfArray > 1023 ){
            printf("Too many variables to declare!\n");
            exit(1);
        }

        symbol_table[symbol_count].name = strdup(name);
        symbol_table[symbol_count].type = strdup(type);

        int steps = 0;
        while(steps < lengthOfArray){
            // char v[] = "";
            symbol_table[symbol_count + steps].value = strdup(value);
            symbol_table[symbol_count + steps].name = strdup(name);
            symbol_table[symbol_count + steps].type = strdup(type);
            steps++;
        }
        symbol_count += lengthOfArray;

        //clear arraySize
        for(int i = 0;i<arrLen;i++){
            arraySize[i] = 0;
        }
        arrLen = 0;
        
        return;
    }

    if (!check_correct_type(type, value))
        exit(1);

    int i;
    for (i = 0; i < symbol_count; i++)
    {
        // if (symbol_table[i].name)
        if (strcmp(symbol_table[i].name, name) == 0)
        {
            if (strcmp(symbol_table[i].type, type) == 0)
            {
                symbol_table[i].value = strdup(value);
            }
            else
            {
                yyerror("invalid type");
                exit(1);
            }
        }
    }
    printf("AM GASIT SIMBOLUL %d", i);
    symbol_table[symbol_count].name = strdup(name);
    symbol_table[symbol_count].type = strdup(type);
    symbol_table[symbol_count].value = strdup(value);
    symbol_table[symbol_count].size[0] = 0;
    symbol_count++;
}

void check_correct_type(char* type, char* value)
{
    //bool
    if(strcmp(type, "bool") == 0 && !(strcmp(value, "true") == 0 || strcmp(value, "false") == 0))
    {
        yyerror("only a bool value can be assigned to a bool variable");
        return false;
        // exit(1);
    }
    //int
    else if(strcmp(type, "int") == 0)
    {
        printf("AM AJUNS IN SET VALUE LA INT\n");
        int i = 0;
        if(value[0] == '-' || value[0] == '+')
            i ++;
        for(; i < strlen(value); i ++)
            if(value[i] < '0' || value[i] > '9')
            {
                yyerror("only an int value can be assigned to an int variable");
                return false;
                // exit(1);
            }
    }
    else if(strcmp(type, "uint") == 0){
        int i = 0;
        if(value[0] == '+')
            i++;
        for(; i < strlen(value); i ++)
            if(value[i] < '0' || value[i] > '9')
            {
                yyerror("only an uint value can be assigned to an uint variable");
                return false;
                // exit(1);
            }
            

    }
    else if(strcmp(type, "float") == 0)
    {
        bool dot = false;
        int i = 0;
        if(value[0] == '-')
            i ++;
        for(; i < strlen(value); i ++)
        {
            if(value[i] == '.')
            {
                if(dot == false)
                    dot = true;
                else if (dot == true){
                    yyerror("only a float value can be assigned to a float variable");
                    return false;
                    // exit(1);
                }
            }
            else if(value[i] < '0' || value[i] > '9'){
                yyerror("only a float value can be assigned to a float variable");
                return false;
                // exit(1);
            }
        }
    }
    return true;
}

int check_existing_variable(char *name)             
{
    printf("NUME IN CHECK: %s\n", name);
    for (int i = 0; i < symbol_count; i++)
    {
        // if (symbol_table[i].name)
        if (strcmp(name, symbol_table[i].name) == 0)
            return 1;
    }
    return 0;
}

ASTNode* eval_boolexpr_op(char* a, char* b, char* op)
{
    ASTNode* newnode = (ASTNode*)malloc(sizeof(ASTNode));
}




/* Line 189 of yacc.c  */
#line 703 "test.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

/* "%code requires" blocks.  */

/* Line 209 of yacc.c  */
#line 645 "test.y"

    



/* Line 209 of yacc.c  */
#line 733 "test.tab.c"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     START_VARS = 258,
     START_FUNC = 259,
     START_USER = 260,
     START_MAIN = 261,
     END_SECTION = 262,
     TYPE_OF = 263,
     EVAL = 264,
     PRINT_TABLE = 265,
     IDENTIFIER = 266,
     INT_LITERAL = 267,
     FLOAT_LITERAL = 268,
     BOOLEAN_LITERAL = 269,
     STRING_LITERAL = 270,
     INT = 271,
     UINT = 272,
     FLOAT = 273,
     BOOL = 274,
     STR = 275,
     ADD = 276,
     SUB = 277,
     MUL = 278,
     DIV = 279,
     LE = 280,
     GT = 281,
     LEQ = 282,
     GTQ = 283,
     AND = 284,
     OR = 285,
     EQ = 286
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 650 "test.y"

    char* val;
    char *name;
    int arr;
    int vec[16];
    char** sym;
    struct ASTNode* nod;



/* Line 214 of yacc.c  */
#line 792 "test.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 804 "test.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   214

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  83
/* YYNRULES -- Number of states.  */
#define YYNSTATES  176

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      36,    37,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    32,
       2,    33,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    34,     2,    35,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     8,    12,    13,    15,    18,    19,    20,
      25,    30,    35,    40,    45,    51,    55,    61,    67,    71,
      77,    83,    87,    93,    97,   102,   105,   107,   110,   114,
     115,   118,   120,   123,   124,   128,   130,   132,   134,   138,
     142,   146,   150,   154,   156,   158,   162,   166,   170,   174,
     178,   182,   186,   190,   194,   198,   202,   206,   210,   214,
     218,   222,   226,   230,   234,   236,   239,   240,   241,   244,
     248,   249,   253,   256,   258,   260,   262,   265,   271,   277,
     278,   284,   290,   295
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      39,     0,    -1,    40,    50,    53,    55,    -1,     3,    41,
       7,    -1,    -1,    42,    -1,    42,    41,    -1,    -1,    -1,
      16,    43,    11,    32,    -1,    17,    43,    11,    32,    -1,
      18,    43,    11,    32,    -1,    19,    43,    11,    32,    -1,
      20,    43,    11,    32,    -1,    16,    11,    33,    48,    32,
      -1,    16,    11,    32,    -1,    17,    11,    33,    48,    32,
      -1,    18,    11,    33,    48,    32,    -1,    18,    11,    32,
      -1,    19,    11,    33,    49,    32,    -1,    19,    11,    33,
      48,    32,    -1,    19,    11,    32,    -1,    20,    11,    33,
      15,    32,    -1,    20,    11,    32,    -1,    45,    33,    48,
      32,    -1,    10,    32,    -1,    44,    -1,    44,    43,    -1,
      34,    12,    35,    -1,    -1,    11,    46,    -1,    47,    -1,
      47,    46,    -1,    -1,    34,    12,    35,    -1,    12,    -1,
      13,    -1,    11,    -1,    48,    21,    48,    -1,    48,    22,
      48,    -1,    48,    23,    48,    -1,    48,    24,    48,    -1,
      36,    48,    37,    -1,    14,    -1,    11,    -1,    12,    26,
      12,    -1,    12,    25,    12,    -1,    12,    28,    12,    -1,
      12,    27,    12,    -1,    12,    31,    12,    -1,    13,    26,
      13,    -1,    13,    25,    13,    -1,    13,    28,    13,    -1,
      13,    27,    13,    -1,    13,    31,    13,    -1,    11,    26,
      11,    -1,    11,    25,    11,    -1,    11,    28,    11,    -1,
      11,    27,    11,    -1,    11,    31,    11,    -1,    49,    29,
      49,    -1,    49,    30,    49,    -1,    36,    49,    37,    -1,
       4,    51,     7,    -1,    52,    -1,    52,    51,    -1,    -1,
      -1,    10,    32,    -1,     5,    54,     7,    -1,    -1,     6,
      56,     7,    -1,    56,    56,    -1,    57,    -1,    58,    -1,
      59,    -1,    10,    32,    -1,     8,    36,    48,    37,    32,
      -1,     8,    36,    49,    37,    32,    -1,    -1,     9,    36,
      48,    37,    32,    -1,     9,    36,    49,    37,    32,    -1,
      11,    33,    48,    32,    -1,    11,    33,    49,    32,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   683,   683,   684,   684,   685,   685,   685,   687,   688,
     689,   690,   691,   692,   693,   694,   695,   696,   697,   698,
     699,   700,   701,   702,   703,   710,   712,   712,   713,   714,
     717,   718,   718,   718,   719,   723,   724,   725,   726,   727,
     728,   729,   730,   734,   735,   736,   737,   738,   739,   740,
     741,   742,   743,   744,   745,   746,   748,   750,   752,   754,
     756,   757,   758,   761,   762,   762,   762,   763,   764,   767,
     768,   770,   771,   771,   771,   771,   771,   773,   774,   775,
     781,   782,   787,   788
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "START_VARS", "START_FUNC", "START_USER",
  "START_MAIN", "END_SECTION", "TYPE_OF", "EVAL", "PRINT_TABLE",
  "IDENTIFIER", "INT_LITERAL", "FLOAT_LITERAL", "BOOLEAN_LITERAL",
  "STRING_LITERAL", "INT", "UINT", "FLOAT", "BOOL", "STR", "ADD", "SUB",
  "MUL", "DIV", "LE", "GT", "LEQ", "GTQ", "AND", "OR", "EQ", "';'", "'='",
  "'['", "']'", "'('", "')'", "$accept", "program", "globalvars",
  "globalvar", "declare", "arraytype", "array", "variable", "brackets",
  "bracket", "expr", "booleanexpr", "funcs", "func", "funcdeclaration",
  "usertypes", "usertype", "main", "block", "typeof", "eval",
  "instruction", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,    59,    61,    91,    93,    40,    41
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    38,    39,    40,    40,    41,    41,    41,    42,    42,
      42,    42,    42,    42,    42,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,    42,    43,    43,    44,    44,
      45,    46,    46,    46,    47,    48,    48,    48,    48,    48,
      48,    48,    48,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    50,    51,    51,    51,    52,    52,    53,
      54,    55,    56,    56,    56,    56,    56,    57,    57,    57,
      58,    58,    59,    59
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     4,     3,     0,     1,     2,     0,     0,     4,
       4,     4,     4,     4,     5,     3,     5,     5,     3,     5,
       5,     3,     5,     3,     4,     2,     1,     2,     3,     0,
       2,     1,     2,     0,     3,     1,     1,     1,     3,     3,
       3,     3,     3,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     2,     0,     0,     2,     3,
       0,     3,     2,     1,     1,     1,     2,     5,     5,     0,
       5,     5,     4,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     7,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     5,     0,     1,    66,     0,    25,     0,    30,
      31,     0,     0,     0,    26,     0,     0,     0,     0,     0,
       0,     0,     0,     3,     6,     0,     0,     0,    64,    70,
       0,     0,    32,    15,     0,     0,     0,    27,     0,     0,
      18,     0,     0,    21,     0,     0,    23,     0,     0,    37,
      35,    36,     0,     0,    68,    63,    65,     0,    79,     2,
      34,     0,    28,     9,     0,    10,     0,    11,    37,    35,
      36,    43,     0,     0,     0,    12,     0,    13,     0,     0,
       0,     0,     0,    24,    69,     0,     0,     0,     0,     0,
      73,    74,    75,    14,    16,    17,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,     0,     0,    19,    22,    42,    38,    39,
      40,    41,     0,     0,    76,     0,    71,    72,    56,    55,
      58,    57,    59,    46,    45,    48,    47,    49,    51,    50,
      53,    52,    54,    62,    44,     0,     0,     0,    60,    61,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      82,    83,    77,    78,    80,    81
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    11,    12,    23,    24,    13,    19,    20,
      88,   121,    16,    37,    38,    40,    67,    69,   137,   100,
     101,   102
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -54
static const yytype_int16 yypact[] =
{
      21,   120,    26,    28,    -2,     2,    -1,     0,     1,     3,
       4,    54,   120,    32,   -54,    71,    84,   -54,    75,   -54,
       2,    -4,    87,    99,    92,    83,   104,     7,   117,    31,
     121,    45,   124,   -54,   -54,    -5,    95,   127,    71,   -54,
     146,   118,   -54,   -54,    -5,   125,   134,   -54,    -5,   135,
     -54,    -5,   148,   -54,    -9,   150,   -54,   144,   151,   -54,
     -54,   -54,    -5,    62,   -54,   -54,   -54,   177,   166,   -54,
     -54,    69,   -54,   -54,    81,   -54,    85,   -54,   116,   123,
     130,   -54,    -9,    97,    82,   -54,   153,   -54,    25,    -5,
      -5,    -5,    -5,   -54,   -54,   152,   154,   155,   156,   162,
     -54,   -54,   -54,   -54,   -54,   -54,   175,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   -12,   -54,     9,     9,   -54,   -54,   -54,    72,    72,
     -54,   -54,    -9,    -9,   -54,    -9,   -54,   166,   -54,   -54,
     -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,   -54,
     -54,   -54,   -54,   -54,   137,   123,   130,     9,   165,   -54,
      29,    30,    51,    39,   101,   149,   169,   176,   178,   179,
     -54,   -54,   -54,   -54,   -54,   -54
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -54,   -54,   -54,   195,   -54,    34,   -54,   -54,   194,   -54,
     -35,   -53,   -54,   171,   -54,   -54,   -54,   -54,   145,   -54,
     -54,   -54
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -45
static const yytype_int16 yytable[] =
{
      63,    84,    78,    79,    80,    81,    59,    60,    61,    71,
      21,    25,    27,    74,    29,    31,    76,   123,   124,    83,
     154,   155,   156,    81,     1,   153,    14,    82,    43,    44,
      17,    62,    15,    22,    22,    22,    18,    22,    22,    50,
      51,    26,    28,    30,    32,   157,    89,    90,    91,    92,
      89,    90,    91,    92,   128,   129,   130,   131,    47,   123,
     124,    33,   127,    53,    54,    35,   166,   167,   123,   124,
     158,   159,    89,    90,    91,    92,   169,    56,    57,   161,
     163,    36,   165,    89,    90,    91,    92,    41,   168,    39,
      89,    90,    91,    92,    93,    91,    92,   160,   162,    45,
     164,   103,    89,    90,    91,    92,    89,    90,    91,    92,
      46,   123,   124,   104,   125,    49,    48,   105,    89,    90,
      91,    92,    89,    90,    91,    92,    22,    64,    52,   122,
       4,     5,    55,   170,    65,    58,     6,     7,     8,     9,
      10,   106,   107,   108,   109,   -44,   -44,   110,   111,   112,
     113,   114,    68,    70,   115,   116,   117,   118,   119,    86,
      72,   120,   106,   107,   108,   109,    73,    75,   110,   136,
      95,    96,    97,    98,    95,    96,    97,    98,   123,   124,
      77,   171,    85,    87,    94,   126,   138,   134,   132,   135,
     133,   139,   140,   141,   142,   124,   143,   144,   145,   146,
     147,   172,   148,   149,   150,   151,   152,    34,   173,    66,
     174,   175,     0,    99,    42
};

static const yytype_int16 yycheck[] =
{
      35,    54,    11,    12,    13,    14,    11,    12,    13,    44,
      11,    11,    11,    48,    11,    11,    51,    29,    30,    54,
      11,    12,    13,    14,     3,    37,     0,    36,    32,    33,
      32,    36,     4,    34,    34,    34,    34,    34,    34,    32,
      33,     7,     8,     9,    10,    36,    21,    22,    23,    24,
      21,    22,    23,    24,    89,    90,    91,    92,    24,    29,
      30,     7,    37,    32,    33,    33,    37,    37,    29,    30,
     123,   124,    21,    22,    23,    24,    37,    32,    33,   132,
     133,    10,   135,    21,    22,    23,    24,    12,    37,     5,
      21,    22,    23,    24,    32,    23,    24,   132,   133,    12,
     135,    32,    21,    22,    23,    24,    21,    22,    23,    24,
      11,    29,    30,    32,    32,    11,    33,    32,    21,    22,
      23,    24,    21,    22,    23,    24,    34,    32,    11,    32,
      10,    11,    11,    32,     7,    11,    16,    17,    18,    19,
      20,    25,    26,    27,    28,    29,    30,    31,    25,    26,
      27,    28,     6,    35,    31,    25,    26,    27,    28,    15,
      35,    31,    25,    26,    27,    28,    32,    32,    31,     7,
       8,     9,    10,    11,     8,     9,    10,    11,    29,    30,
      32,    32,    32,    32,     7,    32,    11,    32,    36,    33,
      36,    11,    11,    11,    11,    30,    12,    12,    12,    12,
      12,    32,    13,    13,    13,    13,    13,    12,    32,    38,
      32,    32,    -1,    68,    20
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    39,    40,    10,    11,    16,    17,    18,    19,
      20,    41,    42,    45,     0,     4,    50,    32,    34,    46,
      47,    11,    34,    43,    44,    11,    43,    11,    43,    11,
      43,    11,    43,     7,    41,    33,    10,    51,    52,     5,
      53,    12,    46,    32,    33,    12,    11,    43,    33,    11,
      32,    33,    11,    32,    33,    11,    32,    33,    11,    11,
      12,    13,    36,    48,    32,     7,    51,    54,     6,    55,
      35,    48,    35,    32,    48,    32,    48,    32,    11,    12,
      13,    14,    36,    48,    49,    32,    15,    32,    48,    21,
      22,    23,    24,    32,     7,     8,     9,    10,    11,    56,
      57,    58,    59,    32,    32,    32,    25,    26,    27,    28,
      31,    25,    26,    27,    28,    31,    25,    26,    27,    28,
      31,    49,    32,    29,    30,    32,    32,    37,    48,    48,
      48,    48,    36,    36,    32,    33,     7,    56,    11,    11,
      11,    11,    11,    12,    12,    12,    12,    12,    13,    13,
      13,    13,    13,    37,    11,    12,    13,    36,    49,    49,
      48,    49,    48,    49,    48,    49,    37,    37,    37,    37,
      32,    32,    32,    32,    32,    32
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 9:

/* Line 1455 of yacc.c  */
#line 688 "test.y"
    {printf("ID [%s]\n", (yyvsp[(3) - (4)].name)); set_value((yyvsp[(3) - (4)].name), "0", "int");;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 689 "test.y"
    {printf("ID [%s]\n", (yyvsp[(3) - (4)].name)); set_value((yyvsp[(3) - (4)].name), "0", "uint");;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 690 "test.y"
    {printf("ID [%s]\n", (yyvsp[(3) - (4)].name));set_value((yyvsp[(3) - (4)].name), "0", "float");;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 691 "test.y"
    {printf("ID [%s]\n", (yyvsp[(3) - (4)].name));set_value((yyvsp[(3) - (4)].name), "false", "bool");;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 692 "test.y"
    {printf("ID [%s]\n", (yyvsp[(3) - (4)].name));set_value((yyvsp[(3) - (4)].name), "", "string");;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 693 "test.y"
    {printf("ID [%s]\n", (yyvsp[(2) - (5)].name)); set_value((yyvsp[(2) - (5)].name), evalAST((yyvsp[(4) - (5)].val)), "int");;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 694 "test.y"
    { printf("ID [%s]\n", (yyvsp[(2) - (3)].name)); set_value((yyvsp[(2) - (3)].name), "0", "int");;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 695 "test.y"
    {printf("ID [%s]\n", (yyvsp[(2) - (5)].name)); set_value((yyvsp[(2) - (5)].name), (yyvsp[(4) - (5)].val), "uint");;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 696 "test.y"
    {printf("ID [%s]\n", (yyvsp[(2) - (5)].name)); set_value((yyvsp[(2) - (5)].name), evalAST((yyvsp[(4) - (5)].val)), "float"); ;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 697 "test.y"
    { printf("ID [%s]\n", (yyvsp[(2) - (3)].name)); set_value((yyvsp[(2) - (3)].name), "0", "float");;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 698 "test.y"
    {printf("ID [%s]\n", (yyvsp[(2) - (5)].name)); set_value((yyvsp[(2) - (5)].name), evalAST((yyvsp[(4) - (5)].nod)), "bool"); ;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 699 "test.y"
    {yyerror("only a bool value can be assigned to bool literal\n"); exit(1);;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 700 "test.y"
    { printf("ID [%s]\n", (yyvsp[(2) - (3)].name)); set_value((yyvsp[(2) - (3)].name), "0", "bool");;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 701 "test.y"
    {printf("ID [%s]\n", (yyvsp[(2) - (5)].name)); set_value((yyvsp[(2) - (5)].name), strdup((yyvsp[(4) - (5)].val)), "string"); ;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 702 "test.y"
    { printf("ID [%s]\n", (yyvsp[(2) - (3)].name)); set_value((yyvsp[(2) - (3)].name), "0", "string");;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 703 "test.y"
    {
    if (strcmp(get_type((yyvsp[(1) - (4)].sym)), "string") == 0)
    {
        yyerror("only a string value can be assigned to a string variable\n");
        exit(1);
    }
    printf("Setting existing value %s, VAR ARR LEN %d: \n", (yyvsp[(1) - (4)].sym), variableArrLen);setExistingValue((yyvsp[(1) - (4)].sym), evalAST((yyvsp[(3) - (4)].val)));;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 710 "test.y"
    { printTable();;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 713 "test.y"
    {printf("Declaring Array of size:%s\n", (yyvsp[(2) - (3)].val)); if((yyvsp[(2) - (3)].val)[0] == '-'){ yyerror("Cannot have array be of negative size!\n"); exit(1);} arraySize[arrLen++] = atoi((yyvsp[(2) - (3)].val));;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 717 "test.y"
    {printf("Atempted to return variable!\n");;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 719 "test.y"
    {printf("Accessing size:%s",(yyvsp[(2) - (3)].val)); variableArraySize[variableArrLen++] = atoi((yyvsp[(2) - (3)].val));;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 723 "test.y"
    {(yyval.val) = buildAST((yyvsp[(1) - (1)].val), NULL, NULL, "int"); ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 724 "test.y"
    { (yyval.val) = buildAST((yyvsp[(1) - (1)].val), NULL, NULL, "float"); ;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 725 "test.y"
    { (yyval.val) = buildAST(get_value((yyvsp[(1) - (1)].name)), NULL, NULL, get_type((yyvsp[(1) - (1)].name))); ;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 726 "test.y"
    { (yyval.val) = buildAST(strdup("+"), (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val), "op");;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 727 "test.y"
    {  (yyval.val) = buildAST(strdup("-"), (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val), "op");;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 728 "test.y"
    {  (yyval.val) = buildAST(strdup("*"), (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val), "op");;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 729 "test.y"
    {  (yyval.val) = buildAST(strdup("/"), (yyvsp[(1) - (3)].val), (yyvsp[(3) - (3)].val), "op");;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 730 "test.y"
    { (yyval.val) = (yyvsp[(2) - (3)].val); ;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 734 "test.y"
    {printf("yytext = %s\n", yytext); (yyval.nod) = buildAST(yytext, NULL, NULL, "bool");;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 735 "test.y"
    { (yyval.nod) = buildAST(get_value((yyvsp[(1) - (1)].name)), NULL, NULL, get_type((yyvsp[(1) - (1)].name)));;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 736 "test.y"
    { (yyval.nod) = buildAST( ((atoi((yyvsp[(1) - (3)].val)) > atoi((yyvsp[(3) - (3)].val)))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 737 "test.y"
    { (yyval.nod) = buildAST( ((atoi((yyvsp[(1) - (3)].val)) < atoi((yyvsp[(3) - (3)].val)))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 738 "test.y"
    { (yyval.nod) = buildAST( ((atoi((yyvsp[(1) - (3)].val)) >= atoi((yyvsp[(3) - (3)].val)))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 739 "test.y"
    { (yyval.nod) = buildAST( ((atoi((yyvsp[(1) - (3)].val)) <= atoi((yyvsp[(3) - (3)].val)))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 740 "test.y"
    { (yyval.nod) = buildAST( ((atoi((yyvsp[(1) - (3)].val)) == atoi((yyvsp[(3) - (3)].val)))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 741 "test.y"
    { (yyval.nod) = buildAST( ((atof((yyvsp[(1) - (3)].val)) > atof((yyvsp[(3) - (3)].val)))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 742 "test.y"
    { (yyval.nod) = buildAST( ((atof((yyvsp[(1) - (3)].val)) < atof((yyvsp[(3) - (3)].val)))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 743 "test.y"
    { (yyval.nod) = buildAST( ((atof((yyvsp[(1) - (3)].val)) >= atof((yyvsp[(3) - (3)].val)))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 744 "test.y"
    { (yyval.nod) = buildAST( ((atof((yyvsp[(1) - (3)].val)) <= atof((yyvsp[(3) - (3)].val)))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 745 "test.y"
    { (yyval.nod) = buildAST( ((atof((yyvsp[(1) - (3)].val)) == atof((yyvsp[(3) - (3)].val)))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 746 "test.y"
    {if (strcmp(get_type((yyvsp[(1) - (3)].name)), get_type((yyvsp[(3) - (3)].name))) == 0) {printf("%s %s\n", get_value((yyvsp[(1) - (3)].name)), get_value((yyvsp[(3) - (3)].name))); char* result = ((atoi(get_value((yyvsp[(1) - (3)].name))) > atoi(get_value((yyvsp[(3) - (3)].name)))) ? strdup("true") : strdup("false")); (yyval.nod) = buildAST(result, (yyvsp[(1) - (3)].name), (yyvsp[(3) - (3)].name), strdup("bool"));} 
                                else {(yyval.nod) = NULL;yyerror("variabilele din expresia booleana nu au acelasi tip");};}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 748 "test.y"
    {if (strcmp(get_type((yyvsp[(1) - (3)].name)), get_type((yyvsp[(3) - (3)].name))) == 0) {printf("%s %s\n", get_value((yyvsp[(1) - (3)].name)), get_value((yyvsp[(3) - (3)].name))); char* result = ((atoi(get_value((yyvsp[(1) - (3)].name))) < atoi(get_value((yyvsp[(3) - (3)].name)))) ? strdup("true") : strdup("false")); (yyval.nod) = buildAST(result, (yyvsp[(1) - (3)].name), (yyvsp[(3) - (3)].name), strdup("bool"));} 
                                else {(yyval.nod) = NULL;yyerror("variabilele din expresia booleana nu au acelasi tip");};}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 750 "test.y"
    {if (strcmp(get_type((yyvsp[(1) - (3)].name)), get_type((yyvsp[(3) - (3)].name))) == 0) {printf("%s %s\n", get_value((yyvsp[(1) - (3)].name)), get_value((yyvsp[(3) - (3)].name))); char* result = ((atoi(get_value((yyvsp[(1) - (3)].name))) >= atoi(get_value((yyvsp[(3) - (3)].name)))) ? strdup("true") : strdup("false")); (yyval.nod) = buildAST(result, (yyvsp[(1) - (3)].name), (yyvsp[(3) - (3)].name), strdup("bool"));} 
                                else {(yyval.nod) = NULL;yyerror("variabilele din expresia booleana nu au acelasi tip");};}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 752 "test.y"
    {if (strcmp(get_type((yyvsp[(1) - (3)].name)), get_type((yyvsp[(3) - (3)].name))) == 0) {printf("%s %s\n", get_value((yyvsp[(1) - (3)].name)), get_value((yyvsp[(3) - (3)].name))); char* result = ((atoi(get_value((yyvsp[(1) - (3)].name))) <= atoi(get_value((yyvsp[(3) - (3)].name)))) ? strdup("true") : strdup("false")); (yyval.nod) = buildAST(result, (yyvsp[(1) - (3)].name), (yyvsp[(3) - (3)].name), strdup("bool"));} 
                                else {(yyval.nod) = NULL;yyerror("variabilele din expresia booleana nu au acelasi tip");};}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 754 "test.y"
    {if (strcmp(get_type((yyvsp[(1) - (3)].name)), get_type((yyvsp[(3) - (3)].name))) == 0) {printf("%s %s\n", get_value((yyvsp[(1) - (3)].name)), get_value((yyvsp[(3) - (3)].name))); char* result = ((atoi(get_value((yyvsp[(1) - (3)].name))) == atoi(get_value((yyvsp[(3) - (3)].name)))) ? strdup("true") : strdup("false")); (yyval.nod) = buildAST(result, (yyvsp[(1) - (3)].name), (yyvsp[(3) - (3)].name), strdup("bool"));} 
                                else {(yyval.nod) = NULL;yyerror("variabilele din expresia booleana nu au acelasi tip");};}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 756 "test.y"
    {(yyval.nod) = buildAST(strdup("&&"), (yyvsp[(1) - (3)].nod), (yyvsp[(3) - (3)].nod), "opb");;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 757 "test.y"
    {(yyval.nod) = buildAST(strdup("||"), (yyvsp[(1) - (3)].nod), (yyvsp[(3) - (3)].nod), "opb");;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 758 "test.y"
    {(yyval.nod) = (yyvsp[(2) - (3)].nod); ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 764 "test.y"
    {printTable();;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 771 "test.y"
    {printTable();;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 773 "test.y"
    {char* type = typeofnode((yyvsp[(3) - (5)].val));evalAST((yyvsp[(3) - (5)].val));printf("Expression has type %s\n", type);;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 774 "test.y"
    {char* type = typeofnode((yyvsp[(3) - (5)].nod));evalAST((yyvsp[(3) - (5)].nod));printf("Expression has type %s\n", type);;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 781 "test.y"
    {printf("Evaluation: %s\n", evalAST((yyvsp[(3) - (5)].val)));;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 782 "test.y"
    {printf("Evaluation: %s\n", evalAST((yyvsp[(3) - (5)].nod)));;}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 787 "test.y"
    {printf("ID [%s]\n", (yyvsp[(1) - (4)].name)); setExistingValue((yyvsp[(1) - (4)].name), evalAST((yyvsp[(3) - (4)].val)));;}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 788 "test.y"
    {printf("ID [%s]\n", (yyvsp[(1) - (4)].name)); setExistingValue((yyvsp[(1) - (4)].name), evalAST((yyvsp[(3) - (4)].nod)));;}
    break;



/* Line 1455 of yacc.c  */
#line 2556 "test.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 789 "test.y"



void yyerror(char *s)
{
    printf("%s\n", s);
}

int main(int argc, char **argv)
{
    yyin = fopen(argv[1], "r");
    yyparse();
    return 0;
}
