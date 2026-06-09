CC=g++
CFLAGS=-I
CFLAGS+=-Wall
FILES1=sysMonExec.cpp
FILES2=intfMonitor.cpp

sysMonExec: $(FILES1)
	$(CC) $(CFLAGS) -o sysMonExec $(FILES1)

intfMonitor: $(FILES2)
	$(CC) $(CFLAGS) -o intfMonitor $(FILES2)

clean:
	rm -f *.o sysMonExec intfMonitor

all: sysMonExec intfMonitor
