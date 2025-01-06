cmake_minimum_required(VERSION 3.16)
project(College_Mental_Health_ VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    custombutton.h
    custombutton.cpp
    homepage.h
    homepage.cpp
    moodwidget.h
    moodwidget.cpp
    taskpage.h
    taskpage.cpp
    schedulepage.h
    schedulepage.cpp
    counselingdialog.h
    counselingdialog.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(College_Mental_Health_
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        resources.qrc
        moodinfodialog.h moodinfodialog.cpp
        journalviewer.h journalviewer.cpp
        basepage.h basepage.cpp
        loginpage.h loginpage.cpp
    )
else()
    if(ANDROID)
        add_library(College_Mental_Health_ SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(College_Mental_Health_
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(College_Mental_Health_ PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.College_Mental_Health_)
endif()

set_target_properties(College_Mental_Health_ PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS College_Mental_Health_
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(College_Mental_Health_)
endif()
