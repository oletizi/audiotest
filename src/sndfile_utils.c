#include "sndfile_utils.h"

void sndfile_copy_buffer(double *data, int count, int channels) {
  double channel_gain[MAX_CHANNELS] = {0.5, 0.8, 0.1, 0.4, 0.4, 0.9};
  int k, chan;

  /* Process the data here.
  ** If the soundfile contains more then 1 channel you need to take care of
  ** the data interleaving youself.
  ** Current we just apply a channel dependant gain.
  */

  for (chan = 0; chan < channels; chan++)
    for (k = chan; k < count; k += channels)
      data[k] *= channel_gain[chan];
}

int sndfile_copy_file(const char *infilename, const char *outfilename) {
  static double data[BUFFER_LEN];
  SNDFILE *infile, *outfile;
  SF_INFO sfinfo;
  int readcount;
  memset (&sfinfo, 0, sizeof(sfinfo));
  if (!(infile = sf_open(infilename, SFM_READ, &sfinfo))) {  /* Open failed so print an error message. */
    printf("Not able to open input file %s.\n", infilename);
    /* Print the error message from libsndfile. */
    puts(sf_strerror(NULL));
    return 1;
  };

  if (sfinfo.channels > MAX_CHANNELS) {
    printf("Not able to process more than %d channels\n", MAX_CHANNELS);
    return 1;
  };
  /* Open the output file. */
  if (!(outfile = sf_open(outfilename, SFM_WRITE, &sfinfo))) {
    printf("Not able to open output file %s.\n", outfilename);
    puts(sf_strerror(NULL));
    return 1;
  };

  /* While there are.frames in the input file, read them, process
  ** them and write them to the output file.
  */
  while ((readcount = sf_read_double(infile, data, BUFFER_LEN))) {
    sndfile_copy_buffer(data, readcount, sfinfo.channels);
    sf_write_double(outfile, data, readcount);
  };

  /* Close input and output files. */
  sf_close(infile);
  sf_close(outfile);

  return 0;
}