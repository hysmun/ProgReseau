
# Si SUN LIBS=-lsocket -lnsl
TMP = "default"
LIBS=
	
all:udplib.o lib2016BM.o utils.o admin cli ser 

lib2016BM.o: lib2016BM.c lib2016BM.h
	echo "compilation de lib2016"
	gcc -c lib2016BM.c data.h -Wall
admin: data.h admin.c lib2016BM.o utils.o
	echo "Compilation de admin"
	gcc -o admin admin.c lib2016BM.o utils.o -Wall
udplib.o:../udplib/udplib.h
	echo "Compilation de udplib.o"
	gcc -c ../udplib/udplib.c ../udplib/udplib.c
cli: cli.c structure.h udplib.o utils.o
	echo "Compilation de client"
	gcc -o cli cli.c udplib.o $(LIBS) -Wall
ser: ser.c structure.h data.h udplib.o lib2016BM.o utils.o
	echo "Compilation de serveur"
	gcc -o ser ser.c udplib.o lib2016BM.o utils.o $(LIBS) -Wall
utils.o:utils.c utils.h
	echo "Compilation utils.o"
	gcc -o utils.o -c utils.c -Wall
	
	

ser0:
	./ser 127.0.0.1 1300

cli0:
	./cli 127.0.0.1 1400 127.0.0.1 1300

cli1:
	./cli 127.0.0.1 1401 127.0.0.1 1300

cli2:
	./cli 127.0.0.1 1402 127.0.0.1 1300

cli3:
	./cli 127.0.0.1 1403 127.0.0.1 1300


clean:
	clear
	clear
	echo "clean"
	rm -f *.o admin cli ser

git:
	clear
	clear
	cd .. ; make -f makefile git $(TMP)

pull:
	clear
	clear
	cd ..; git pull
