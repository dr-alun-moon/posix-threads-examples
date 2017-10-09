# makefie
all: fork_ex thread_ex summation

fork_ex: fork_ex.c
	cc -o fork_ex fork_ex.c

thread_ex: thread_ex.c
	cc -o thread_ex thread_ex.c -pthread

summation: summation.c
	cc -o summation summation.c -pthread

.PHONY: clean
clean:
	rm -f thread_ex
	rm -f fork_ex
	rm -f summation
