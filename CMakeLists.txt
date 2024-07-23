cmake_minimum_required(VERSION 3.5.0)
project(Toolbar VERSION 0.1.0 LANGUAGES C CXX)

if (WIN32)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL3 REQUIRED sdl3)
    pkg_check_modules(SDL3_IMAGE REQUIRED SDL3_image)
elseif(APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
    find_package(SDL3 REQUIRED)
    find_package(SDL3_image REQUIRED)
endif()

set(SOURCES
    toolbar_define.cpp
    toolbar_main.cpp
    toolbar_component.cpp
    toolbar_texture.cpp
    toolbar_function.cpp
)

add_executable(Toolbar ${SOURCES})

if(WIN32)
    target_include_directories(Toolbar PRIVATE
    ${SDL3_INCLUDE_DIRS}
    ${SDL3_IMAGE_INCLUDE_DIRS}
    )

    target_link_libraries(Toolbar PRIVATE
        ${SDL3_LIBRARIES}
        ${SDL3_IMAGE_LIBRARIES}
    )
elseif(APPLE)
    target_link_libraries(Toolbar SDL3::SDL3 SDL3_image::SDL3_image)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
