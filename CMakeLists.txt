cmake_minimum_required(VERSION 3.16)

project(GUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Widgets
    Multimedia
    MultimediaWidgets
    Network
    OpenGL
    OpenGLWidgets
)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    camerareceiver.h
    camerareceiver.cpp
    resources.qrc
    src/colmaprunner.h
    src/colmaprunner.cpp
    src/photogrammetrywidget.h
    src/photogrammetrywidget.cpp
    src/modelviewer.h
    src/modelviewer.cpp
)

# Info.plist is macOS-only — don't pass it to the build on Windows/Linux
if(APPLE)
    list(APPEND PROJECT_SOURCES Info.plist)
endif()

qt_add_executable(GUI
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(GUI PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    Qt6::Network
    Qt6::OpenGL
    Qt6::OpenGLWidgets
)

target_include_directories(GUI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

set_target_properties(GUI PROPERTIES
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    OUTPUT_NAME "MainUI_26"
)

# Info.plist is only meaningful on macOS
if(APPLE)
    set_target_properties(GUI PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
    )
endif()

# Bundle COLMAP tools next to the built binary
if(WIN32)
    set(TOOLS_SUBDIR "win64")
elseif(APPLE)
    set(TOOLS_SUBDIR "macos")
else()
    set(TOOLS_SUBDIR "linux")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tools/${TOOLS_SUBDIR}")
    add_custom_command(TARGET GUI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_SOURCE_DIR}/tools/${TOOLS_SUBDIR}"
            "$<TARGET_FILE_DIR:GUI>/tools/${TOOLS_SUBDIR}"
        COMMENT "Bundling COLMAP tools for ${TOOLS_SUBDIR}"
    )
endif()

include(GNUInstallDirs)
if(APPLE)
    install(TARGETS GUI BUNDLE DESTINATION .)
elseif(WIN32)
    install(TARGETS GUI RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
else()
    install(TARGETS GUI
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
endif()

qt_finalize_executable(GUI)
