CC = g++
CFLAGS = -Wall -Wextra -std=c++11 # we use C++11 for compatibility on Matrix

app_static: lab2-preet.cpp libPidUtil_Matrix_Version.a
	$(CC) $(CFLAGS) lab2-preet.cpp ./libPidUtil_Matrix_Version.a -o $@

run_static: app_static
	./app_static

clean:
	rm -f app_static