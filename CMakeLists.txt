cmake_minimum_required(VERSION 3.5)

project(WebEngine2 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS widgets webengine webenginewidgets REQUIRED)

if(ANDROID)
  add_library(WebEngine2 SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Downloader.h
    Downloader.cpp
  )
else()
  add_executable(WebEngine2
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/Downloader.h
    src/Downloader.cpp
  )
endif()


target_link_libraries(WebEngine2 PRIVATE Qt5::Widgets)
target_link_libraries(WebEngine2 PRIVATE Qt5::WebEngineWidgets)
