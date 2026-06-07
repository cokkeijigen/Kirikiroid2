cmake_minimum_required(VERSION 3.22.1)

project("kr2patch" C CXX)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

set(DOBBY_HOOK_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake_deps/DobbyHook" )
set(KR2ANDROID_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake_deps/kr2android")

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

if(NOT EXISTS "${KR2ANDROID_DIR}/CMakeLists.txt")
    FetchContent_Declare(
            kr2android
            GIT_REPOSITORY https://github.com/cokkeijigen/Kirikiroid2.git
            GIT_TAG kr2android
            SOURCE_DIR ${KR2ANDROID_DIR}
    )
    FetchContent_MakeAvailable(kr2android)
else()
    add_subdirectory(${KR2ANDROID_DIR})
endif()

add_library(${CMAKE_PROJECT_NAME} SHARED
        src/native-lib.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
        src
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        dobby_static
        kr2android
        android
        log
)