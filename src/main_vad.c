#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sndfile.h>

#include "vad.h"
#include "vad_docopt.h"

#define DEBUG_VAD 0x1
#define N_INIT 1

int main(int argc, char *argv[]) {
  int verbose = 0; /* To show internal state of vad: verbose = DEBUG_VAD; */

  SNDFILE *sndfile_in, *sndfile_out = 0;
  SF_INFO sf_info;
  FILE *vadfile;
  int n_read = 0, i;

  VAD_DATA *vad_data;
  VAD_STATE state, last_state, pre_maybe_state;

  float *buffer, *buffer_zeros;
  int frame_size;         /* in samples */
  float frame_duration;   /* in seconds */
  unsigned int t, last_t, maybe_t; /* in frames */
  float alpha1;

  char	*input_wav, *output_vad, *output_wav;

  DocoptArgs args = docopt(argc, argv, /* help */ 1, /* version */ "2.0");

  verbose    = args.verbose ? DEBUG_VAD : 0;
  input_wav  = args.input_wav;
  output_vad = args.output_vad;
  output_wav = args.output_wav;
  alpha1 = atof(args.alpha1);

  if (input_wav == 0 || output_vad == 0) {
    fprintf(stderr, "%s\n", args.usage_pattern);
    return -1;
  }

  /* Open input sound file */
  if ((sndfile_in = sf_open(input_wav, SFM_READ, &sf_info)) == 0) {
    fprintf(stderr, "Error opening input file %s (%s)\n", input_wav, strerror(errno));
    return -1;
  }

  if (sf_info.channels != 1) {
    fprintf(stderr, "Error: the input file has to be mono: %s\n", input_wav);
    return -2;
  }

  /* Open vad file */
  if ((vadfile = fopen(output_vad, "wt")) == 0) {
    fprintf(stderr, "Error opening output vad file %s (%s)\n", output_vad, strerror(errno));
    return -1;
  }

  /* Open output sound file, with same format, channels, etc. than input */
  if (output_wav) {
    if ((sndfile_out = sf_open(output_wav, SFM_WRITE, &sf_info)) == 0) {
      fprintf(stderr, "Error opening output wav file %s (%s)\n", output_wav, strerror(errno));
      return -1;
    }
  }

  vad_data = vad_open(sf_info.samplerate);
  /* Allocate memory for buffers */
  frame_size   = vad_frame_size(vad_data);
  buffer       = (float *) malloc(frame_size * sizeof(float));
  buffer_zeros = (float *) malloc(frame_size * sizeof(float));
  for (i=0; i< frame_size; ++i) buffer_zeros[i] = 0.0F;

  frame_duration = (float) frame_size/ (float) sf_info.samplerate;
  last_state = ST_INIT;

  for (t = last_t = 0; ; t++) { /* For each frame ... */
    /* End loop when file has finished (or there is an error) */
    if  ((n_read = sf_read_float(sndfile_in, buffer, frame_size)) != frame_size) break;

    if (sndfile_out != 0) {
      /* TODO: copy all the samples into sndfile_out */
      sf_write_float(sndfile_out, buffer, frame_size);
    }

    state = vad(vad_data, buffer/*, alpha1*/);
    printf("%s\n", state2str(state));
    if (verbose & DEBUG_VAD) vad_show_state(vad_data, stdout);

    if(last_state == ST_INIT && state != ST_INIT){
      // vad_data->k0 /= N_INIT;
      // vad_data->k1 = vad_data->k0 + 10;
      last_state = state;
    }

    if(state == (ST_MAYBE_SILENCE || ST_MAYBE_VOICE) && last_state == (ST_SILENCE || ST_VOICE)){  // pass to a maybe
      pre_maybe_state = last_state;
      maybe_t = t;
      // printf("we change the states\n");
    }
      // printf("Pre if: pre_maybe: %s, last_state: %s, state: %s\n", state2str(pre_maybe_state), state2str(last_state), state2str(state));

    if((state == ST_SILENCE || state == ST_VOICE) && (last_state == ST_MAYBE_SILENCE || last_state == ST_MAYBE_VOICE)){ // decide the state of the maybe
      // printf("pre_maybe: %s, last_state: %s, state: %s\n", state2str(pre_maybe_state), state2str(last_state), state2str(state));
      if(pre_maybe_state != state){
        fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, maybe_t * frame_duration, state2str(pre_maybe_state));
        printf("%.5f\t%.5f\t%s\n", last_t * frame_duration, maybe_t * frame_duration, state2str(pre_maybe_state));
        printf("%s\n", state2str(state));
        printf("%s\n", state2str(pre_maybe_state));
        last_t = maybe_t;
      }
    }

    // /* TODO: print only SILENCE and VOICE labels */
    // /* As it is, it prints UNDEF segments but is should be merge to the proper value */
    // if ((state == ST_SILENCE || state == ST_VOICE) && state != last_state) {
    //   if (t != last_t)
    //     fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration, state2str(last_state));
    //   last_state = state;
    //   last_t = t;
    // }

    if (sndfile_out != 0) {
      /* TODO: go back and write zeros in silence segments */
      if (state == ST_SILENCE) {
        int silence_frames = t - last_t; // Number of frames in the silence segment
        int silence_samples = silence_frames * frame_size; // Number of samples in the silence segment
        fseek(sndfile_out, last_t * frame_size * sizeof(float), SEEK_SET); // Seek to the start of the silence segment
        float *zeros_buffer = (float *)malloc(silence_samples * sizeof(float));
        memset(zeros_buffer, 0, silence_samples * sizeof(float)); // Fill the buffer with zeros
        sf_write_float(sndfile_out, zeros_buffer, silence_samples); // Write zeros to the file
        free(zeros_buffer);
      }
    }
    last_state = state;
  }

  state = vad_close(vad_data);
  /* TODO: what do you want to print, for last frames? */
  if (t != last_t)
    fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration + n_read / (float) sf_info.samplerate, state2str(state));

  /* clean up: free memory, close open files */
  free(buffer);
  free(buffer_zeros);
  sf_close(sndfile_in);
  fclose(vadfile);
  if (sndfile_out) sf_close(sndfile_out);
  return 0;
}
