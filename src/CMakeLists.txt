add_subdirectory(headless)

target_sources(SimplePlugin PRIVATE
    SimplePlugin.cpp
)

target_precompile_headers(SimplePlugin PRIVATE pch.h)
    