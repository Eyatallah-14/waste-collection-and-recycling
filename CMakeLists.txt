cmake_minimum_required(VERSION 3.16)

project(emp_vehic_zones_poubelle VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -------------------------------
# Find Qt with Widgets + Charts + PrintSupport
# -------------------------------
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts PrintSupport)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts PrintSupport)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        employepages.cpp
        employepages.h
        employepages.ui
        zonepages.cpp
        zonepages.h
        gestionpoubellepages.cpp
        gestionpoubellepages.h
        gestionpoubellepages.ui
        resources.qrc
        Loginwindow.h
        Loginwindow.cpp
        loginwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(emp_vehic_zones_poubelle
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(emp_vehic_zones_poubelle SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(emp_vehic_zones_poubelle
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# -------------------------------
# Link Qt Libraries
# -------------------------------
target_link_libraries(emp_vehic_zones_poubelle
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::PrintSupport
)

# -------------------------------
# App Properties
# -------------------------------
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.emp_vehic_zones_poubelle)
endif()

set_target_properties(emp_vehic_zones_poubelle PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING
        ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)

install(TARGETS emp_vehic_zones_poubelle
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(emp_vehic_zones_poubelle)
endif()
