//
// Created by Orion Letizi on 11/30/19.
//

#ifndef AUDIOTEST_SNDFILE_UTILS_H
#define AUDIOTEST_SNDFILE_UTILS_H
#include <string.h>
#include <sndfile.h>
/*	This will be the length of the buffer used to hold.frames while
**	we process them.
*/
#define    BUFFER_LEN  1024

/* libsndfile can handle more than 6 channels but we'll restrict it to 6. */
#define    MAX_CHANNELS  6

/* Function prototype. */
void sndfile_copy_buffer(double *data, int count, int channels);

int sndfile_copy_file(const char *infilename, const char *outfilename);



#endif //AUDIOTEST_SNDFILE_UTILS_H
