#!/bin/sh

ls "${MESON_BUILD_ROOT}/shaders" &> /dev/null || mkdir "${MESON_BUILD_ROOT}/shaders"

cd "${MESON_SOURCE_ROOT}/src/shaders/"

for shader in "$@"; do
    glslc -fshader-stage="$shader" "$shader.glsl" -o "${MESON_BUILD_ROOT}/shaders/$shader.spv" && echo "Shader built: $shader";
done
