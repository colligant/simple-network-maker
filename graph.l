%{
#include <string>

// Needs to be included before y.tab.h
#include "graph.tab.h"

#define YY_DECL extern "C" int yylex()

%}

/***
 These are the same token rules as before except
 with the addition of a PRINT keyword token for 
 returning variable values. This is preferred
 over the previous method of just having the 
 var name be the return command.
***/

%%

[ \t]            ;

[\n]            { return EOL; }


"print" 		{ return PRINT; }

[a-zA-Z][a-zA-Z0-9]* { yylval.sVal = strdup(yytext); return VARNAME; }

[0-9]*[0-9]+ { yylval.sVal = strdup(yytext); return NODE; } 

"="             { return EQUALS; }
","             { return DELIMITER; }
"+"             { return ADD; }
"++"             { return FCADD; }
"-"             { return ARROW; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }

%%
