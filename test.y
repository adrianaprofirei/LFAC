%{
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


%}

/*typedef struct
{
    char* type;
    char* value;
    struct ASTNode* left;
    struct ASTNode* right;
}ASTNode;typedef struct
{
    char* type;
    char* value;
    struct ASTNode* left;
    struct ASTNode* right;
}ASTNode;
*/
%code requires
{
    
}

%union 
{
    char* val;
    char *name;
    int arr;
    int vec[16];
    char** sym;
    struct ASTNode* nod;
}

%start program

%token START_VARS START_FUNC START_USER START_MAIN END_SECTION
%token TYPE_OF EVAL
%token PRINT_TABLE
%token <name> IDENTIFIER
/* %token <nod> IDENTIFIER */
%token <val> INT_LITERAL FLOAT_LITERAL BOOLEAN_LITERAL STRING_LITERAL
%token <name> INT UINT FLOAT BOOL STR
%token <name> ADD SUB MUL DIV
%token <name> LE GT LEQ GTQ AND OR EQ

%type <val> program expr //booleanexpr
%type <nod> booleanexpr
%type <arr> array
%type <sym> variable

%left ADD SUB
%left MUL DIV
%left LE GT LEQ GTQ EQ
%left AND
%left OR

%%
program: globalvars funcs usertypes main;
globalvars: START_VARS globalvar END_SECTION | ;
globalvar: declare |  declare globalvar |;

declare:
  | INT arraytype IDENTIFIER ';'{printf("ID [%s]\n", $3); set_value($3, "0", "int");}
  | UINT arraytype IDENTIFIER ';'{printf("ID [%s]\n", $3); set_value($3, "0", "uint");}
  | FLOAT arraytype IDENTIFIER ';'{printf("ID [%s]\n", $3);set_value($3, "0", "float");} 
  | BOOL arraytype IDENTIFIER ';'{printf("ID [%s]\n", $3);set_value($3, "false", "bool");}
  | STR arraytype IDENTIFIER ';'{printf("ID [%s]\n", $3);set_value($3, "", "string");}
  | INT IDENTIFIER '=' expr ';' {printf("ID [%s]\n", $2); set_value($2, evalAST($4), "int");}
  | INT IDENTIFIER ';' { printf("ID [%s]\n", $2); set_value($2, "0", "int");}
  | UINT IDENTIFIER '=' expr ';' {printf("ID [%s]\n", $2); set_value($2, $4, "uint");}
  | FLOAT IDENTIFIER '=' expr ';' {printf("ID [%s]\n", $2); set_value($2, evalAST($4), "float"); }
  | FLOAT IDENTIFIER ';' { printf("ID [%s]\n", $2); set_value($2, "0", "float");}
  | BOOL IDENTIFIER '=' booleanexpr ';' {printf("ID [%s]\n", $2); set_value($2, evalAST($4), "bool"); }
  | BOOL IDENTIFIER '=' expr ';' {yyerror("only a bool value can be assigned to bool literal\n"); exit(1);}
  | BOOL IDENTIFIER ';' { printf("ID [%s]\n", $2); set_value($2, "0", "bool");}
  | STR IDENTIFIER '=' STRING_LITERAL ';' {printf("ID [%s]\n", $2); set_value($2, strdup($4), "string"); }
  | STR IDENTIFIER ';' { printf("ID [%s]\n", $2); set_value($2, "0", "string");}
  | variable '=' expr ';' {
    if (strcmp(get_type($1), "string") == 0)
    {
        yyerror("only a string value can be assigned to a string variable\n");
        exit(1);
    }
    printf("Setting existing value %s, VAR ARR LEN %d: \n", $1, variableArrLen);setExistingValue($1, evalAST($3));}
  | PRINT_TABLE ';' { printTable();}  ;
  
arraytype: array | array arraytype ;
array:'['INT_LITERAL']' {printf("Declaring Array of size:%s\n", $2); if($2[0] == '-'){ yyerror("Cannot have array be of negative size!\n"); exit(1);} arraySize[arrLen++] = atoi($2);}
    |
    ;

variable: IDENTIFIER brackets {printf("Atempted to return variable!\n");}// /*returnVariable($1)*/;};
brackets: bracket | bracket brackets | ;
bracket: '[' INT_LITERAL ']' {printf("Accessing size:%s",$2); variableArraySize[variableArrLen++] = atoi($2);};


expr:
  INT_LITERAL {$$ = buildAST($1, NULL, NULL, "int"); }
  | FLOAT_LITERAL { $$ = buildAST($1, NULL, NULL, "float"); }
  | IDENTIFIER { $$ = buildAST(get_value($1), NULL, NULL, get_type($1)); }
  | expr ADD expr { $$ = buildAST(strdup("+"), $1, $3, "op");}
  | expr SUB expr {  $$ = buildAST(strdup("-"), $1, $3, "op");}
  | expr MUL expr {  $$ = buildAST(strdup("*"), $1, $3, "op");}
  | expr DIV expr {  $$ = buildAST(strdup("/"), $1, $3, "op");}
  | '(' expr ')' { $$ = $2; }
  ;

