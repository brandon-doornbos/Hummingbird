project('hummingbird', 'cpp',
  version : '0.1.2',
  default_options : [
    'warning_level=3',
    'cpp_std=c++20',
  ],
)

conf_data = configuration_data()
conf_data.set_quoted('ENGINE_NAME', meson.project_name())
conf_data.set_quoted('ENGINE_VERSION', meson.project_version())
conf_data.set_quoted('APP_NAME', 'test_app')
conf_data.set_quoted('APP_VERSION', '0.0.1')
configure_file(
  output : 'config.hpp',
  configuration : conf_data,
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

executable(
  meson.project_name(),
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

