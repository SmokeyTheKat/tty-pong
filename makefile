#compile the shit yo
install:
	gcc ./src/main.c -o ./main -lm -lpthread
full:
	gcc ./src/main.c -o ./main -lm -lpthread
	cp ./main /usr/bin/ttyPong
remove:
	rm /usr/bin/ttyPong
