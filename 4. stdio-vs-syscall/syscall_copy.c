#include <stdio.h>    
#include <unistd.h>   
#include <fcntl.h>
#include <stdlib.h>
#include <sys/time.h>

#define BSIZE 16384

int main(){
  int fin, fout;
  char buf[BSIZE];
  int count;

  struct timeval start, end;
  gettimeofday(&start, NULL);

  if ((fin = open("foo", O_RDONLY)) < 0) {
    perror("foo");
    exit(1);
  }

  if ((fout = open("bar", O_WRONLY | O_CREAT, 0644)) < 0) {
    perror("bar");
    exit(2);
  }

  while ((count = read(fin, buf, BSIZE)) > 0)
    write(fout, buf, count);

  close(fin);
  close(fout);
    gettimeofday(&end, NULL);
  double elapsed = (end.tv_sec - start.tv_sec) * 1000.0 +
                   (end.tv_usec - start.tv_usec) / 1000.0;
  printf("[syscall] Copy complete. Time: %.4f ms\n", elapsed);
  return 0;
}
