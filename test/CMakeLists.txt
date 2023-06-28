cmake_minimum_required(VERSION 3.5)

project(AudioMetaEditor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Test REQUIRED)


add_executable(AudioMetaEditorTest
  ../audiometadatawidget.h
  ../audiometadatawidget.cpp

  test_meta_parsing.cpp
)

add_test(NAME Test COMMAND AudioMetaEditorTest)

target_compile_definitions(AudioMetaEditorTest PRIVATE TEST_RUN)

configure_file(beep.mp3 ${CMAKE_CURRENT_BINARY_DIR}/beep.mp3 COPYONLY)
configure_file(beep-intersect.mp3 ${CMAKE_CURRENT_BINARY_DIR}/beep-intersect.mp3 COPYONLY)
configure_file(beep-empty.wav ${CMAKE_CURRENT_BINARY_DIR}/beep-empty.wav COPYONLY)

#set(tag_DIR "D:/CppLibs/taglib")
target_include_directories(AudioMetaEditorTest PRIVATE ${tag_DIR}/include)
target_link_directories(AudioMetaEditorTest PRIVATE ${tag_DIR}/lib)
target_link_libraries(AudioMetaEditorTest PRIVATE tag Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Test)

