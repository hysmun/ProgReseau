#.SILENT:
TMP = "default"
ALLOBJ=

	
#special compiler tout les cpp
%.o: %.c
	clear
	clear
	echo $@
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	clear
	clear
	echo clean
	rm -f -r *.o *~


git:
	clear
	clear
	git add -A
	git commit -m "$(TMP)"
	git push
















