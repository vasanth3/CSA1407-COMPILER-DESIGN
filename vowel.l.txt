%{
int vcount=0;
int ccount=0;
%}
%%
[aeiouAEIOU] {vcount++;}
[a-z,A-Z] {ccount++;}
%%
int yywrap(){}
int main()
{
printf("enter the string with vowels and consonants:");
yylex();
printf("\n no of vowels ::%d \n",vcount);
printf("\n no of consonants ::%d \n",ccount);
}