booleanexpr:
    BOOLEAN_LITERAL {printf("yytext = %s\n", yytext); $$ = buildAST(yytext, NULL, NULL, "bool");}
    | IDENTIFIER { $$ = buildAST(get_value($1), NULL, NULL, get_type($1));}
    | INT_LITERAL   GT   INT_LITERAL { $$ = buildAST( ((atoi($1) > atoi($3))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));}
    | INT_LITERAL   LE   INT_LITERAL { $$ = buildAST( ((atoi($1) < atoi($3))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));}
    | INT_LITERAL   GTQ  INT_LITERAL { $$ = buildAST( ((atoi($1) >= atoi($3))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));}
    | INT_LITERAL   LEQ  INT_LITERAL { $$ = buildAST( ((atoi($1) <= atoi($3))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));}
    | INT_LITERAL   EQ  INT_LITERAL { $$ = buildAST( ((atoi($1) == atoi($3))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));}
    | FLOAT_LITERAL GT   FLOAT_LITERAL { $$ = buildAST( ((atof($1) > atof($3))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));}
    | FLOAT_LITERAL LE   FLOAT_LITERAL { $$ = buildAST( ((atof($1) < atof($3))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));}
    | FLOAT_LITERAL GTQ  FLOAT_LITERAL { $$ = buildAST( ((atof($1) >= atof($3))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));}
    | FLOAT_LITERAL LEQ  FLOAT_LITERAL { $$ = buildAST( ((atof($1) <= atof($3))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));}
    | FLOAT_LITERAL EQ  FLOAT_LITERAL { $$ = buildAST( ((atof($1) == atof($3))?(strdup("true")):(strdup("false"))), NULL, NULL, strdup("bool"));}
    | IDENTIFIER GT IDENTIFIER {if (strcmp(get_type($1), get_type($3)) == 0) {printf("%s %s\n", get_value($1), get_value($3)); char* result = ((atoi(get_value($1)) > atoi(get_value($3))) ? strdup("true") : strdup("false")); $$ = buildAST(result, $1, $3, strdup("bool"));} 
                                else {$$ = NULL;yyerror("variabilele din expresia booleana nu au acelasi tip");}}
    | IDENTIFIER LE   IDENTIFIER {if (strcmp(get_type($1), get_type($3)) == 0) {printf("%s %s\n", get_value($1), get_value($3)); char* result = ((atoi(get_value($1)) < atoi(get_value($3))) ? strdup("true") : strdup("false")); $$ = buildAST(result, $1, $3, strdup("bool"));} 
                                else {$$ = NULL;yyerror("variabilele din expresia booleana nu au acelasi tip");}}
    | IDENTIFIER GTQ  IDENTIFIER {if (strcmp(get_type($1), get_type($3)) == 0) {printf("%s %s\n", get_value($1), get_value($3)); char* result = ((atoi(get_value($1)) >= atoi(get_value($3))) ? strdup("true") : strdup("false")); $$ = buildAST(result, $1, $3, strdup("bool"));} 
                                else {$$ = NULL;yyerror("variabilele din expresia booleana nu au acelasi tip");}}
    | IDENTIFIER LEQ  IDENTIFIER {if (strcmp(get_type($1), get_type($3)) == 0) {printf("%s %s\n", get_value($1), get_value($3)); char* result = ((atoi(get_value($1)) <= atoi(get_value($3))) ? strdup("true") : strdup("false")); $$ = buildAST(result, $1, $3, strdup("bool"));} 
                                else {$$ = NULL;yyerror("variabilele din expresia booleana nu au acelasi tip");}}
    | IDENTIFIER EQ  IDENTIFIER {if (strcmp(get_type($1), get_type($3)) == 0) {printf("%s %s\n", get_value($1), get_value($3)); char* result = ((atoi(get_value($1)) == atoi(get_value($3))) ? strdup("true") : strdup("false")); $$ = buildAST(result, $1, $3, strdup("bool"));} 
                                else {$$ = NULL;yyerror("variabilele din expresia booleana nu au acelasi tip");}}
    | booleanexpr AND booleanexpr {$$ = buildAST(strdup("&&"), $1, $3, "opb");}                
    | booleanexpr OR booleanexpr {$$ = buildAST(strdup("||"), $1, $3, "opb");}
    | '(' booleanexpr ')' {$$ = $2; }
    ;

funcs: START_FUNC func END_SECTION;
func: funcdeclaration | funcdeclaration func | ;
funcdeclaration: ;
    | PRINT_TABLE ';' {printTable();}


usertypes:START_USER usertype END_SECTION;
usertype: ;

main:START_MAIN block END_SECTION;
block: block block | typeof | eval | instruction | PRINT_TABLE ';' {printTable();};
typeof:
    TYPE_OF '(' expr ')' ';' {char* type = typeofnode($3);evalAST($3);printf("Expression has type %s\n", type);}
    | TYPE_OF '(' booleanexpr ')' ';' {char* type = typeofnode($3);evalAST($3);printf("Expression has type %s\n", type);}
    |
    ;

/* typeof: TYPE_OF '(' typeofexpr ')';
typeofexpr : expr | booleanexpr; */
eval:
    EVAL '(' expr ')' ';' {printf("Evaluation: %s\n", evalAST($3));}
    | EVAL '(' booleanexpr ')' ';' {printf("Evaluation: %s\n", evalAST($3));};


/* typeofexpr: expr | booleanexpr; */
instruction:
    IDENTIFIER '=' expr ';' {printf("ID [%s]\n", $1); setExistingValue($1, evalAST($3));}
    | IDENTIFIER '=' booleanexpr ';' {printf("ID [%s]\n", $1); setExistingValue($1, evalAST($3));};
%%


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