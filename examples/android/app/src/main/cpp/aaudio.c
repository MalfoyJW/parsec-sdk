#include "aaudio.h"

#include <stdbool.h>
#include <stdlib.h>

#include <aaudio/AAudio.h>
#include <android/log.h>

struct aaudio {
    AAudioStreamBuilder *builder;
    AAudioStream *stream;
    int32_t last_underruns;
};

static void aaudio_errorcallback(AAudioStream *stream, void *userData, aaudio_result_t error)
{
    __android_log_print(ANDROID_LOG_INFO, "PARSEC", "aaudio error %d", error);
}

void aaudio_init(struct aaudio **ctx_out)
{
    struct aaudio *ctx = *ctx_out = calloc(1, sizeof(struct aaudio));

    AAudio_createStreamBuilder(&ctx->builder);
    AAudioStreamBuilder_setDeviceId(ctx->builder, AAUDIO_UNSPECIFIED);
    AAudioStreamBuilder_setSampleRate(ctx->builder, 48000);
    AAudioStreamBuilder_setChannelCount(ctx->builder, 2);
    AAudioStreamBuilder_setFormat(ctx->builder, AAUDIO_FORMAT_PCM_I16);
    AAudioStreamBuilder_setPerformanceMode(ctx->builder, AAUDIO_PERFORMANCE_MODE_LOW_LATENCY);
    AAudioStreamBuilder_setErrorCallback(ctx->builder, aaudio_errorcallback, NULL);

    // Optional:
    // AAudioStreamBuilder_setBufferCapacityInFrames(ctx->builder, ???);            // Use this function if you want a larger buffer
    // AAudioStreamBuilder_setUsage(ctx->builder, AAUDIO_USAGE_GAME);               // Added in Pie
    // AAudioStreamBuilder_setContentType(ctx->builder, AAUDIO_CONTENT_TYPE_MUSIC); // Added in Pie

    AAudioStreamBuilder_openStream(ctx->builder, &ctx->stream);
}

void aaudio_destroy(struct aaudio **ctx_out)
{
    if (!ctx_out || !*ctx_out)
        return;

    struct aaudio *ctx = *ctx_out;

    if (ctx->stream) {
        AAudioStream_requestStop(ctx->stream);
        AAudioStream_close(ctx->stream);
    }

    if (ctx->builder)
        AAudioStreamBuilder_delete(ctx->builder);

    free(ctx);
    *ctx_out = NULL;
}

void aaudio_play(const int16_t *pcm, uint32_t frames, void *opaque)
{
    struct aaudio *ctx = (struct aaudio *) opaque;

    AAudioStream_write(ctx->stream, pcm, frames, 40000000); // 40ms

    int32_t underruns = AAudioStream_getXRunCount(ctx->stream);
    int32_t state = AAudioStream_getState(ctx->stream);

    if (underruns > ctx->last_underruns || state != AAUDIO_STREAM_STATE_STARTED) {
        AAudioStream_requestStop(ctx->stream);
        AAudioStream_requestStart(ctx->stream);
        ctx->last_underruns = underruns;
    }
}
