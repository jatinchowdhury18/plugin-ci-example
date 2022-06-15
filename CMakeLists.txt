cmake_minimum_required(VERSION 3.15)
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12" CACHE STRING "Minimum OS X deployment target")
project(SimplePlugin VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(COMPANY_NAME "chowdsp")
set(PRODUCT_NAME "SimplePlugin")

option(CLAP_WRAP "Wrap a CLAP plugin" OFF)
if(CLAP_WRAP)
    # usage: cmake -Bbuild-clap -G<generator> -DCMAKE_BUILD_TYPE=<Debug|Release> -DCLAP_WRAP=ON
    #        cmake --build build-clap --config <Debug|Release>
    message(STATUS "Building a CLAP!")

    set(PATH_TO_JUCE modules/JUCE)
    set(PATH_TO_CLAP_EXTENSIONS modules/clap-juce-extensions)

    if(APPLE)
        set(JUCER_GENERATOR "Xcode")
    elseif(WIN32)
        set(JUCER_GENERATOR "VisualStudio2019")
    else() # Linux
        set(JUCER_GENERATOR "LinuxMakefiles")
    endif()

    include(cmake/JucerClap.cmake)
    create_jucer_clap_target(
        TARGET SimplePlugin
        PLUGIN_NAME "Simple Plugin"
        MANUFACTURER_NAME chowdsp
        VERSION_STRING "1.0.0"
        CLAP_ID "org.chowdsp.SimplePlugin"
        CLAP_FEATURES audio-effect utility
    )

    return()
endif()

add_subdirectory(modules)

# juce_set_vst2_sdk_path(C:/SDKs/VST_SDK/VST2_SDK)
# set default plugin formats to build
if(IOS)
    set(JUCE_FORMATS Standalone AUv3)
else()
    set(JUCE_FORMATS AU VST3 Standalone)
endif()

# Build LV2 only on Linux
if(UNIX AND NOT APPLE)
    message(STATUS "Building LV2 plugin format")
    list(APPEND JUCE_FORMATS LV2)
endif()

# Build VST2 is SDK set
if(TARGET juce_vst2_sdk)
    message(STATUS "Building VST2 plugin format")
    list(APPEND JUCE_FORMATS VST)
endif()

juce_add_plugin(SimplePlugin
    COMPANY_NAME "${COMPANY_NAME}"
    PLUGIN_MANUFACTURER_CODE Chow
    PLUGIN_CODE ixu0
    FORMATS ${JUCE_FORMATS}
    PRODUCT_NAME "${PRODUCT_NAME}"
    LV2_URI https://github.com/Chowdhury-DSP/SimplePlugin
)

juce_generate_juce_header(SimplePlugin)
add_subdirectory(src)
include_directories(src)
add_subdirectory(res)

target_compile_definitions(SimplePlugin PUBLIC
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(SimplePlugin PRIVATE juce_plugin_modules)

# we need these flags for notarization on MacOS
option(MACOS_RELEASE "Set build flags for MacOS Release" OFF)
if(MACOS_RELEASE)
    message(STATUS "Setting MacOS release flags...")
    set_target_properties(SimplePlugin_Standalone PROPERTIES
        XCODE_ATTRIBUTE_ENABLE_HARDENED_RUNTIME YES)
endif()
