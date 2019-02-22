#ifndef CDPLAYER_H_
#define CDPLAYER_H_

typedef struct State_{
  const struct State_ *(*const stop)(const struct State_ *self);
  const struct State_ *(*const playOrPause)(const struct State_ *self);
  const struct State_ *(*const disk)(const struct State_ *self);
} State;

void initialize();
void onStop();
void onPlayOrPause();
void onDisk();

#endif
