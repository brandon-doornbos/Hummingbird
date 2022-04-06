project('hummingbird', 'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++20',
  ],
)

glm = dependency('glm')
vulkan = dependency('vulkan')
glfw = dependency('glfw3')

sources = files([
  'src/util.hpp',
  'src/util.cpp',
  'src/app.hpp',
  'src/app.cpp',
  'src/main.cpp',
])

hummingbird = executable(
  'hummingbird',
  sources,
  dependencies : [
    glm,
    vulkan,
    glfw,
  ],
)

shaders = [
  'vert',
  'frag',
]

find_program('glslc')
run_target(
  'shaders',
  command : [
    'compile_shaders.sh',
    shaders,
  ],
)

test('basic', files(['test.sh']))

