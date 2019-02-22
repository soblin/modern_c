#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  FILE *fp = fopen("toydata.txt", "w");
  if(fp == NULL) exit(1);

  srand((unsigned)time(NULL));
  const int range = 101;
  const int min = -50;
  const int max = 50;
  for(int i=0; i<range; ++i){
    int number = (rand() % range) + min;
    fprintf(fp, "%d\n", number);
  }
  fclose(fp);
  return 0;
}
