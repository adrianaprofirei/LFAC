del a.exe
flex test.l
bison -d test.y
gcc test.tab.c lex.yy.c -w