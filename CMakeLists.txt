cmake_minimum_required(VERSION 3.13)
project(modkey-trigger VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ruta a Hyprland que clonaste
set(HYPRLAND_DIR "${CMAKE_SOURCE_DIR}/../hyprland")  # ajusta si está en otro sitio

include_directories(
    ${HYPRLAND_DIR}/
    ${HYPRLAND_DIR}/subprojects/wlroots/include
    (/usr/include/pixman-1)

)

add_library(modkey-trigger SHARED modkey-trigger.cpp)

target_compile_definitions(modkey-trigger PRIVATE WL_EGL_PLATFORM=1)
