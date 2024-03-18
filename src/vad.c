#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "vad.h"
#include "pav_analysis.h"

const float FRAME_TIME = 10.0F; /* in ms. */
unsigned int long_state = 0;
int initial = 0;

/* 
 * As the output state is only ST_VOICE, ST_SILENCE, or ST_UNDEF,
 * only this labels are needed. You need to add all labels, in case
 * you want to print the internal state in string format
 */

const char *state_str[] = {
  "UNDEF", "S", "V", "INIT", "MS", "MV"
};

const char *state2str(VAD_STATE st) {
  return state_str[st];
}

/* Define a datatype with interesting features */
typedef struct {
  float zcr;
  float p;
  float am;
} Features;

/* 
 * TODO: Delete and use your own features!
 */

Features compute_features(const float *x, int N, const float sampling_rate) {
  /*
   * Input: x[i] : i=0 .... N-1 
   * Ouput: computed features
   */
  /* 
   * DELETE and include a call to your own functions
   *
   * For the moment, compute random value between 0 and 1 
   */
  Features feat;
  feat.p = compute_power(x, N);
  feat.am = compute_am(x, N);
  feat.zcr = compute_zcr(x, N, sampling_rate);
  return feat;
}

/* 
 * TODO: Init the values of vad_data
 */

VAD_DATA * vad_open(float rate) {
  VAD_DATA *vad_data = malloc(sizeof(VAD_DATA));
  // if (vad_data == NULL) {                                              -> not sure
  //   fprintf(stderr, "Error: Memory allocation failed in vad_open\n");
  //   exit(EXIT_FAILURE);
  // }
  vad_data->state = ST_INIT;
  vad_data->sampling_rate = rate;
  vad_data->frame_length = rate * FRAME_TIME * 1e-3;
  vad_data->min_s = 10;
  vad_data->min_v = 10;
  return vad_data;
}

VAD_STATE vad_close(VAD_DATA *vad_data) {
  /* 
   * TODO: decide what to do with the last undecided frames
   */
  VAD_STATE state = vad_data->state;

  free(vad_data);
  return state;
}

unsigned int vad_frame_size(VAD_DATA *vad_data) {
  return vad_data->frame_length;
}

/* 
 * TODO: Implement the Voice Activity Detection 
 * using a Finite State Automata
 */

VAD_STATE vad(VAD_DATA *vad_data, float *x/*, float alpha1*/) {

  /* 
   * TODO: You can change this, using your own features,
   * program finite state automaton, define conditions, etc.
   */

  Features f = compute_features(x, vad_data->frame_length, vad_data->sampling_rate);
  vad_data->last_feature = f.p; // save feature, in case you want to show 
  VAD_STATE actual_state = vad_data->state;

  switch (vad_data->state) {
  case ST_INIT:
    vad_data->k0 = f.p;
    vad_data->k1 = vad_data->k0 + 5;
    vad_data->state = ST_SILENCE;

  case ST_SILENCE:
    // if (long_state < 5 && initial == 0) {
    //   vad_data->k0 += f.p;
    //   if (long_state == 4) {
    //     vad_data->k0 /= 5;
    //     vad_data->k1 = vad_data->k0 + 5;
    //     initial = 1;
    //   }
    // } 
    if (f.p > vad_data->k1)
      vad_data->state = ST_MAYBE_VOICE;
      // if (initial == 0) {
      //   vad_data->k0 /= long_state+1;
      //   vad_data->k1 = vad_data->k0 + 5;
      //   initial = 1;
      // }
      
    break;

  case ST_MAYBE_VOICE:
    if (f.p > vad_data->k1 && long_state > vad_data->min_v)
      vad_data->state = ST_VOICE;
    else if (f.p < vad_data->k1)
      vad_data->state = ST_SILENCE;
    break;

  case ST_VOICE:
    // printf("ST_VOICE\n");
    if (f.p < vad_data->k1)
      vad_data->state = ST_MAYBE_SILENCE;
    break;

  case ST_MAYBE_SILENCE:
    // printf("ST_MAYBE_SILENCE\n");
    if (f.p < vad_data->k1 && long_state > vad_data->min_s)
      vad_data->state = ST_SILENCE;
    else if (f.p > vad_data->k1)
      vad_data->state = ST_VOICE;
    break;

  // case ST_UNDEF:

  }

  if(actual_state != vad_data->state){
    long_state = 1;
  } else {
    long_state++;
  }

  return vad_data->state;
  // else
  //   return ST_UNDEF;

  /*Features f = compute_features(x, vad_data->frame_length, vad_data->sampling_rate);
  vad_data->last_feature = f.p; // save feature, in case you want to show 

  switch (vad_data->state) {
  case ST_INIT:
    vad_data->p0 = f.p;
    vad_data->state = ST_SILENCE;
    break;

  case ST_SILENCE:
    if (f.p > -25)
      vad_data->state = ST_VOICE;
    break;

  case ST_VOICE:
    if (f.p < -25)
      vad_data->state = ST_SILENCE;
    break;

  case ST_UNDEF:
    break;
  }

  if (vad_data->state == ST_SILENCE ||
      vad_data->state == ST_VOICE)
    return vad_data->state;
  else
    return ST_UNDEF;*/
}

void vad_show_state(const VAD_DATA *vad_data, FILE *out) {
  fprintf(out, "%d\t%f\n", vad_data->state, vad_data->last_feature);
}
