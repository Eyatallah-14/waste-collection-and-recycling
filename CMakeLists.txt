cmake_minimum_required(VERSION 3.16)

project(GestionPoubelle VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Trouver les packages Qt nécessaires
find_package(Qt6 REQUIRED COMPONENTS 
    Core 
    Widgets 
    Charts
    PrintSupport
)

# Fichiers sources du projet
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    gestionpoubellepages.cpp
    gestionpoubellepages.h
    gestionpoubellepages.ui
    resources.qrc
)

# Créer l'exécutable
qt_add_executable(GestionPoubelle
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

# Lier les bibliothèques Qt
target_link_libraries(GestionPoubelle PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Charts
    Qt6::PrintSupport
)

# Configuration spécifique à Windows
if(WIN32)
    set_target_properties(GestionPoubelle PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Finaliser l'exécutable Qt
qt_finalize_executable(GestionPoubelle)

# Installation
install(TARGETS GestionPoubelle
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
