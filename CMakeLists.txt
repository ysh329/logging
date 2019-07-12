cmake_minimum_required(VERSION 3.0)
project(logger)

option(X86_PLATFORM     "X86 platform"                            ON)
option(ANDROID_PLATFORM "Android platform"                        OFF) #NOT(X86_PLATFROM))
option(ENABLE_NDEBUG    "Disable all check and log informations." ON)

message(STATUS "ENABLE_NDEBUG: "   ${ENABLE_NDEBUG})
message(STATUS "X86_PLATFORM: "     ${X86_PLATFORM})
message(STATUS "ANDROID_PLATFORM: " ${ANDROID_PLATFORM})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(ENABLE_NDEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG")
endif(ENABLE_NDEBUG)

if(X86_PLATFORM AND (NOT ANDROID_PLATFORM))
    # TODO(ysh329): X86 config
else(X86_PLATFORM AND (NOT ANDROID_PLATFORM))
    if(${ANDROID_RECOVERY_MODE})
        message(STATUS "Android recovery mode")
        set(CMAKE_EXE_LINKER_FLAGS "-static ${CMAKE_EXE_LINKER_FLAGS}")
    endif(${ANDROID_RECOVERY_MODE})
endif(X86_PLATFORM AND (NOT ANDROID_PLATFORM))

set(BUILD_TARGET example)
add_executable(${BUILD_TARGET} example.cc logging.h)
