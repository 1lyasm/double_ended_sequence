c:
	clang -g -Weverything -fsanitize=address src/main.c -o main
runc:
	./main
py:
	python3 src/main.py
