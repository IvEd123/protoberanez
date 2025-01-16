set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

add_executable(${PROJECT_NAME} ${SRC})

add_subdirectory(Application)
add_subdirectory(Render)