build: 
	gcc -Wall -g functiiL2.c functiihash.c tema1.c -o tema1
run:
	./tema1 10 hash.in hash.out
clean:
	rm -rf *.o tema1