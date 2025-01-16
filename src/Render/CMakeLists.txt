
set(SOURCES
    ./application.cpp
)

set(HEADERS
    ./application.h
)

target_sources(${PROJECT_NAME} PRIVATE ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>)
