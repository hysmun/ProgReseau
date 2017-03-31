
# Si SUN LIBS=-lsocket -lnsl
TMP = "default"
LIBS=
	
all:admin cli ser udplib.o lib2016BM.o
lib2016BM.o: lib2016BM.c lib2016BM.h
	echo "compilation de lib2016"
	gcc -c lib2016BM.c data.h -Wall
admin: data.h admin.c lib2016BM.o
	echo "Compilation de admin"
	gcc -o admin admin.c lib2016BM.o -Wall
udplib.o:../udplib/udplib.h
	echo "Compilation de udplib.o"
	gcc -c ../udplib/udplib.c ../udplib/udplib.c
cli: cli.c structure.h udplib.o
	echo "Compilation de client"
	gcc -o cli cli.c udplib.o $(LIBS) -Wall
ser: ser.c structure.h data.h udplib.o lib2016BM.o
	echo "Compilation de serveur"
	gcc -o ser ser.c udplib.o lib2016BM.o $(LIBS) -Wall
	
	
	
	
clean:
	echo "clean"
	rm -f *.o admin cli ser

git:
	cd .. ; make -f makefile git
