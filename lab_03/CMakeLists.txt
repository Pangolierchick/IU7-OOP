cmake_minimum_required(VERSION 3.5)
project(lab_03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(lab_03 main.cpp
        src/object/model/details/point/point.cpp
        inc/object/model/details/point/point.h
        src/object/model/details/edge/edge.cpp
        inc/object/model/details/edge/edge.h
        src/object/model/details/details.cpp
        inc/object/model/details/details.h
        inc/visitor.h
        inc/object/object.h
        src/object/model/model.cpp
        inc/object/model/model.h
        src/object/composite/composite.cpp
        inc/object/composite/composite.h
        src/object/camera/camera.cpp
        inc/object/camera/camera.h
        src/scene/scene.cpp
        inc/scene/scene.h
        inc/drawer/abstract_drawer.h
        inc/drawer/abstract_drawer_factory.h
        src/managers/draw/draw_manager.cpp
        inc/managers/draw/draw_manager.h
        src/managers/draw/draw_manager_creator.cpp
        inc/managers/draw/draw_manager_creator.h
        inc/managers/base_manager.h
        src/managers/transform/transform_manager.cpp
        inc/managers/transform/transform_manager.h
        src/managers/transform/transform_manager_creator.cpp
        inc/managers/transform/transform_manager_creator.h
        src/managers/scene/scene_manager.cpp
        inc/managers/scene/scene_manager.h
        src/managers/scene/scene_manager_creator.cpp
        inc/managers/scene/scene_manager_creator.h
        inc/builder/base_builder.h
        src/builder/camera/camera_builder.cpp
        inc/builder/camera/camera_builder.h
        src/builder/model/model_builder.cpp
        inc/builder/model/model_builder.h
        src/builder/scene/scene_builder.cpp
        inc/builder/scene/scene_builder.h
        src/load_controller/abstract_load_controller.cpp
        inc/load_controller/abstract_load_controller.h
        inc/loader/base_loader.h
        src/load_controller/model/model_load_controller.cpp
        inc/load_controller/model/model_load_controller.h
        src/loader/model/model_loader_file.cpp
        inc/loader/model/model_loader_file.h
        inc/loader/model/base_model_loader.h
        inc/loader/scene/base_scene_loader.h
        src/loader/scene/scene_loader_file.cpp
        inc/loader/scene/scene_loader_file.h
        inc/loader/camera/base_camera_loader.h
        src/loader/camera/camera_loader_file.cpp
        inc/loader/camera/camera_loader_file.h
        src/load_controller/model/model_load_controller_creator.cpp
        inc/load_controller/model/model_load_controller_creator.h
        src/load_controller/scene/scene_load_controller.cpp
        inc/load_controller/scene/scene_load_controller.h
        src/load_controller/scene/scene_load_controller_creator.cpp
        inc/load_controller/scene/scene_load_controller_creator.h
        src/managers/load/load_manager.cpp
        inc/managers/load/load_manager.h
        src/managers/load/load_manager_creator.cpp
        inc/managers/load/load_manager_creator.h
        src/qt/qt_drawer.cpp inc/qt/qt_drawer.h
        src/qt/qt_drawer_factory.cpp
        inc/qt/qt_drawer_factory.h
        main.cpp
        src/facade/facade.cpp
        inc/facade/facade.h
        inc/error/error.h
        inc/configuration/abstract_configuration.h
        src/configuration/configuration_creator.cpp
        inc/configuration/configuration_creator.h
        src/configuration/libconfig_configuration.cpp
        inc/configuration/libconfig_configuration.h
        inc/command/base_command.h
        src/command/camera_commands.cpp
        inc/command/camera_commands.h
        src/command/model_commands.cpp
        inc/command/model_commands.h
        src/command/scene_commands.cpp
        inc/command/scene_commands.h
        mainwindow.h
        mainwindow.cpp
        design.h)

target_include_directories(${PROJECT_NAME} PRIVATE
        ./inc
        ./src/
        )

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)

target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED} -lconfig++)
