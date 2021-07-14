all: rmo lso dateo mkdiro cato 
	gcc shell.c
	./a.out
rmo: 
	gcc rm.c -o rmo
lso:
	gcc ls.c -o lso
dateo:
	gcc date.c -o dateo
mkdiro:
	gcc mkdir.c -o mkdiro
cato:
	gcc cat.c -o cato
clean:
	rm rmo lso dateo mkdiro cato a.out


