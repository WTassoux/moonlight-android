#include <android/log.h>
#include "decoder.h"

AudioDecoder::AudioDecoder() {
    mBuilder.setDirection(oboe::Direction::Output);
    mBuilder.setPerformanceMode(oboe::PerformanceMode::LowLatency);
    mBuilder.setSharingMode(oboe::SharingMode::Exclusive);
    mBuilder.setFormat(oboe::AudioFormat::I16);
    mBuilder.setSampleRate(48000);
    mBuilder.setChannelCount(oboe::ChannelCount::Stereo);
    mBuilder.setFormatConversionAllowed(true);
    mBuilder.setCallback(this);
}

AudioDecoder &AudioDecoder::instance() {
    static AudioDecoder decoder;
    return decoder;
}

void AudioDecoder::start() {
    oboe::Result result = mBuilder.openStream(mStream);
    if (result != oboe::Result::OK) {
        return;
    }
    mStream->requestStart();
    __android_log_print(ANDROID_LOG_VERBOSE, "WTX", "Perf %d\n", mStream->getPerformanceMode());

}

void AudioDecoder::stop() {
    mStream->requestStop();
}

void AudioDecoder::write(short *data, int32_t len) {
    mQueueChunks.push_range(data, len);
}

oboe::DataCallbackResult
AudioDecoder::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    auto *outputData = static_cast<short *>(audioData);
    int32_t numberOfChannels = mStream->getChannelCount();

    uint32_t queueSize = mQueueChunks.size();
    if (queueSize < numFrames * numberOfChannels) {
        mQueueChunks.pop_range(outputData, queueSize);
        memset(outputData + queueSize * 2, '\0', 2 * (numFrames * numberOfChannels - queueSize));
        return oboe::DataCallbackResult::Continue;
    }
    mQueueChunks.pop_range(outputData, numFrames * numberOfChannels);
    return oboe::DataCallbackResult::Continue;
}
