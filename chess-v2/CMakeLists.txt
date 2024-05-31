cmake_minimum_required(VERSION 3.27)
project(chess_v2 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

set(SRC_DIR src)
set(DEPENDENCIES_DIR /home/kkafara/software/dependencies)

set(SFML_DIR ${DEPENDENCIES_DIR}/SFML-2.6.0)
set(SFML_LIB_DIR ${SFML_DIR}/lib)
set(GLOG_DIR ${DEPENDENCIES_DIR}/glog-0.6.0)
set(GLOG_LIB_DIR ${GLOG_DIR}/lib)

#file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp ${SRC_DIR}/**/*.cpp)
set(SFML_LIBS
    ${SFML_LIB_DIR}/libsfml-graphics.so
    ${SFML_LIB_DIR}/libsfml-window.so
    ${SFML_LIB_DIR}/libsfml-system.so
    ${SFML_LIB_DIR}/libsfml-system.so
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_executable(chess_v2 ${SRC_FILES})
add_executable(chess_v2 src/main.cpp src/model/board/Chessboard.cpp src/model/piece/Piece.cpp src/model/piece/PieceColor.cpp src/model/piece/PieceKind.cpp src/model/board/BoardPosition.cpp
        src/Application.cpp
        src/Application.h
        src/core/CommonTypes.h)

target_include_directories(chess_v2 PUBLIC ${SFML_DIR}/include/ ${GLOG_DIR}/include/)
target_include_directories(chess_v2 PUBLIC ${SRC_DIR})
target_link_directories(chess_v2 PUBLIC ${SFML_LIB_DIR})
target_link_libraries(chess_v2 PUBLIC ${SFML_LIBS} ${GLOG_LIB_DIR}/libglog.so)
