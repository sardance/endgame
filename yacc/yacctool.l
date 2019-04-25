%{
    #include<stdio.h>
    #include"y.tab.h"
    #include<stdlib.h>
    void yyerror(char *s);
%}
%%
[0-9]+   {
              yylval=atoi(yytext);
              return INTEGER;
             }
[-+*/\n]  {
          return *yytext;
         }
[ \t]       ;
.           yyerror("Unknown Character");
%%
int yywrap(void)
{return 1;}

