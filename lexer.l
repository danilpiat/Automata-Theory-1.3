%{
#include <iostream>
%}

%option noyywrap c++
%option outfile="scanner.cpp" 

%x ERROR SERVER ZONE STR
%{
	#include <string>
	#include <iostream>
	std::string zone;
    using namespace std;
%}

%%
<INITIAL>
{
	((http\:\/\/)([a-zA-Z0-9]{1,20}\.)([a-zA-Z0-9]{1,20}\.))|((www\.)([a-zA-Z0-9]{1,20}\.))  { BEGIN(ZONE); }
	.? { BEGIN(ERROR); }
}
<ZONE>
{
	([a-zA-Z]{1,5}) { zone = std::string(yytext); yyout << zone; BEGIN(STR);}
	.? { BEGIN(ERROR); }
}
<STR>
{
	([ \n]+) {return 1;}
	.? { BEGIN(ERROR); }
}
<ERROR>
{
	.? { BEGIN(INITIAL); return 0; }
}
%%
