#ifndef CDPLAYER_H_
#define CDPLAYER_H_

typedef enum{
  EV_STOP,
  EV_PLAY_PAUSE
} EventCode;

void initialize();
void onEvent(EventCode ec);
void stopPlayer();
void pausePlayer();
void resumePlayer();
void startPlayer();

#endif
