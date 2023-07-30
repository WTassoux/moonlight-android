package com.limelight.binding.audio;

import android.content.Context;

import com.limelight.Game;
import com.limelight.nvstream.av.audio.AudioRenderer;
import com.limelight.nvstream.jni.MoonBridge;

public class AndroidOboeAudioRenderer implements AudioRenderer {

    static {
        System.loadLibrary("audio-decoder");
    }

    public AndroidOboeAudioRenderer(Context context, boolean enableAudioFx) {
    }

    @Override
    public int setup(MoonBridge.AudioConfiguration audioConfiguration, int sampleRate, int samplesPerFrame) {
        return 0;
    }

    @Override
    public void start() {
        startStream();
    }

    @Override
    public void stop() {
        stopStream();
    }

    @Override
    public void playDecodedAudio(short[] audioData) {
        writeToStream(audioData);
    }

    @Override
    public void cleanup() {

    }

    public static native void writeToStream(short[] data);

    public static native void startStream();
    public static native void stopStream();

}
