cmake_minimum_required (VERSION 2.8)
set (PROJECT CrystallViewer)
set (SOURCES src/main.cpp
             src/geometryengine.cpp
             src/mainwidget.cpp
             src/mshader.cpp
             src/mvertexshader.cpp
             src/mfragmentshader.cpp
             src/mprogram.cpp
             src/utils.cpp
)
set (QT_USE_QTOPENGL TRUE)
set (HEADERS headers/geometryengine.h
             headers/mainwidget.h
             
)
set (CMAKE_PREFIX_PATH /Users/vitalii.shastun/Development/qtgit/qtbase)

set (RESOURCES resources/texture.qrc
               resources/shaders.qrc
)

project (${PROJECT})

set (CMAKE_BUILD_TYPE Debug)

set (MOC_HEADERS 
            headers/mainwidget.h
)

find_package(Qt5Core)
#find_package(Qt5Widgets)
find_package(Qt5Xml)
find_package(Qt5OpenGL)
find_package(Qt5Gui)
find_package(Qt5OpenGLExtensions)
find_package(Qt5LinguistTools)
find_package(Qt5PrintSupport)
find_package(Qt5UiTools)

include_directories (headers)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Xml_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5OpenGL_INCLUDE_DIRS})
include_directories(${Qt5OpenGLExtensions_INCLUDE_DIRS})
include_directories(${Qt5Sql_INCLUDE_DIRS})
#include_directories(${Qt5Gui_INCLUDE_DIRS} ${AIR_QT_PATH}/include/QtGui/5.2.1/QtGui)  # Fix it
include_directories(${Qt5Gui_INCLUDE_DIRS})
include_directories("${AIR_QT_PATH}/src/3rdparty/sqlite")
include_directories("${AIR_QT_DIR}/qtmacextras/src/macextras")
include_directories("${AIR_QT_PATH}/src/plugins/platforms/cocoa")

include_directories (${GLUT_INCLUDE_DIRS})
add_definitions (${QT_DEFINITIONS} -Werror -Wall)

QT5_WRAP_CPP (MOC_SOURCES ${MOC_HEADERS})
QT5_ADD_RESOURCES(QT_RESOURCES ${RESOURCES})

set (DEPENDANCY_LIBRARIES
                Qt5::Gui
				Qt5::Core
				Qt5::Xml
				Qt5::OpenGL
				Qt5::OpenGLExtensions
                Qt5::UiTools
                Qt5::PrintSupport
                "-framework Carbon"
                "-framework Cocoa"
                "-framework OpenGL"
                "-framework IOKit"
				"${CMAKE_PREFIX_PATH}/plugins/platforms/libqcocoa_debug.a"
				"${CMAKE_PREFIX_PATH}/plugins/printsupport/libcocoaprintersupport_debug.a"
				"${CMAKE_PREFIX_PATH}/lib/libQt5PlatformSupport_debug.a"
				c++
                z 
    )

add_executable (${PROJECT} ${SOURCES} ${MOC_SOURCES} ${QT_RESOURCES} ${HEADERS})
target_link_libraries (${PROJECT} ${DEPENDANCY_LIBRARIES})
