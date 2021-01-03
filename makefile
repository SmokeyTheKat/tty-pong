all:
	gcc ./src/main.c -o ./tty-pong -lm -lpthread
install: all
	sudo cp ./tty-pong /usr/bin/tty-pong
remove:
	sudo rm /usr/bin/tty-pong
