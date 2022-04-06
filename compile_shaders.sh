#!/bin/sh

ls "${MESON_BUILD_ROOT}/shaders" &> /dev/null || mkdir "${MESON_BUILD_ROOT}/shaders"

cd "${MESON_SOURCE_ROOT}/src/shaders/"

glslc -fshader-stage=vert "vert.glsl" -o "${MESON_BUILD_ROOT}/shaders/vert.spv"
glslc -fshader-stage=frag "frag.glsl" -o "${MESON_BUILD_ROOT}/shaders/frag.spv"
