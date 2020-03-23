/***
 Purpose: Assign expression values to variables.
 Expressions can either be addition, subtraction,
 multiplication, or division between integers or
 previously assigned variables. The expressions
 should be in a hierarchy that interprets the 
 order of operations correctly. Be able to return
 the stored value of an assigned variable by calling
 the name as a single line command.
**/

%{
#include <iostream>
#include <map>
#include <cstring>
#include <assert.h>
#include "utils.hpp"

extern "C" int yylex();
extern "C" int yyparse();

void yyerror(const char *s);



Graph program_graph;
std::map<std::string, Layer*> var_to_layer;

%}

/*** union of all possible data return types from grammar ***/
%union {
	int iVal;
	char* sVal;
	struct Layer* lVal;
}


/*** Define token identifiers for flex regex matches ***/
%token ARROW
%token VARNAME
%token LBRACKET RBRACKET
%token ADD FCADD 
%token DELIMITER
%token EQUALS
%token PRINT
%token WS
%token EOL
%token NODE

/*** Define return type for grammar rules ***/
%type<iVal> expr
%type<lVal> vartuple
%type<lVal> to
%type<sVal> DELIMITER 
%type<sVal> VARNAME 
%type<sVal> NODE 
%%

start: expr EOL start { 
	 printf("%i\n\n", $1); 
     } 
     | 
     ;

expr: VARNAME EQUALS vartuple {

     $3->name = std::string($1);
     var_to_layer[std::string($1)] = $3;
     program_graph.add_node($3);
    }
    | PRINT {
      program_graph.make_graph();
    }


vartuple: to {
      }
      | LBRACKET to DELIMITER VARNAME RBRACKET {
        $2->nodelabel = std::string($4);
	$$ = $2;
      }
      | LBRACKET to RBRACKET {
        $$ = $2;
      }


to: NODE {
    Layer* ll = new Layer;
    ll->n_nodes = std::string($1);
    ll->nodelabel= "";
    ll->name= "";
    ll->connected_to_next_by=" ";
    $$ = ll;

}

%%

int main(int argc, char **argv) {
	yyparse();
}

/* Display error messages */
void yyerror(const char *s) {
	printf("ERROR: %s\n", s);
}
