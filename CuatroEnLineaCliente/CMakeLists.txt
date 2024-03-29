cmake_minimum_required(VERSION 3.5)

project(CuatroEnLineaCliente VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED WebSockets Network COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        Board.h
        Board.cpp
        mainwindow.ui
        files.qrc
        WS.cpp
        WS.hpp
        Players.hpp
        Players.cpp
        GameLobbyWindow.cpp
        GameLobbyWindow.hpp
        MesaWindow.cpp
        MesaWindow.hpp
        Account.hpp
        Account.cpp
        NavBarWidget.cpp
        NavBarWidget.hpp
        NavBarU.cpp
        NavBarU.hpp
        Game.cpp
        Game.hpp
        GameWindow.cpp
        GameWindow.hpp
        PlayerScore.hpp
        PlayerScore.cpp
        Scores.hpp
        Scores.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CuatroEnLineaCliente
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CuatroEnLineaCliente APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CuatroEnLineaCliente SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CuatroEnLineaCliente
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CuatroEnLineaCliente PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebSockets Qt${QT_VERSION_MAJOR}::Network)

set_target_properties(CuatroEnLineaCliente PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS CuatroEnLineaCliente
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CuatroEnLineaCliente)
endif()
