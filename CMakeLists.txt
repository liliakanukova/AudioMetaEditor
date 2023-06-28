cmake_minimum_required(VERSION 3.5)

project(AudioMetaEditor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_executable(AudioMetaEditor
  main.cpp

  mainwindow.h
  mainwindow.cpp

  scaledsvgwidget.h
  scaledsvgwidget.cpp

  audiofiledropreceiver.h
  audiofiledropreceiver.cpp

  audiometadatawidget.h
  audiometadatawidget.cpp

  filelistwidget.h
  filelistwidget.cpp

  openfilebutton.h
  openfilebutton.cpp

  mainwindow.ui
  resources.qrc
)

enable_testing()
add_subdirectory(test)

#set(tag_DIR "D:/CppLibs/taglib")
target_include_directories(AudioMetaEditor PRIVATE ${tag_DIR}/include)
target_link_directories(AudioMetaEditor PRIVATE ${tag_DIR}/lib)
target_link_libraries(AudioMetaEditor PRIVATE tag Qt${QT_VERSION_MAJOR}::Widgets)
