etapa6: y.tab.o lex.yy.o hash.o astree.o semantic.o tac.o assembly.o main.o
	gcc -o etapa6 y.tab.o lex.yy.o hash.o astree.o semantic.o tac.o assembly.o main.o -lm

main.o: main.c
	gcc -c main.c

assembly.o: assembly.c
	gcc -c assembly.c -lm

tac.o: tac.c
	gcc -c tac.c

semantic.o: semantic.c
	gcc -c semantic.c

astree.o:
	gcc -c astree.c

hash.o: hash.c
	gcc -c hash.c

y.tab.o: y.tab.c lex.yy.h
	gcc -c y.tab.c

y.tab.c: parser.y
	yacc -d -v parser.y

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.h: scanner.l
	flex --header-file=lex.yy.h scanner.l

lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l

clean:
	rm *.o lex.yy.c y.tab.c lex.yy.h y.tab.h y.output etapa6
