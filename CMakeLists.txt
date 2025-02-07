cmake_minimum_required(VERSION 3.16)

project(qtwebcall VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        quotefetcher.h quotefetcher.cpp
        quotewidget.h quotewidget.cpp
        util.h util.cpp
)

qt_add_executable(qtwebcall
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(qtwebcall PRIVATE Qt6::Widgets Qt6::Network)

qt_finalize_executable(qtwebcall)
