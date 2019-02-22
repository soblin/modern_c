#include "cdplayer.h"

static const State *pCurrentState;
static const State *ignore(const State *self);
static const State *startPlay(const State *self);
static const State *stopPlay(const State *self);
static const State *pausePlay(const State *self);
static const State *resumePlay(const State *self);
static const State *insertCD(const State *self);
static const State *removeCD(const State *self);

const State IDLE_WITHOUT_CD = {
  ignore,
  ignore,
  insertCD
};

const State IDLE_WITH_CD = {
  ignore,
  startPlay,
  removeCD
};

const State PLAY = {
  stopPlay,
  pausePlay,
  removeCD
};

const State PAUSE = {
  stopPlay,
  resumePlay,
  removeCD
};

static const State *ignore(const State *self){
  return pCurrentState;
}

static const State *startPlay(const State *self){
  return &PLAY;
}

static const State *stopPlay(const State *self){
  return &IDLE_WITH_CD;
}

static const State *pausePlay(const State *self){
  return &PAUSE;
}

static const State *resumePlay(const State *self){
  return &PLAY;
}

static const State *insertCD(const State *self){
  return &IDLE_WITH_CD;
}

static const State *removeCD(const State *self){
  return &IDLE_WITHOUT_CD;
}

void initialize(){
  pCurrentState = &IDLE_WITHOUT_CD;
}

void onStop(){
  pCurrentState = pCurrentState->stop(pCurrentState);
}

void onPlayOrPause(){
  pCurrentState = pCurrentState->playOrPause(pCurrentState);
}

void onDisk(){
  pCurrentState = pCurrentState->disk(pCurrentState);
}
