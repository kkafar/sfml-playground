cmake_minimum_required(VERSION 3.22)

project(balls VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR src)
set(DEPENDENCIES_DIR /home/kkafara/software/dependencies)

set(SFML_DIR ${DEPENDENCIES_DIR}/SFML-2.6.0)
set(SFML_LIB_DIR ${SFML_DIR}/lib)
set(GLOG_DIR ${DEPENDENCIES_DIR}/glog-0.6.0)
set(GLOG_LIB_DIR ${GLOG_DIR}/lib)

add_executable(main src/main.cpp src/PieceKind.cpp src/Controller.cpp src/PlayerKind.cpp)

target_include_directories(main PUBLIC ${SFML_DIR}/include/ ${GLOG_DIR}/include/)
target_link_libraries(main PUBLIC ${SFML_LIB_DIR}/libsfml-graphics.so ${SFML_LIB_DIR}/libsfml-window.so ${SFML_LIB_DIR}/libsfml-system.so ${GLOG_LIB_DIR}/libglog.so)

target_compile_features(main PUBLIC cxx_std_17)

