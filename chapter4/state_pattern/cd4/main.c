#include "cdplayer.h"
#include <stdlib.h>
#include <time.h>

int main(){
  initialize();
  onDisk(); // insert CD
  srand((unsigned)time(NULL));
  // play!!
  for(int i=0; i<50; ++i){
    if(rand() % 2 == 0) onStop(); // pause
    else onPlayOrPause(); // play or pause
  }
  onDisk(); // remove CD
}
