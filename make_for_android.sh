#!/usr/bin/env bash

build_profile(){
    abi=$1
    bootMode=$2
    if [[ ${bootMode} == "recovery" ]]; then
        isRecovery=ON
    else
        isRecovery=OFF
    fi
    profileName="Release-${abi}-${bootMode}"
    generationDir="build/${profileName}"
    ndkRoot=${ANDROID_NDK_HOME}
    if [[ ${ndkRoot} == "" ]]; then
        ndkRoot=${ANDROID_NDK_ROOT}
    fi
    if [[ ${ndkRoot} == "" ]]; then
        echo "ANDROID_NDK_HOME or ANDROID_NDK_ROOT not defined"
        exit 1
    fi
    echo "-- Build ${profileName}"
    mkdir -p "${generationDir}"
    cd "${generationDir}"
    cmake \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_TOOLCHAIN_FILE=${ndkRoot}/build/cmake/android.toolchain.cmake \
        -DANDROID_ABI=${abi} \
        -DANDROID_NATIVE_API_LEVEL=21 \
        -DANDROID_RECOVERY_MODE=${isRecovery} \
        ../..
    cmake --build . --target all
    cd -
    echo ""
    echo ""
}

rm -rf build
build_profile armeabi-v7a normal
build_profile armeabi-v7a recovery
build_profile arm64-v8a normal
build_profile arm64-v8a recovery
