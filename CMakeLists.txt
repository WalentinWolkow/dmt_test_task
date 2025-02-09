cmake_minimum_required(VERSION 3.31.5)

set(PROJECT_NAME testTask)

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

set(TARGET_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

project(${PROJECT_NAME} VERSION ${TARGET_VERSION})

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES_DIR src)
set(HEADERS_DIR ${SOURCES_DIR}/headers)
set(UI_DIR ui)

aux_source_directory(${SOURCES_DIR} SOURCES)
file(GLOB HEADERS ${HEADERS_DIR}/*.h)
file(GLOB UIS ${UI_DIR}/*.ui)
qt5_wrap_ui(UI_HEADERS ${UIS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI_HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${HEADERS_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
