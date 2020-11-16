default:
	bison -dv TheParser.y
	flex lextest.l
	gcc -o  Analyzer TheParser.tab.c lex.yy.c

clean:
	rm lex.yy.c TheParser.tab.c TheParser.tab.h Analyzer 
	ls -l 


	