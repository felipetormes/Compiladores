


%%

"for"		{printf("Achei um for");}


%%

int yywrap()
{
return 1;
}

int main(){
yylex();
}
