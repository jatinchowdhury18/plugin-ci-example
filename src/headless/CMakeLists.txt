juce_add_console_app(SimplePlugin_headless
    PRODUCT_NAME "SimplePlugin"
    COMPANY_NAME chowdsp
)

juce_generate_juce_header(SimplePlugin_headless)
add_custom_command(TARGET SimplePlugin_headless
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E echo "copying $<TARGET_FILE:SimplePlugin_headless> to ${PROJECT_BINARY_DIR}/SimplePlugin"
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SimplePlugin_headless> ${PROJECT_BINARY_DIR}/SimplePlugin)

target_sources(SimplePlugin_headless PRIVATE
    main.cpp

    tests/GainTest.cpp
    tests/UnitTests.cpp
)

target_precompile_headers(SimplePlugin_headless PRIVATE ../pch.h)
target_include_directories(SimplePlugin_headless
    PRIVATE
    ../
    ../../modules
    ../../modules/JUCE/modules
)

target_link_libraries(SimplePlugin_headless PUBLIC
    BinaryData
    SimplePlugin
)

set_target_properties(SimplePlugin_headless PROPERTIES CXX_VISIBILITY_PRESET hidden)
