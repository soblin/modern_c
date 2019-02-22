#include "cdplayer.h"
#include <stdbool.h>

// これが指しているIDLE, PLAY, PAUSEのどれかが現在の状態
static const State *pCurrentState;

// たんにpCurrentStateの指す先を変えるだけだから、引数いらないのでは
static const State *ignore(const State *This);
static const State *startPlay(const State *This);
static const State *stopPlay(const State *This);
static const State *pausePlay(const State *This);
static const State *resumePlay(const State *This);

const State IDLE = {
  ignore,
  startPlay
};

const State PLAY = {
  stopPlay,
  pausePlay
};

const State PAUSE = {
  stopPlay,
  resumePlay
};

void initialize(){
  pCurrentState = &IDLE;
}

void onStop(){
  pCurrentState = pCurrentState->stop(pCurrentState);
}

void onPlayorPause(){
  pCurrentState = pCurrentState->playOrPause(pCurrentState);
}

static const State *ignore(const State *This){
  return pCurrentState;
}

static const State *startPlay(const State *This){
  return &PLAY;
}

static const State *pausePlay(const State *This){
  return &PAUSE;
}

static const State *resumePlay(const State *This){
  return &PLAY;
}

static const State *stopPlay(const State *This){
  return &IDLE;
}

