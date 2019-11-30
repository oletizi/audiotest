#include <sndfile.h>
#include <soundio/soundio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*	This will be the length of the buffer used to hold.frames while
**	we process them.
*/
#define		BUFFER_LEN	1024

/* libsndfile can handle more than 6 channels but we'll restrict it to 6. */
#define		MAX_CHANNELS	6

/* Function prototype. */
static void process_data (double *data, int count, int channels) ;






static const float PI = 3.1415926535f;
static float seconds_offset = 0.0f;
static void write_callback(struct SoundIoOutStream *outstream,
                           int frame_count_min, int frame_count_max)
{
  const struct SoundIoChannelLayout *layout = &outstream->layout;
  float float_sample_rate = outstream->sample_rate;
  float seconds_per_frame = 1.0f / float_sample_rate;
  struct SoundIoChannelArea *areas;
  int frames_left = frame_count_max;
  int err;

  while (frames_left > 0) {
    int frame_count = frames_left;

    if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count))) {
      fprintf(stderr, "%s\n", soundio_strerror(err));
      exit(1);
    }

    if (!frame_count)
      break;

    float pitch = 440.0f;
    float radians_per_second = pitch * 2.0f * PI;
    for (int frame = 0; frame < frame_count; frame += 1) {
      float sample = sinf((seconds_offset + frame * seconds_per_frame) * radians_per_second);
      for (int channel = 0; channel < layout->channel_count; channel += 1) {
        float *ptr = (float*)(areas[channel].ptr + areas[channel].step * frame);
        *ptr = sample;
      }
    }
    seconds_offset = fmodf(seconds_offset +
                           seconds_per_frame * frame_count, 1.0f);

    if ((err = soundio_outstream_end_write(outstream))) {
      fprintf(stderr, "%s\n", soundio_strerror(err));
      exit(1);
    }

    frames_left -= frame_count;
  }
}

int main(int argc, char **argv) {
  printf("Hello, world!");
  static double data [BUFFER_LEN] ;
  SNDFILE	*infile, *outfile ;
  SF_INFO		sfinfo ;
  int			readcount ;
  const char	*infilename = "resources/input.aif" ;
  const char	*outfilename = "resources/output.wav" ;
  memset (&sfinfo, 0, sizeof (sfinfo)) ;
  if (! (infile = sf_open (infilename, SFM_READ, &sfinfo)))
  {	/* Open failed so print an error message. */
    printf ("Not able to open input file %s.\n", infilename) ;
    /* Print the error message from libsndfile. */
    puts (sf_strerror (NULL)) ;
    return 1 ;
  } ;

  if (sfinfo.channels > MAX_CHANNELS)
  {	printf ("Not able to process more than %d channels\n", MAX_CHANNELS) ;
    return 1 ;
  } ;
  /* Open the output file. */
  if (! (outfile = sf_open (outfilename, SFM_WRITE, &sfinfo)))
  {	printf ("Not able to open output file %s.\n", outfilename) ;
    puts (sf_strerror (NULL)) ;
    return 1 ;
  } ;

  /* While there are.frames in the input file, read them, process
  ** them and write them to the output file.
  */
  while ((readcount = sf_read_double (infile, data, BUFFER_LEN)))
  {	process_data (data, readcount, sfinfo.channels) ;
    sf_write_double (outfile, data, readcount) ;
  } ;

  /* Close input and output files. */
  sf_close (infile) ;
  sf_close (outfile) ;

  return 0 ;
}

static void
process_data (double *data, int count, int channels)
{	double channel_gain [MAX_CHANNELS] = { 0.5, 0.8, 0.1, 0.4, 0.4, 0.9 } ;
  int k, chan ;

  /* Process the data here.
  ** If the soundfile contains more then 1 channel you need to take care of
  ** the data interleaving youself.
  ** Current we just apply a channel dependant gain.
  */

  for (chan = 0 ; chan < channels ; chan ++)
    for (k = chan ; k < count ; k+= channels)
      data [k] *= channel_gain [chan] ;

  return ;
}

/**
int main(int argc, char **argv) {
  int err;
  struct SoundIo *soundio = soundio_create();
  if (!soundio) {
    fprintf(stderr, "out of memory\n");
    return 1;
  }

  if ((err = soundio_connect(soundio))) {
    fprintf(stderr, "error connecting: %s", soundio_strerror(err));
    return 1;
  }

  soundio_flush_events(soundio);

  int default_out_device_index = soundio_default_output_device_index(soundio);
  if (default_out_device_index < 0) {
    fprintf(stderr, "no output device found");
    return 1;
  }

  struct SoundIoDevice *device = soundio_get_output_device(soundio, default_out_device_index);
  if (!device) {
    fprintf(stderr, "out of memory");
    return 1;
  }

  fprintf(stderr, "Output device: %s\n", device->name);

  struct SoundIoOutStream *outstream = soundio_outstream_create(device);
  outstream->format = SoundIoFormatFloat32NE;
  outstream->write_callback = write_callback;

  if ((err = soundio_outstream_open(outstream))) {
    fprintf(stderr, "unable to open device: %s", soundio_strerror(err));
    return 1;
  }

  if (outstream->layout_error)
    fprintf(stderr, "unable to set channel layout: %s\n", soundio_strerror(outstream->layout_error));

  if ((err = soundio_outstream_start(outstream))) {
    fprintf(stderr, "unable to start device: %s", soundio_strerror(err));
    return 1;
  }

  for (;;)
    soundio_wait_events(soundio);

  soundio_outstream_destroy(outstream);
  soundio_device_unref(device);
  soundio_destroy(soundio);
  return 0;
}
**/

