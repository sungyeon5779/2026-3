cmake_minimum_required(VERSION 3.16)
project(SubwayShortestPath LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
add_executable(SubwayShortestPath
    main.cpp Graph.cpp MapWidget.cpp MainWindow.cpp
    Graph.h MapWidget.h MainWindow.h SubwayData.h)
target_link_libraries(SubwayShortestPath PRIVATE Qt6::Widgets)
