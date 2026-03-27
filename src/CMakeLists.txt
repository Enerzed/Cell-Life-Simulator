file(GLOB CLS_SRC "*.h" "*.cpp")

file(GLOB_RECURSE RESOURCE_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/textures/*
    ${CMAKE_CURRENT_SOURCE_DIR}/fonts/*
)

add_executable(CLS ${CLS_SRC})

target_link_libraries(CLS PRIVATE ImGui-SFML::ImGui-SFML)

set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/textures)
add_custom_command(TARGET CLS POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/textures
    ${OUTPUT_DIR}
)

set(OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/fonts)
add_custom_command(TARGET CLS POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/fonts
    ${OUTPUT_DIR}
)