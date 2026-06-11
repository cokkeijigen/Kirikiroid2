#pragma once
#include <jni.h>
#include <dobby.h>
#include <android/log.h>
#include <kr2android.hpp>
#if defined(__aarch64__)
#define armv8orv7(arm64v8a, armeabiv7a, ...) arm64v8a
#define arm_only(...) __VA_ARGS__
#define ARM_ONLY(...) __VA_ARGS__
#define arm64v8_only(...) __VA_ARGS__
#define ARM64V8_ONLY(...) __VA_ARGS__
#elif defined(__arm__)
#define armv8orv7(arm64v8a, armeabiv7a, ...) armeabiv7a
#define arm_only(...) __VA_ARGS__
#define ARM_ONLY(...) __VA_ARGS__
#define armeabiv7_only(...) __VA_ARGS__
#define ARMEABIV7_ONLY(...) __VA_ARGS__
#else
#define armv8orv7(arm64v8a, armeabiv7a, ...) __VA_ARGS__
#define arm_only(...)
#define ARM_ONLY(...)
#endif

#define TAG "kr2patch"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, "[kr2patch] " __VA_ARGS__)
#define logd(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, "[kr2patch] " __VA_ARGS__)
#define noinline __attribute__((noinline))

namespace kr2patch
{
    extern auto get_jvm() noexcept -> JavaVM*;

    struct hooker
    {
        template<auto fun>
        inline static decltype(fun) call;

        template<auto fun>
        inline static auto add(void* target) -> int
        {
            auto _out{ reinterpret_cast<void**>(&hooker::call<fun>) };
            auto _fun{ reinterpret_cast<void*>(fun) };
            return ::DobbyHook(target, _fun, _out);
        }

        template<auto fun>
        inline static auto add(decltype(fun) target) -> int
        {
            return hooker::add<fun>(reinterpret_cast<void*>(target));
        }
    };
}