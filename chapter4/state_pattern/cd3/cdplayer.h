#ifndef CDPLAYER_H_
#define CDPLAYER_H_

typedef struct _State{
  const struct _State *(*stop)(const struct _State *This);
  const struct _State *(*playOrPause)(const struct _State *This);
} State;

void initialize();
void onStop();
void onPlayorPause();

#endif
