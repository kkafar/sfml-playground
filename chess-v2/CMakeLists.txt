cmake_minimum_required(VERSION 3.27)
project(chess_v2 LANGUAGES CXX)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MESSAGE_LOG_LEVEL DEBUG)

set(SRC_DIR src)

# Yeah I know this is extremely bad, but this project is just for me.
# TODO: Install these packages via find_package / create download scripts / bundle deps with the project.
set(DEPENDENCIES_DIR /home/kkafara/software/dependencies)
set(SFML_DIR ${DEPENDENCIES_DIR}/SFML-2.6.0)
set(SFML_LIB_DIR ${SFML_DIR}/lib)
set(GLOG_DIR ${DEPENDENCIES_DIR}/glog-0.6.0)
set(GLOG_LIB_DIR ${GLOG_DIR}/lib)
set(RAPIDJSON_DIR ${DEPENDENCIES_DIR}/rapidjson)
set(FROZEN_DIR ${DEPENDENCIES_DIR}/frozen)

#file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${SRC_DIR}/*.cpp ${SRC_DIR}/**/*.cpp)
set(SFML_LIBS
    ${SFML_LIB_DIR}/libsfml-graphics.so
    ${SFML_LIB_DIR}/libsfml-window.so
    ${SFML_LIB_DIR}/libsfml-system.so
    ${SFML_LIB_DIR}/libsfml-system.so
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_executable(chess_v2 ${SRC_FILES})
add_executable(chess_v2 src/main.cpp src/model/board/Chessboard.cpp src/model/piece/Piece.cpp src/model/board/BoardPosition.cpp
        src/Application.cpp
        src/Application.h
        src/core/CommonTypes.h
        src/core/Constants.h
        src/config/Config.cpp
        src/config/Config.h
        src/config/ConfigLoader.cpp
        src/config/ConfigLoader.h
        src/core/render/RenderNode.cpp
        src/core/render/RenderNode.h
        src/core/Tagged.cpp
        src/core/Tagged.h
        src/core/view/View.cpp
        src/core/view/View.h
        src/core/view/ViewGroup.cpp
        src/core/view/ViewGroup.h
        src/core/view/ViewParent.cpp
        src/core/view/ViewParent.h
        src/core/scene/Scene.cpp
        src/core/scene/Scene.h
        src/core/scene/ViewRegistry.cpp
        src/core/scene/ViewRegistry.h
        src/core/view/ViewUtils.cpp
        src/core/view/ViewUtils.h
        src/core/view/ViewType.h
        src/graphics/assets/AssetsManager.cpp
        src/graphics/assets/AssetsManager.h
        src/graphics/assets/PieceImageDescriptor.cpp
        src/graphics/assets/PieceImageDescriptor.h
)

target_include_directories(
        chess_v2
        PUBLIC
        ${SFML_DIR}/include/
        ${GLOG_DIR}/include/
        ${RAPIDJSON_DIR}/include/
        ${FROZEN_DIR}/include/)

target_include_directories(chess_v2 PUBLIC ${SRC_DIR})

target_link_directories(chess_v2 PUBLIC ${SFML_LIB_DIR})
target_link_libraries(chess_v2 PUBLIC ${SFML_LIBS} ${GLOG_LIB_DIR}/libglog.so)
