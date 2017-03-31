
# Si SUN LIBS=-lsocket -lnsl
TMP = "default"
LIBS=
all:	admin	lib2016BM.o	 


lib2016BM.o:	lib2016BM.c	lib2016BM.h	data.h	
	echo "compilation de lib2016"
	gcc -c lib2016BM.c

admin:	data.h	admin.c	lib2016BM.o		
	echo "Compilation de admin"
	gcc -o admin	admin.c  lib2016BM.o

git:
	cd .. ; make -f makefile git
