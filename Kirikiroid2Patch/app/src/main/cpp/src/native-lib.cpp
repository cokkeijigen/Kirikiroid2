#include <native-lib.hpp>
#include <kr2android.hpp>
#include <link.h>

namespace kr2patch
{
    static JavaVM *javavm{};

    auto get_javavm() noexcept -> JavaVM*
    {
        return kr2patch::javavm;
    }

    extern "C" JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved)
    {
        kr2patch::javavm = vm;

        if(kr2android::init())
        {
            logd("kr2android init success!\n");
        }
        else
        {
            logd("kr2android init failed!\n");
        }

        return JNI_VERSION_1_6;
    }
}