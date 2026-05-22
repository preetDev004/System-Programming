#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define BSIZE 16384

int main(){
  FILE *fin, *fout;
  char buf[BSIZE];
  int count;

  struct timeval start, end;
  gettimeofday(&start, NULL);

    if ((fin = fopen("foo", "rb")) == NULL) {
    perror("foo");
    exit(1);
  }
  if ((fout = fopen("bar", "wb")) == NULL) {
    perror("bar");
    exit(2);
  }
  while ((count = fread(buf, 1, BSIZE, fin)) > 0)
    fwrite(buf, 1, count, fout);
 
  fclose(fin);

  fclose(fout);
  gettimeofday(&end, NULL);
  double elapsed = (end.tv_sec - start.tv_sec) * 1000.0 +
                   (end.tv_usec - start.tv_usec) / 1000.0;
  printf("[stdio] Copy complete. Time: %.4f ms\n", elapsed);
  return 0;
}
