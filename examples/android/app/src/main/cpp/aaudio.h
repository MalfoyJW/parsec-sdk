#pragma once

#include <stdint.h>

struct aaudio;

void aaudio_init(struct aaudio **ctx_out);
void aaudio_destroy(struct aaudio **ctx_out);
void aaudio_play(const int16_t *pcm, uint32_t frames, void *opaque);
