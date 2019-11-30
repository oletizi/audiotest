//
// Created by Orion Letizi on 11/30/19.
//
#ifndef AUDIOTEST_SNDIO_UTILS_H
#define AUDIOTEST_SNDIO_UTILS_H

void sndio_write_sine(struct SoundIoOutStream *outstream,
                      int frame_count_min, int frame_count_max);
#endif //AUDIOTEST_SNDIO_UTILS_H
