cmake_minimum_required(VERSION 3.2.6)

project(renderer VERSION 0.0 LANGUAGES C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "-Wall -Werror")

set(SRC_FILES 
    src/game.cpp
    src/main.cpp
)
set(HEADER_FILES 

    src/game.h
)


add_executable(renderer ${SRC_FILES} ${HEADER_FILES})
target_include_directories(renderer 
                           PRIVATE "C:/SDL2/include",
                            ${CMAKE_SOURCE_DIR}/vendor/glm
                            ${CMAKE_SOURCE_DIR}/vendor/imgui
                            ${CMAKE_SOURCE_DIR}/vendor/lua/include)
            
target_link_libraries(renderer 
                      PRIVATE "C:/SDL2/lib/libSDL2.dll.a"
                      ${CMAKE_SOURCE_DIR}/vendor/lua/lua53.dll)
