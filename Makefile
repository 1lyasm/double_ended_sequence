all:
	clang -g -Weverything -fsanitize=address src/main.c -o main
run:
	./main
