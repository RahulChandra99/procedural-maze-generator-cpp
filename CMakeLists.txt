cmake_minimum_required(VERSION 3.20)
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
   set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()
# Name of the project
project(ProcGenBuild)

set(TargetName ProcGenNGL)

find_package(NGL CONFIG REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Set the name of the executable we want to build
add_executable(${TargetName}
		src/NGLScene.cpp
		include/NGLScene.h
        src/Prims.cpp
		include/Prims.h
        src/MapLocation.cpp
		include/MapLocation.h
		src/Maze.cpp
		include/Maze.h
        src/Wilsons.cpp
		include/Wilsons.h
		src/DFSRecursive.cpp
		include/DFSRecursive.h
)

target_sources(${TargetName} PRIVATE ${PROJECT_SOURCE_DIR}/src/main.cpp  
			${PROJECT_SOURCE_DIR}/src/NGLScene.cpp  
			${PROJECT_SOURCE_DIR}/src/MainWindow.cpp  
			${PROJECT_SOURCE_DIR}/src/NGLSceneMouseControls.cpp
			${PROJECT_SOURCE_DIR}/include/MainWindow.h  
			${PROJECT_SOURCE_DIR}/include/NGLScene.h  
)

target_link_libraries(${TargetName} PRIVATE  NGL Qt${QT_VERSION_MAJOR}::Widgets )


### Testing Code
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
add_executable(ProcGenTests)
target_link_libraries(ProcGenTests PRIVATE  NGL Qt${QT_VERSION_MAJOR}::Widgets )
target_include_directories(ProcGenTests PRIVATE include src)
target_sources(ProcGenTests PRIVATE tests/MazeGenTests.cpp
		src/NGLScene.cpp
		include/NGLScene.h
		src/Prims.cpp
		include/Prims.h
		src/MapLocation.cpp
		include/MapLocation.h
		src/Maze.cpp
		include/Maze.h
		src/Wilsons.cpp
		include/Wilsons.h
		src/DFSRecursive.cpp
		include/DFSRecursive.h
		src/NGLSceneMouseControls.cpp)
target_link_libraries(ProcGenTests PRIVATE GTest::gtest GTest::gtest_main)
gtest_discover_tests(ProcGenTests)

add_custom_target(${TargetName}CopyShaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    $<TARGET_FILE_DIR:${TargetName}>/shaders)


