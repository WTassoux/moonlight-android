#pragma once

#include <oboe/Oboe.h>
#include <vector>
#include <jni.h>
#include "queue.h"

class AudioDecoder : public oboe::AudioStreamCallback {
public:
    static AudioDecoder& instance();

    void start();
    void stop();
    void write(short* data, int32_t len);
    oboe::DataCallbackResult onAudioReady(
            oboe::AudioStream *audioStream,
            void *audioData,
            int32_t numFrames) override;
private:
    AudioDecoder();

    oboe::AudioStreamBuilder mBuilder;
    std::shared_ptr<oboe::AudioStream> mStream;
    LockFreeQueue<short, 32768> mQueueChunks;
};