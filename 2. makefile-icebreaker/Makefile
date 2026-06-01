# Minimal Makefile: static vs shared (single folder)
CC = gcc
CFLAGS = -Wall -Wextra -O2

all: run_static

# Build objects (PIC so they work for shared too; OK for static)
add.o: add.c math.h
	$(CC) $(CFLAGS) -fPIC -c add.c

# Static library (archive)
libmath.a: add.o
	ar rcs $@ $^

# Shared library
libmath.so: add.o
	$(CC) -shared -o $@ $^

# Link apps — use explicit file paths to avoid ambiguity
app_static: main.c libmath.a math.h
	$(CC) $(CFLAGS) main.c ./libmath.a -o $@

# rpath makes the loader look in the app's folder for libmath.so
app_shared: main.c libmath.so math.h
	$(CC) $(CFLAGS) main.c -L. -lmath -Wl,-rpath,'$$ORIGIN' -o $@

run_static: app_static
	./app_static 6 7

run_shared: app_shared
	./app_shared 6 7

clean:
	rm -f *.o *.a *.so app_static app_shared
