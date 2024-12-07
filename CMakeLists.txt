cmake_minimum_required(VERSION 3.30)
project(untitled3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
  Core
  Gui
  Widgets
  REQUIRED)

add_executable(untitled3
        src/main.cpp
        src/mainwnd.cpp
        src/mainwnd.hpp
        src/mainwnd.ui
        src/TriangleWidget.cpp
        src/TriangleWidget.hpp
        src/ControlWidget.cpp
        src/ControlWidget.hpp
        src/ShapeWidget.cpp
        src/ShapeWidget.hpp
        src/RelationWidget.cpp
        src/RelationWidget.hpp
        src/EllipseWidget.cpp
        src/EllipseWidget.hpp
        src/RectangleWidget.cpp
        src/RectangleWidget.hpp
        src/ShapeType.hpp
        src/ShapeFactory.cpp
        src/ShapeFactory.hpp
)
target_link_libraries(untitled3
  Qt::Core
  Qt::Gui
  Qt::Widgets
)
#
#if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
#    set(DEBUG_SUFFIX)
#    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
#        set(DEBUG_SUFFIX "d")
#    endif()
#    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
#    if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
#        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#        if(NOT EXISTS "${QT_INSTALL_PATH}/bin")
#            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
#        endif()
#    endif()
#    if(EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E make_directory
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
#    endif()
#    foreach(QT_LIB Core Gui Widgets )
#        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#                COMMAND ${CMAKE_COMMAND} -E copy
#                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
#                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
#    endforeach(QT_LIB)
#endif()
