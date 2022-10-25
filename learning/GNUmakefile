prog=main

include ../GNUmakefile

try: main.o libdeq.so
	gcc -o $@ $< -L. -lmain -Wl,-rpath=.
