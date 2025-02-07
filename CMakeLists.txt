cmake_minimum_required(VERSION 3.16)

project(qtwebcall VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Network)


qt_add_executable(qtwebcall
    MANUAL_FINALIZATION
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    raiiguard.h
    quotefetcher.h quotefetcher.cpp
    quotewidget.h quotewidget.cpp
    util.h util.cpp
    jsonfetcher.h jsonfetcher.cpp
)

target_link_libraries(qtwebcall PRIVATE Qt6::Widgets Qt6::Network)

qt_finalize_executable(qtwebcall)
