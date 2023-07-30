MY_LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_PATH := $(MY_LOCAL_PATH)

include $(CLEAR_VARS)
LOCAL_MODULE    := audio-decoder

LOCAL_SRC_FILES := bridge.cpp \
				   decoder.cpp
LOCAL_LDFLAGS  := -llog
LOCAL_SHARED_LIBRARIES := oboe
include $(BUILD_SHARED_LIBRARY)
