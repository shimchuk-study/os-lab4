cmake_minimum_required(VERSION 3.5)

project(os_lab4 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(
  MOC_HEADERS
  src/btree.hpp
  src/filename.hpp
  src/btree.tcc
  src/filenametree.hpp
  src/treebuilder.hpp
)

set(
  SOURCES 
  src/main.cpp
  src/filename.cpp
  src/filenametree.cpp
  src/treebuilder.cpp
)

if(ANDROID)
  add_library(os_lab4 SHARED)
else()
  add_executable(
    os_lab4
    ${SOURCES}
  )
endif()

target_link_libraries(os_lab4 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
