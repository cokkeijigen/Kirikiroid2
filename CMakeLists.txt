project(kr2android)

set(ONIGURUMA_DIR "${CMAKE_CURRENT_LIST_DIR}/oniguruma")
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
    include(oniguruma.cmake)
endif()

add_library(kr2android STATIC
        src/kr2android.cpp
        src/utils/AndroidUtils.cpp
        src/utils/TickCount.cpp
        src/tjs2/tjs.cpp
        src/tjs2/tjs.tab.cpp
        src/tjs2/tjsArray.cpp
        src/tjs2/tjsBinarySerializer.cpp
        src/tjs2/tjsByteCodeLoader.cpp
        src/tjs2/tjsCompileControl.cpp
        src/tjs2/tjsConfig.cpp
        src/tjs2/tjsConstArrayData.cpp
        src/tjs2/tjsDate.cpp
        src/tjs2/tjsdate.tab.cpp
        src/tjs2/tjsDateParser.cpp
        src/tjs2/tjsDebug.cpp
        src/tjs2/tjsDictionary.cpp
        src/tjs2/tjsDisassemble.cpp
        src/tjs2/tjsError.cpp
        src/tjs2/tjsException.cpp
        src/tjs2/tjsGlobalStringMap.cpp
        src/tjs2/tjsInterCodeExec.cpp
        src/tjs2/tjsInterCodeGen.cpp
        src/tjs2/tjsInterface.cpp
        src/tjs2/tjsLex.cpp
        src/tjs2/tjsMath.cpp
        src/tjs2/tjsMessage.cpp
        src/tjs2/tjsMT19937ar-cok.cpp
        src/tjs2/tjsNamespace.cpp
        src/tjs2/tjsNative.cpp
        src/tjs2/tjsObject.cpp
        src/tjs2/tjsObjectExtendable.cpp
        src/tjs2/tjsOctPack.cpp
        src/tjs2/tjspp.tab.cpp
        src/tjs2/tjsRandomGenerator.cpp
        src/tjs2/tjsRegExp.cpp
        src/tjs2/tjsScriptBlock.cpp
        src/tjs2/tjsScriptCache.cpp
        src/tjs2/tjsString.cpp
        src/tjs2/tjsUtils.cpp
        src/tjs2/tjsVariant.cpp
        src/tjs2/tjsVariantString.cpp
)

target_include_directories(kr2android PUBLIC
        src
        src/tjs2
        src/utils
)

target_link_libraries(kr2android PUBLIC
        oniguruma
)