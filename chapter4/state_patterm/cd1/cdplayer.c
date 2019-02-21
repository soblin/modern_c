#include <stdbool.h>
#include "cdplayer.h"

bool playflag;
bool pauseflag;

void initialize(){
  playflag = false;
  pauseflag = false;
}

void onEvent(EventCode ec){
  switch(ec){
    case EV_STOP:
      if(playflag == true || pauseflag == true)
        stopPlayer();
      break;

    case EV_PLAY_PAUSE:
      if(playflag == true) pausePlayer();
      else if(pauseflag == true) resumePlayer();
      else startPlayer();
      break;

    default:
      break;
  }
}

void stopPlayer(){
  pauseflag = false;
  playflag = false;
}

void pausePlayer(){
  pauseflag = true;
  playflag = false;
}

void resumePlayer(){
  pauseflag = false;
  playflag = true;
}

void startPlayer(){
  pauseflag = false;
  playflag = true;
}
