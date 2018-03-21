#ifndef __log_H__
#define __log_H__
#include <jni.h>
#include <android/log.h>

#define logd(...)  __android_log_print(ANDROID_LOG_DEBUG,"tiaoshi",__VA_ARGS__)
//屏蔽log
//#define logd(...)
#endif // !__log_H__
