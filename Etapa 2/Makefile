
etapa2:  y.tab.o hash.o main.o lex.yy.o
		gcc lex.yy.o hash.o main.o y.tab.o -o etapa2
		
y.tab.o: y.tab.c
		gcc -c y.tab.c
		
y.tab.c: parser.y
		yacc -d parser.y
		
lex.yy.o: lex.yy.c
		  gcc -c lex.yy.c

hash.o: hash.c
		gcc -c hash.c

main.o: main.c
		gcc -c main.c

lex.yy.c: scanner.l
		  lex --header-file=lex.yy.h scanner.l

clean:
		rm etapa2 lex.yy.c y.tab.c y.tab.h *.o
