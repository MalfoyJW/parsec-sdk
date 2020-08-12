#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>

#include <EGL/egl.h>
#include <GLES/gl.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "aaudio.h"
#include "parsec.h"

#define TIMEOUT 250

struct ImplementationContext {
    pthread_t videoThread;
    pthread_t audioThread;
    ANativeWindow *window;
    Parsec *parsec;
    struct aaudio *aaudio;
    bool running;
};

static void *getPointer(JNIEnv *env, jobject instance, const char *name)
{
    jclass cls = (*env)->GetObjectClass(env, instance);
    jfieldID id = (*env)->GetFieldID(env, cls, name, "J");
    return (void *) (*env)->GetLongField(env, instance, id);
}

static void setPointer(JNIEnv *env, jobject instance, const char *name, void *ptr)
{
    jclass cls = (*env)->GetObjectClass(env, instance);
    jfieldID id = (*env)->GetFieldID(env, cls, name, "J");
    (*env)->SetLongField(env, instance, id, (long) ptr);
}

static bool preRender(void *opaque)
{
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    return true;
}

static void *renderVideo(void *opaque)
{
    struct ImplementationContext *ctx = (struct ImplementationContext *)opaque;

    if (ctx->window == NULL) return NULL;

    const EGLint attribs[] = {
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_RED_SIZE, 8,
        EGL_NONE
    };

    EGLint contextConfig[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};

    EGLDisplay display;
    EGLint majorVersion;
    EGLint minorVersion;
    EGLConfig config;
    EGLint numConfigs;
    EGLint format;
    EGLSurface surface;
    EGLContext context;

    if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY)
        return NULL;

    if (!eglInitialize(display, &majorVersion, &minorVersion))
        return NULL;

    if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs))
        return NULL;

    if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format))
        return NULL;

    ANativeWindow_setBuffersGeometry(ctx->window, 0, 0, format);

    if (!(surface = eglCreateWindowSurface(display, config, ctx->window, 0)))
        return NULL;

    if (!(context = eglCreateContext(display, config, 0, contextConfig)))
        return NULL;

    if (!eglMakeCurrent(display, surface, surface, context))
        return NULL;

    while (ctx->running) {
        ParsecClientGLRenderFrame(ctx->parsec, 0, preRender, NULL, TIMEOUT);
        eglSwapBuffers(display, surface);
        glFinish();
    }

    return NULL;
}

static void *playAudio(void *opaque)
{
    struct ImplementationContext *ctx = (struct ImplementationContext *)opaque;

    while (ctx->running) {
        ParsecClientPollAudio(ctx->parsec, aaudio_play, TIMEOUT, ctx->aaudio);
    }

    return NULL;
}

static void stopThreads(struct ImplementationContext *ctx)
{
    if (!ctx->running) return;

    ctx->running = false;
    pthread_join(ctx->videoThread, NULL);
    pthread_join(ctx->audioThread, NULL);
}

static void startThreads(struct ImplementationContext *ctx)
{
    if (ctx->running) return;

    ctx->running = true;
    pthread_create(&ctx->videoThread, NULL, renderVideo, ctx);
    pthread_create(&ctx->audioThread, NULL, playAudio, ctx);
}

JNIEXPORT void JNICALL Java_parsec_bindings_Parsec_appInit(JNIEnv *env, jobject instance)
{
    struct ImplementationContext *impl = calloc(1, sizeof(struct ImplementationContext));

    Parsec *parsec = getPointer(env, instance, "parsec");
    impl->parsec = parsec;

    aaudio_init(&impl->aaudio);

    setPointer(env, instance, "impl", impl);
}

JNIEXPORT void JNICALL Java_parsec_bindings_Parsec_appDestroy(JNIEnv *env, jobject instance)
{
    struct ImplementationContext *impl = getPointer(env, instance, "impl");
    if (!impl) return;

    stopThreads(impl);

    aaudio_destroy(&impl->aaudio);

    if (impl->window) {
        ANativeWindow_release(impl->window);
    }

    free(impl);
    setPointer(env, instance, "impl", NULL);
}

JNIEXPORT void JNICALL Java_parsec_bindings_Parsec_appSetSurface(JNIEnv *env,
                                                                 jobject instance,
                                                                 jobject surface)
{
    struct ImplementationContext *impl = getPointer(env, instance, "impl");

    impl->window = ANativeWindow_fromSurface(env, surface);
    startThreads(impl);
}

JNIEXPORT void JNICALL Java_parsec_bindings_Parsec_appDestroySurface(JNIEnv *env,
                                                                     jobject instance)
{
    struct ImplementationContext *impl = getPointer(env, instance, "impl");

    if (impl->window) {
        ANativeWindow_release(impl->window);
        impl->window = NULL;
    }

    stopThreads(impl);
}
