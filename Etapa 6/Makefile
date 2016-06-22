all:	etapa6

etapa6: lex.yy.o main.o hash.o y.tab.o ast.o semantic.o tac.o genco.o asm.o
	gcc -o etapa6 lex.yy.o main.o hash.o y.tab.o ast.o semantic.o tac.o genco.o asm.o

main.o: main.c lex.yy.c
	gcc -c main.c

hash.o: hash.c
	gcc -c hash.c

ast.o: ast.c
	gcc -c ast.c

lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l y.tab.o
	lex --header-file=lex.yy.h scanner.l

y.tab.o: y.tab.c
	gcc -c y.tab.c

y.tab.c: parser.y
	yacc -d parser.y

semantic.o: semantic.c
	gcc -c semantic.c

tac.o: tac.c
	gcc -c tac.c

genco.o: genco.c
	gcc -c genco.c

asm.o: asm.c
	gcc -c asm.c

clean:
	rm -f lex.yy.c lex.yy.h y.tab.c y.tab.h *.o etapa6
