#pragma once
#include <jni.h>
#include <android/log.h>
#define TAG "kr2patch"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define logd(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

namespace kr2patch
{
    extern auto get_javavm() noexcept -> JavaVM*;
}