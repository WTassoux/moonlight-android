#pragma once
#include <jni.h>
#include "decoder.h"

extern "C" {
JNIEXPORT void JNICALL
Java_com_limelight_binding_audio_AndroidOboeAudioRenderer_startStream(JNIEnv *env, jobject thisObj);
JNIEXPORT void JNICALL
Java_com_limelight_binding_audio_AndroidOboeAudioRenderer_stopStream(JNIEnv *env, jobject thisObj);
JNIEXPORT void JNICALL
Java_com_limelight_binding_audio_AndroidOboeAudioRenderer_writeToStream(JNIEnv *env, jobject thisObj, jshortArray jData);
}