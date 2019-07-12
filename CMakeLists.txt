cmake_minimum_required(VERSION 3.0)
project(logger)

if (${ANDROID_RECOVERY_MODE})
    message(STATUS "Android recovery mode")
    set(CMAKE_EXE_LINKER_FLAGS "-static ${CMAKE_EXE_LINKER_FLAGS}")
endif ()

set(BUILD_TARGET logging)

add_executable(${BUILD_TARGET} logging.cc)
