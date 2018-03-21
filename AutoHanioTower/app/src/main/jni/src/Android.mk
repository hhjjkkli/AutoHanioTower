LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE:= SDL2
LOCAL_SRC_FILES:= lib/libSDL2.so
LOCAL_EXPORT_C_INCLUDES:= $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_CPPFLAGS :=--std=c++11
LOCAL_MODULE := main
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
# Add your application source files here...
LOCAL_SRC_FILES := main.c log.cpp entry.cpp Game.cpp HanioTowerAlgo.cpp
LOCAL_SHARED_LIBRARIES := SDL2
LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog -latomic -lOpenSLES
include $(BUILD_SHARED_LIBRARY)
