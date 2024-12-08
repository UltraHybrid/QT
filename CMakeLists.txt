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
        src/widgets/TriangleWidget.cpp
        src/widgets/TriangleWidget.hpp
        src/widgets/PaintPanel.hpp
        src/widgets/PaintPanel.cpp
        src/widgets/ShapeWidget.cpp
        src/widgets/ShapeWidget.hpp
        src/widgets/RelationWidget.cpp
        src/widgets/RelationWidget.hpp
        src/widgets/EllipseWidget.cpp
        src/widgets/EllipseWidget.hpp
        src/widgets/RectangleWidget.cpp
        src/widgets/RectangleWidget.hpp
        src/ShapeType.hpp
        src/ShapeFactory.cpp
        src/ShapeFactory.hpp
        src/ShapeInfo.cpp
        src/ShapeInfo.hpp
        src/control/AbstractController.cpp
        src/control/AbstractController.hpp
        src/control/ControlManager.cpp
        src/control/ControlManager.hpp
        src/control/CreateController.cpp
        src/control/CreateController.hpp
        src/control/MoveController.cpp
        src/control/MoveController.hpp
        src/control/RelationController.cpp
        src/control/RelationController.hpp
        src/control/DeleteController.cpp
        src/control/DeleteController.hpp
)

target_include_directories(untitled3 PUBLIC
        src/
        src/widgets
        src/control
)
target_link_libraries(untitled3
  Qt::Core
  Qt::Gui
  Qt::Widgets
)
