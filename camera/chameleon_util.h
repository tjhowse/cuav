#ifndef CHAMELEON_UTIL_H_
#define CHAMELEON_UTIL_H_

#include "chameleon.h"

int capture_wait(struct chameleon_camera* c, float* shutter,
		 void* buf, size_t stride, size_t size,
		 int timeout_ms,
		 float *frame_time, uint32_t *frame_counter);

int trigger_capture(struct chameleon_camera* c, float shutter, bool continuous);

struct chameleon_camera *open_camera(bool colour_chameleon, uint8_t depth, uint16_t brightness);

void close_camera(struct chameleon_camera *);

void camera_set_brightness(chameleon_camera_t *camera, uint16_t brightness);
void camera_set_gamma(chameleon_camera_t *camera, uint16_t gamma);

#endif
