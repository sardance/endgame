%{ 
  int key=0,op=0,relop=0,id=0;
%}
letter [a-zA-Z]
digit [0-9]
%%
(if|else|while|do) {key++; printf("%s",yytext);}
("+"|"*"|"-"|"/"|"=") {op++; printf("%s",yytext);}
("<="|"<"|">"|">=") {relop++; printf("%s",yytext);}
{letter}({letter}|{digit})* {id++; printf("%s",yytext);}
%%
main()
{
 yylex();
 printf("ids=%d\n",id);
 printf("ops=%d\n",op);
 printf("relops=%d\n",relop);
 printf("keywords=%d\n",key);
}

