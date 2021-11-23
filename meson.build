project('hummingbird', 'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++20',
  ],
)

vulkan = dependency('vulkan')
x11 = dependency('x11')
glfw = dependency('glfw3')

sources = files([
  'src/app.hpp',
  'src/app.cpp',
  'src/main.cpp',
])

hummingbird = executable(
  'hummingbird',
  sources,
  dependencies : [
    vulkan,
    x11,
    glfw,
  ],
)

test('basic', hummingbird)