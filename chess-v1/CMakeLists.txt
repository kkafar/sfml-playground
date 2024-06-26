cmake_minimum_required(VERSION 3.22)

project(balls VERSION 0.1 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

set(SRC_DIR src)
set(DEPENDENCIES_DIR /home/kkafara/software/dependencies)

set(SFML_DIR ${DEPENDENCIES_DIR}/SFML-2.6.0)
set(SFML_LIB_DIR ${SFML_DIR}/lib)
set(GLOG_DIR ${DEPENDENCIES_DIR}/glog-0.6.0)
set(GLOG_LIB_DIR ${GLOG_DIR}/lib)

# set(SRC_FILES 
#   src/main.cpp
#   src/Controller.cpp
#   src/Chessboard.cpp
#   src/PlayerKind.cpp
#   src/PieceKind.cpp
# )

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp ${SRC_DIR}/**/*.cpp)

set(SFML_LIBS
  ${SFML_LIB_DIR}/libsfml-graphics.so
  ${SFML_LIB_DIR}/libsfml-window.so
  ${SFML_LIB_DIR}/libsfml-system.so 
)

add_executable(main ${SRC_FILES})

target_include_directories(main PUBLIC ${SFML_DIR}/include/ ${GLOG_DIR}/include/ ${SRC_DIR})
target_link_libraries(main PUBLIC ${SFML_LIBS} ${GLOG_LIB_DIR}/libglog.so)

target_compile_features(main PUBLIC cxx_std_20)
set_target_properties(main PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

