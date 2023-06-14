all: build 

build: ping_pong

ping_pong: pong.c
		gcc -Wall -Werror -Wextra pong.c -o pong
		./pong

clean:
		rm ./pong
