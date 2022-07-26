#include <stdlib.h>
#include <stdbool.h>

#include <jni.h>
#include <android/log.h>

#include "parsec.h"

static void logCallback(ParsecLogLevel level, const char *msg, void *opaque)
{
    __android_log_print(ANDROID_LOG_INFO, "PARSEC", "%s", msg);
}

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

JNIEXPORT void JNICALL
Java_parsec_bindings_Parsec_setLogCallback(JNIEnv *env, jobject instance)
{
    ParsecSetLogCallback(logCallback, NULL);
}

JNIEXPORT void JNICALL
Java_parsec_bindings_Parsec_init(JNIEnv *env, jobject instance)
{
    Parsec *parsec = NULL;
    ParsecInit(PARSEC_VER, NULL, NULL, &parsec);

    setPointer(env, instance, "parsec", parsec);
}

JNIEXPORT void JNICALL
Java_parsec_bindings_Parsec_destroy(JNIEnv *env, jobject instance)
{
    Parsec *parsec = getPointer(env, instance, "parsec");
    ParsecDestroy(parsec);

    setPointer(env, instance, "parsec", NULL);
}

JNIEXPORT jint JNICALL
Java_parsec_bindings_Parsec_clientConnect(JNIEnv *env, jobject instance, jstring sessionID,
    jstring peerID)
{
    Parsec *parsec = getPointer(env, instance, "parsec");

    const char *cSessionID = (*env)->GetStringUTFChars(env, sessionID, 0);
    const char *cPeerID = (*env)->GetStringUTFChars(env, peerID, 0);

    ParsecStatus e = ParsecClientConnect(parsec, NULL, cSessionID, cPeerID);

    (*env)->ReleaseStringUTFChars(env, sessionID, cSessionID);
    (*env)->ReleaseStringUTFChars(env, peerID, cPeerID);

    return (jint) e;
}

JNIEXPORT jint JNICALL
Java_parsec_bindings_Parsec_clientGetStatus(JNIEnv *env, jobject instance)
{
    Parsec *parsec = getPointer(env, instance, "parsec");

    return (jint) ParsecClientGetStatus(parsec, NULL);
}

JNIEXPORT void JNICALL
Java_parsec_bindings_Parsec_clientDestroy(JNIEnv *env, jobject instance)
{
    Parsec *parsec = getPointer(env, instance, "parsec");
    ParsecClientDisconnect(parsec);
}

JNIEXPORT void JNICALL
Java_parsec_bindings_Parsec_clientSetDimensions(JNIEnv *env, jobject instance,
    jint x, jint y)
{
    Parsec *parsec = getPointer(env, instance, "parsec");
    ParsecClientSetDimensions(parsec, 0, (uint32_t) x, (uint32_t) y, 1.0f);
}

JNIEXPORT jint JNICALL
Java_parsec_bindings_Parsec_clientSendMouseMotion(JNIEnv *env, jobject instance,
    jboolean relative, jint x, jint y)
{
    Parsec *parsec = getPointer(env, instance, "parsec");

    ParsecMessage msg = {};
    msg.type = MESSAGE_MOUSE_MOTION;
    msg.mouseMotion.relative = relative;
    msg.mouseMotion.x = x;
    msg.mouseMotion.y = y;

    return (jint) ParsecClientSendMessage(parsec, &msg);
}

JNIEXPORT jint JNICALL
Java_parsec_bindings_Parsec_clientSendMouseWheel(JNIEnv *env, jobject instance, jint x, jint y)
{
    Parsec *parsec = getPointer(env, instance, "parsec");

    struct ParsecMessage msg;
    msg.type = MESSAGE_MOUSE_WHEEL;
    msg.mouseWheel.x = x;
    msg.mouseWheel.y = y;

    return (jint) ParsecClientSendMessage(parsec, &msg);
}

JNIEXPORT jint JNICALL
Java_parsec_bindings_Parsec_clientSendGamepadButton(JNIEnv *env, jobject instance,
        jint gamepadID, jint button, jboolean pressed)
{
    Parsec *parsec = getPointer(env, instance, "parsec");

    struct ParsecMessage msg;
    msg.type = MESSAGE_GAMEPAD_BUTTON;
    msg.gamepadButton.button = (ParsecGamepadButton) button;
    msg.gamepadButton.id = (uint32_t) gamepadID;
    msg.gamepadButton.pressed = pressed;

    return (jint) ParsecClientSendMessage(parsec, &msg);
}

JNIEXPORT jint JNICALL
Java_parsec_bindings_Parsec_clientSendGamepadAxis(JNIEnv *env, jobject instance,
        jint gamepadID, jint axis, jint value)
{
    Parsec *parsec = getPointer(env, instance, "parsec");

    struct ParsecMessage msg;
    msg.type = MESSAGE_GAMEPAD_AXIS;
    msg.gamepadAxis.axis = (ParsecGamepadAxis) axis;
    msg.gamepadAxis.id = (uint32_t) gamepadID;
    msg.gamepadAxis.value = (uint16_t) value;

    return (jint) ParsecClientSendMessage(parsec, &msg);
}

JNIEXPORT jint JNICALL
Java_parsec_bindings_Parsec_clientSendKeyboard(JNIEnv *env, jobject instance,
        jint keyCode, jint keyMod, jboolean pressed)
{
    Parsec *parsec = getPointer(env, instance, "parsec");

    struct ParsecMessage msg;
    msg.type = MESSAGE_KEYBOARD;
    msg.keyboard.code = (ParsecKeycode) keyCode;
    msg.keyboard.mod = (ParsecKeymod) keyMod;
    msg.keyboard.pressed = pressed;

    return (jint) ParsecClientSendMessage(parsec, &msg);
}

JNIEXPORT jint JNICALL
Java_parsec_bindings_Parsec_clientSendMouseButton(JNIEnv *env, jobject instance,
    jint button, jboolean pressed)
{
    Parsec *parsec = getPointer(env, instance, "parsec");

    ParsecMessage msg = {};
    msg.type = MESSAGE_MOUSE_BUTTON;
    msg.mouseButton.button = (ParsecMouseButton) button;
    msg.mouseButton.pressed = pressed;

    return (jint) ParsecClientSendMessage(parsec, &msg);
}
