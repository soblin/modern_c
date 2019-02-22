#ifndef CDPLAYER_H_
#define CDPLAYER_H_

#ifdef __cplusplus
extern "C"{
#endif

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
  
#ifdef __cplusplus
}
#endif

#endif
