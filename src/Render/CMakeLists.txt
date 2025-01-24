
set(SOURCES
    shader.cpp
    shader_program.cpp
    renderer.cpp
    vertex_array.cpp
    framebuffer.cpp
    draw_object.cpp
    texture.cpp
)

set(HEADERS
    shader.h
    shader_program.h
    renderer.h
    vertex_array.h
    framebuffer.h
    draw_object.h
    texture.h
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
