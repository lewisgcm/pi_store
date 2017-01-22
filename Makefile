all:
	clang -I include src/*.c -o test -l gmp
