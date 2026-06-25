cmake_minimum_required(VERSION 3.22.1)

project("kr2patch" C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
        -Wno-macro-redefined
        -Wno-format-truncation
)

include(FetchContent)
set(DOBBY_HOOK_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake_deps/DobbyHook")
set(ONIGURUMA_DIR  "${CMAKE_CURRENT_LIST_DIR}/cmake_deps/oniguruma")

if(NOT EXISTS "${DOBBY_HOOK_DIR}/CMakeLists.txt")
    FetchContent_Declare(
            DobbyHook
            GIT_REPOSITORY https://github.com/dzyong/Dobby.git
            GIT_TAG master
            SOURCE_DIR ${DOBBY_HOOK_DIR}
    )
    FetchContent_MakeAvailable(DobbyHook)
else()
    add_subdirectory(${DOBBY_HOOK_DIR})
endif()

if(NOT EXISTS "${ONIGURUMA_DIR}/CMakeLists.txt")
    include(FetchContent)
    FetchContent_Declare(
            oniguruma
            GIT_REPOSITORY https://github.com/krkrz/oniguruma.git
            GIT_TAG 8c8b22809b7cd22548698a413c987fe2969f7119
            SOURCE_DIR ${ONIGURUMA_DIR}
    )
    FetchContent_GetProperties(oniguruma)
    if(NOT oniguruma_POPULATED)
        FetchContent_Populate(oniguruma)
    endif()
else()
    set(oniguruma_SOURCE_DIR ${ONIGURUMA_DIR})
endif()

if(oniguruma_SOURCE_DIR)
    include(src/oniguruma.cmake)
endif()

add_library(${CMAKE_PROJECT_NAME} SHARED
        src/native-lib.cpp
        src/plugin/pulgin_function.cpp
        src/plugin/plugin_manager.cpp
        src/plugin/k2atvp.cpp
        src/plugin/k2atjs.cpp
        src/plugin/kr2android.cpp
        src/plugin/k2atvp_storage.cpp
        src/plugin/k2atvp_graphic.cpp
        src/plugin/k2atvp_exports.cpp
        src/plugin/utils/AndroidUtils.cpp
        src/plugin/utils/TJSDumpFileOutput.cpp
        src/plugin/utils/TickCount.cpp
        src/plugin/tjs2/tjs.cpp
        src/plugin/tjs2/tjs.tab.cpp
        src/plugin/tjs2/tjsArray.cpp
        src/plugin/tjs2/tjsBinarySerializer.cpp
        src/plugin/tjs2/tjsByteCodeLoader.cpp
        src/plugin/tjs2/tjsCompileControl.cpp
        src/plugin/tjs2/tjsConfig.cpp
        src/plugin/tjs2/tjsConstArrayData.cpp
        src/plugin/tjs2/tjsDate.cpp
        src/plugin/tjs2/tjsdate.tab.cpp
        src/plugin/tjs2/tjsDateParser.cpp
        src/plugin/tjs2/tjsDebug.cpp
        src/plugin/tjs2/tjsDictionary.cpp
        src/plugin/tjs2/tjsDisassemble.cpp
        src/plugin/tjs2/tjsError.cpp
        src/plugin/tjs2/tjsException.cpp
        src/plugin/tjs2/tjsGlobalStringMap.cpp
        src/plugin/tjs2/tjsInterCodeExec.cpp
        src/plugin/tjs2/tjsInterCodeGen.cpp
        src/plugin/tjs2/tjsInterface.cpp
        src/plugin/tjs2/tjsLex.cpp
        src/plugin/tjs2/tjsMath.cpp
        src/plugin/tjs2/tjsMessage.cpp
        src/plugin/tjs2/tjsMT19937ar-cok.cpp
        src/plugin/tjs2/tjsNamespace.cpp
        src/plugin/tjs2/tjsNative.cpp
        src/plugin/tjs2/tjsObject.cpp
        src/plugin/tjs2/tjsObjectExtendable.cpp
        src/plugin/tjs2/tjsOctPack.cpp
        src/plugin/tjs2/tjspp.tab.cpp
        src/plugin/tjs2/tjsRandomGenerator.cpp
        src/plugin/tjs2/tjsRegExp.cpp
        src/plugin/tjs2/tjsScriptBlock.cpp
        src/plugin/tjs2/tjsScriptCache.cpp
        src/plugin/tjs2/tjsString.cpp
        src/plugin/tjs2/tjsUtils.cpp
        src/plugin/tjs2/tjsVariant.cpp
        src/plugin/tjs2/tjsVariantString.cpp
        ${ONIGURUMA_SOURCES}
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        src
        src/plugin
        src/plugin/tjs2
        src/plugin/utils
        ${ONIGURUMA_INCLUDES}
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        dobby_static
        android
        log
)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        -Wno-tautological-constant-out-of-range-compare
        -Wno-null-dereference
        -Wno-writable-strings
        -Wno-return-type
        -Wno-macro-redefined
        -Wno-pointer-to-int-cast
        -Wno-null-conversion
        -Wno-shift-count-overflow
        -Wno-undefined-bool-conversion
        -Wno-pointer-to-int-cast
        -Wno-deprecated-non-prototype
)