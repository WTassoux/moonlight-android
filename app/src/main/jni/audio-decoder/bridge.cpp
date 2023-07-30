#include "bridge.h"

extern "C" {
JNIEXPORT void JNICALL
Java_com_limelight_binding_audio_AndroidOboeAudioRenderer_startStream(JNIEnv *env, jobject thisObj) {
    AudioDecoder::instance().start();
}
JNIEXPORT void JNICALL
Java_com_limelight_binding_audio_AndroidOboeAudioRenderer_stopStream(JNIEnv *env, jobject thisObj) {
    AudioDecoder::instance().stop();
}
JNIEXPORT void JNICALL
Java_com_limelight_binding_audio_AndroidOboeAudioRenderer_writeToStream(JNIEnv *env, jobject thisObj, jshortArray jData){
    jboolean isCopy = true;
    short *data = env->GetShortArrayElements(jData, &isCopy);
    int32_t len = env->GetArrayLength( jData );
    AudioDecoder::instance().write(data, len);
}
}