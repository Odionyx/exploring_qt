cmake_minimum_required(VERSION 3.20)

project(task1 VERSION 0.001 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS
    Widgets
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS
    Widgets
)

set(SOURCES
    main.cpp
    mainwindow.cpp
    dialog.cpp
)
set(HEADERS
    mainwindow.h
    dialog.h
)
set(USER_INTERFACE
    mainwindow.ui
    dialog.ui
)

add_executable(${PROJECT_NAME}
    ${USER_INTERFACE}
    ${HEADERS}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

#find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

#qt_standard_project_setup()

#qt_add_executable(standarddialogs
#    dialog.cpp dialog.h
#    main.cpp
#)

#set_target_properties(standarddialogs PROPERTIES
#    WIN32_EXECUTABLE TRUE
#    MACOSX_BUNDLE TRUE
#)

#target_link_libraries(standarddialogs PRIVATE
#    Qt6::Core
#    Qt6::Gui
#    Qt6::Widgets
#)

#install(TARGETS standarddialogs
#    BUNDLE  DESTINATION .
#    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#)

#qt_generate_deploy_app_script(
#    TARGET standarddialogs
#    OUTPUT_SCRIPT deploy_script
#    NO_UNSUPPORTED_PLATFORM_ERROR
#)
#install(SCRIPT ${deploy_script})
