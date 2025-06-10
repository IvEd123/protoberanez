include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

add_executable(framebuffer_test
    framebuffer_test.cpp
    ${CMAKE_SOURCE_DIR}/src/Render/framebuffer.cpp
)

target_include_directories(framebuffer_test PRIVATE
    ${CMAKE_SOURCE_DIR}/src/Render
)

target_link_libraries(framebuffer_test PRIVATE
    gtest_main
    SDL2::SDL2main SDL2::SDL2-static
    GLEW::GLEW
)

add_test(NAME framebuffer_test COMMAND framebuffer_test)
