#include "cdplayer.h"
#include <stdlib.h>
#include <time.h>

int main(){
  initialize();
  srand((unsigned)time(NULL));
  for(int i=0; i<50; ++i){
    if(rand() % 2 == 0) onEvent(EV_PLAY_PAUSE);
    else onEvent(EV_STOP);
  }
  return 0;
}
