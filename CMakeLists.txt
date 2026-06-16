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
    Charts
)
find_package(OpenCV REQUIRED)

# ONNX Runtime 1.26.0 bundled
set(ORT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/third_party/onnxruntime")
set(ORT_INC  "${ORT_ROOT}/include")

if(APPLE)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64")
        set(ORT_LIB_DIR "${ORT_ROOT}/lib/mac_arm64")
    else()
        set(ORT_LIB_DIR "${ORT_ROOT}/lib/mac_x86")
    endif()
    set(ORT_LIB "${ORT_LIB_DIR}/libonnxruntime.dylib")

elseif(WIN32)
    set(ORT_LIB_DIR "${ORT_ROOT}/lib/win")
    set(ORT_LIB "${ORT_LIB_DIR}/onnxruntime.lib")   # import lib (link-time)
    set(ORT_DLL "${ORT_LIB_DIR}/onnxruntime.dll")   # runtime DLL (run-time)

elseif(UNIX)
    set(ORT_LIB_DIR "${ORT_ROOT}/lib/linux")
    set(ORT_LIB "${ORT_LIB_DIR}/libonnxruntime.so")
endif()

add_library(onnxruntime SHARED IMPORTED GLOBAL)
set_target_properties(onnxruntime PROPERTIES
    IMPORTED_LOCATION "${ORT_LIB}"
    INTERFACE_INCLUDE_DIRECTORIES "${ORT_INC}"
)

if(WIN32)
    set_target_properties(onnxruntime PROPERTIES IMPORTED_IMPLIB "${ORT_LIB}")
endif()


set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    camerareceiver.h
    camerareceiver.cpp
    crabdetector.h
    crabdetector.cpp
    resources.qrc
    src/colmaprunner.h
    src/colmaprunner.cpp
    src/taskrunner.h
    src/taskrunner.cpp
    src/pilink.h
    src/pilink.cpp
    src/rovsetuppage.h
    src/rovsetuppage.cpp
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
    crabs/green_crab.png crabs/jonah_crab.png crabs/rock_crab.png
)

target_link_libraries(GUI PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Multimedia
    Qt6::MultimediaWidgets
    Qt6::Network
    Qt6::OpenGL
    Qt6::OpenGLWidgets
    Qt6::Charts

    ${OpenCV_LIBS}
    onnxruntime
)

target_include_directories(GUI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
                                       ${OpenCV_INCLUDE_DIRS}
                                       ${ORT_INC})

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

# Copy ONNX Runtime library
if(APPLE)
    add_custom_command(TARGET GUI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${ORT_LIB}"
            "$<TARGET_FILE_DIR:GUI>/libonnxruntime.1.dylib"
        COMMENT "Copying libonnxruntime.dylib into bundle"
    )
    add_custom_command(TARGET GUI POST_BUILD
        COMMAND install_name_tool
            -change "@rpath/libonnxruntime.1.dylib"
                    "@executable_path/libonnxruntime.1.dylib"
            "$<TARGET_FILE:GUI>"
        COMMENT "Patching ONNX Runtime rpath in executable"
    )

elseif(WIN32)
    add_custom_command(TARGET GUI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${ORT_DLL}"
            "$<TARGET_FILE_DIR:GUI>/onnxruntime.dll"
        COMMENT "Copying onnxruntime.dll next to executable"
    )

elseif(UNIX)
    add_custom_command(TARGET GUI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${ORT_LIB_DIR}/libonnxruntime.so"
            "$<TARGET_FILE_DIR:GUI>/libonnxruntime.so"
        COMMENT "Copying libonnxruntime.so next to executable"
    )
    add_custom_command(TARGET GUI POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${ORT_LIB_DIR}/libonnxruntime.so.1.26.0"
            "$<TARGET_FILE_DIR:GUI>/libonnxruntime.so.1.26.0"
    )
endif()

# Copy detection model
add_custom_command(TARGET GUI POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_FILE_DIR:GUI>/models"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/models/crabs_yolov8n.onnx"
        "$<TARGET_FILE_DIR:GUI>/models/crabs_yolov8n.onnx"
    COMMENT "Copying crab detection model to build output"
)

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
