cmake_minimum_required(VERSION 3.20)

project(task1 VERSION 0.001 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Concurrent
    Widgets
    Charts
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Concurrent
    Widgets
    Charts
)

set(SOURCES
    main.cpp
    mainwindow.cpp
    graphicchart.cpp
)
set(HEADERS
    mainwindow.h
    graphicchart.h
)
set(USER_INTERFACE
    mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(
        ${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${USER_INTERFACE}
        ${HEADERS}
        ${SOURCES}
    )
else()
    add_executable(
        ${PROJECT_NAME}
        ${USER_INTERFACE}
        ${HEADERS}
        ${SOURCES}
    )
endif()

target_link_libraries(
    ${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Concurrent
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Charts
)
