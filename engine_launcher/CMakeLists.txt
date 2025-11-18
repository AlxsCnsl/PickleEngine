add_auto_executable(
    engine_launcher
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/header"
)

target_link_libraries(engine_launcher PRIVATE
  # link modules you want statically if needed:
  Pickle::Module::window_render
  Pickle::Module::app_loop
  Pickle::Module::easy_drawing
  Pickle::Module::keyboard_manager
  Pickle::Module::ecs_sprite
  Pickle::Module::rgb_pallet

  #link libs
  SDL3::SDL3
  SDL3_image::SDL3_image
  entt

)
set_target_properties(engine_launcher PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
