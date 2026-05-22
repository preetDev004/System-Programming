CC=gcc
CFLAGS=-Wall

all: run_syscall run_stdio

foo:
	dd if=/dev/urandom of=foo bs=1000 count=1000

app_syscall: syscall_copy.c
	$(CC) $(CFLAGS) -o app_syscall syscall_copy.c

app_stdio: stdio_copy.c
	$(CC) $(CFLAGS) -o app_stdio stdio_copy.c

run_syscall: app_syscall foo
	./app_syscall

run_stdio: app_stdio foo
	./app_stdio

clean:
	rm -f *.o app_syscall app_stdio bar foo
