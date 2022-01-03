project('hummingbird', 'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++20',
  ],
)

vulkan = dependency('vulkan')
glfw = dependency('glfw3')

sources = files([
  'src/HB/app.hpp',
  'src/HB/app.cpp',
  'src/main.cpp',
])

hummingbird = executable(
  'hummingbird',
  sources,
  dependencies : [
    vulkan,
    glfw,
  ],
)

test('basic', hummingbird)

