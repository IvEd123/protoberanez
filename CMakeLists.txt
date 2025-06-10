cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME 
    cosmo
)


project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 
    17 # C++ standard 
)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)
find_package(GLEW REQUIRED CONFIG)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2-static)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image-static)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)