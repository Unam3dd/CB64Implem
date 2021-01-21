all:
	gcc -I includes src/base64.c src/main.c -o main.elf -m64
