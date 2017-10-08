# makefie
all: fork_ex thread_ex

fork_ex: fork_ex.c
	$(CC) -o fork_ex fork_ex.c

thread_ex: thread_ex.c
		$(CC) -o thread_ex thread_ex.c -pthread

.PHONY: clean
clean:
	rm -f thread_ex
	rm -f fork_ex
