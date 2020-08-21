cmake_minimum_required(VERSION 3.16)
project(GameEngine)

set(DEFAULT_CMAKE_BUILD_TYPE Release)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_CMAKE_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE ${DEFAULT_CMAKE_BUILD_TYPE}
      CACHE STRING "Choose the type of build." FORCE)

  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE
               PROPERTY STRINGS Debug RelWithDebInfo) #Release
endif()

add_executable(GameEngine "")

set_target_properties(GameEngine
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

if(MSVC)
	add_definitions(/D "_CRT_SECURE_NO_WARNINGS")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

set_property(TARGET GameEngine PROPERTY CXX_STANDARD 17)
set_property(TARGET GameEngine PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET GameEngine PROPERTY CXX_EXTENSIONS OFF)

target_include_directories(GameEngine PRIVATE sources)
target_include_directories(GameEngine PRIVATE engine)


# SDL library
############################################
add_library(SDL2 STATIC IMPORTED)
add_library(SDL2main STATIC IMPORTED)
add_library(SDL2_image STATIC IMPORTED)
add_library(SDL2_ttf STATIC IMPORTED)
add_library(SDL2_mixer STATIC IMPORTED)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/engine/SDL)

SET_TARGET_PROPERTIES(SDL2 PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/engine/SDL/SDL2.lib)
SET_TARGET_PROPERTIES(SDL2main PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/engine/SDL/SDL2main.lib)
SET_TARGET_PROPERTIES(SDL2_image PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/engine/SDL/SDL2_image.lib)
SET_TARGET_PROPERTIES(SDL2_ttf PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/engine/SDL/SDL2_ttf.lib)
SET_TARGET_PROPERTIES(SDL2_mixer PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/engine/SDL/SDL2_mixer.lib)

target_compile_features(SDL2 INTERFACE cxx_std_11)
target_compile_features(SDL2main INTERFACE cxx_std_11)
target_compile_features(SDL2_image INTERFACE cxx_std_11)
target_compile_features(SDL2_ttf INTERFACE cxx_std_11)
target_compile_features(SDL2_mixer INTERFACE cxx_std_11)

target_link_libraries(GameEngine PRIVATE SDL2)
target_link_libraries(GameEngine PRIVATE SDL2main)
target_link_libraries(GameEngine PRIVATE SDL2_image)
target_link_libraries(GameEngine PRIVATE SDL2_ttf)
target_link_libraries(GameEngine PRIVATE SDL2_mixer)
############################################

install(TARGETS GameEngine RUNTIME DESTINATION bin)

#########################################
# make MSVC folders for client
set(GAME_SOURCES_INK "")
list(APPEND GAME_SOURCES_INK
	sources/Game_sources/include/GameWindow.h
	sources/Game_sources/include/GameInterface.h
	sources/Game_sources/include/GameSceneBase.h
	sources/Game_sources/include/Menu.h
	sources/Game_sources/include/Level1.h
)
set(GAME_SOURCES_SRC "")
list(APPEND GAME_SOURCES_SRC
	sources/Game_sources/src/GameWindow.cpp
	sources/Game_sources/src/GameInterface.cpp
	sources/Game_sources/src/GameSceneBase.cpp
	sources/Game_sources/src/Menu.cpp
	sources/Game_sources/src/Level1.cpp
)

# Include Game sources
source_group(Game_sources FILES sources/Game_sources/main.cpp)
source_group(Game_sources\\include FILES ${GAME_SOURCES_INK} *.h)
source_group(Game_sources\\src FILES ${GAME_SOURCES_SRC} *.cpp)
target_sources(GameEngine PRIVATE sources/Game_sources/main.cpp )
target_sources(GameEngine PRIVATE ${GAME_SOURCES_INK})
target_sources(GameEngine PRIVATE ${GAME_SOURCES_SRC})
#########################################


#########################################
#Includes
set(ENGINE_TOOLS_INK "")
list(APPEND ENGINE_TOOLS_INK
	engine/include/tools/Utils.h
  	engine/include/tools/Fps.h
	engine/include/tools/ActionMap.h
	engine/include/tools/FunctionParam.h
)

set(ENGINE_INPUT_INK "")
list(APPEND ENGINE_INPUT_INK
  	engine/include/input/MouseInput.h
	engine/include/input/KeyboardBinds.h
  	engine/include/input/KeyboardInput.h
	engine/include/input/SoundManager.h
  	engine/include/input/Camera.h
)

set(ENGINE_TYPES_INK "")
list(APPEND ENGINE_TYPES_INK
	engine/include/types/Vector2.h
	engine/include/types/Vector3.h
	engine/include/types/Color.h
)

set(ENGINE_GAME_OBJECTS_INK "")
list(APPEND ENGINE_GAME_OBJECTS_INK
	engine/include/game_object/BaseObject.h
	engine/include/game_object/GameObject.h
  	engine/include/game_object/Label.h
  	engine/include/game_object/Button.h
	engine/include/game_object/TextBubble.h
  	engine/include/game_object/CheckBox.h
	#NPCs
	engine/include/game_object/npc/Player.h
	engine/include/game_object/npc/NPC.h
	engine/include/game_object/npc/Character.h
)

set(ENGINE_WINDOW_INK "")
list(APPEND ENGINE_WINDOW_INK
	engine/include/window/WindowManager.h
	engine/include/window/BaseWindow.h
	engine/include/window/Window.h
)

set(ENGINE_CONTROLLER_INK "")
list(APPEND ENGINE_CONTROLLER_INK
	engine/include/controller/ResourceManager.h
	engine/include/controller/ScriptManager.h
	engine/include/controller/TextManager.h
	engine/include/controller/PassabilityMap.h
	engine/include/controller/PathFinder.h
	engine/include/controller/MovingController.h
	engine/include/controller/BehaviourController.h
	engine/include/controller/Animator.h
	#Other
	
	engine/include/controller/other/Areas.h
	engine/include/controller/other/DirectionSettings.h
)

set(ENGINE_SOURCES_INK "")
list(APPEND ENGINE_SOURCES_INK
	#Core
	engine/include/Core.h
  	engine/include/base_defs.h
)

#Sources
set(ENGINE_TOOLS_SRC "")
list(APPEND ENGINE_TOOLS_SRC
	engine/src/tools/ActionMap.cpp
	engine/src/tools/Utils.cpp
)

set(ENGINE_INPUT_SRC "")
list(APPEND ENGINE_INPUT_SRC
	engine/src/input/MouseInput.cpp
  	engine/src/input/KeyboardInput.cpp
  	engine/src/input/Camera.cpp
	engine/src/input/SoundManager.cpp
)

set(ENGINE_TYPES_SRC "")
list(APPEND ENGINE_TYPES_SRC
  	engine/src/types/Vector2.cpp
  	engine/src/types/Vector3.cpp
  	engine/src/types/Color.cpp
)

set(ENGINE_GAME_OBJECTS_SRC "")
list(APPEND ENGINE_GAME_OBJECTS_SRC
	engine/src/game_object/BaseObject.cpp
	engine/src/game_object/GameObject.cpp
  	engine/src/game_object/Label.cpp
  	engine/src/game_object/Button.cpp
	engine/src/game_object/CheckBox.cpp
	engine/src/game_object/TextBubble.cpp
	#NPCs
	engine/src/game_object/npc/Player.cpp
	engine/src/game_object/npc/NPC.cpp
)

set(ENGINE_WINDOW_SRC "")
list(APPEND ENGINE_WINDOW_SRC
	engine/src/window/WindowManager.cpp
	engine/src/window/BaseWindow.cpp
	engine/src/window/Window.cpp
)

set(ENGINE_CONTROLLER_SRC "")
list(APPEND ENGINE_CONTROLLER_SRC

	engine/src/controller/ResourceManager.cpp
	engine/src/controller/ScriptManager.cpp
	engine/src/controller/TextManager.cpp
	engine/src/controller/PassabilityMap.cpp
	engine/src/controller/PathFinder.cpp
	engine/src/controller/MovingController.cpp
	engine/src/controller/BehaviourController.cpp
	engine/src/controller/Animator.cpp
	#Other
	engine/src/controller/other/Areas.cpp
	engine/src/controller/other/DirectionSettings.cpp
)

# Include Engine
source_group(Engine_sources\\include FILES ${ENGINE_SOURCES_INK} *.h)
source_group(Engine_sources\\include\\tools FILES ${ENGINE_TOOLS_INK} *.h)
source_group(Engine_sources\\include\\input FILES ${ENGINE_INPUT_INK} *.h)
source_group(Engine_sources\\include\\types FILES ${ENGINE_TYPES_INK} *.h)
source_group(Engine_sources\\include\\game_object FILES ${ENGINE_GAME_OBJECTS_INK} *.h)
source_group(Engine_sources\\include\\window FILES ${ENGINE_WINDOW_INK} *.h)
source_group(Engine_sources\\include\\controller FILES ${ENGINE_CONTROLLER_INK} *.h)

source_group(Engine_sources\\src\\tools FILES ${ENGINE_TOOLS_SRC} *.cpp)
source_group(Engine_sources\\src\\input FILES ${ENGINE_INPUT_SRC} *.cpp)
source_group(Engine_sources\\src\\types FILES ${ENGINE_TYPES_SRC} *.cpp)
source_group(Engine_sources\\src\\game_object FILES ${ENGINE_GAME_OBJECTS_SRC} *.cpp)
source_group(Engine_sources\\src\\window FILES ${ENGINE_WINDOW_SRC} *.cpp)
source_group(Engine_sources\\src\\controller FILES ${ENGINE_CONTROLLER_SRC} *.cpp)


target_sources(GameEngine PRIVATE ${ENGINE_SOURCES_INK})
target_sources(GameEngine PRIVATE ${ENGINE_TOOLS_INK})
target_sources(GameEngine PRIVATE ${ENGINE_INPUT_INK})
target_sources(GameEngine PRIVATE ${ENGINE_TYPES_INK})
target_sources(GameEngine PRIVATE ${ENGINE_GAME_OBJECTS_INK})
target_sources(GameEngine PRIVATE ${ENGINE_WINDOW_INK})
target_sources(GameEngine PRIVATE ${ENGINE_CONTROLLER_INK})

target_sources(GameEngine PRIVATE ${ENGINE_TOOLS_SRC})
target_sources(GameEngine PRIVATE ${ENGINE_INPUT_SRC})
target_sources(GameEngine PRIVATE ${ENGINE_TYPES_SRC})
target_sources(GameEngine PRIVATE ${ENGINE_GAME_OBJECTS_SRC})
target_sources(GameEngine PRIVATE ${ENGINE_WINDOW_SRC})
target_sources(GameEngine PRIVATE ${ENGINE_CONTROLLER_SRC})
#########################################

#########################################
# Include lib pugi XML
set(LIB_PUGIXML "")
list(APPEND LIB_PUGIXML
	engine/pugixml/pugiconfig.hpp
	engine/pugixml/pugixml.cpp
	engine/pugixml/pugixml.hpp
)

source_group(pugixml_lib FILES ${LIB_PUGIXML} *.h)
target_sources(GameEngine PRIVATE ${LIB_PUGIXML})
#########################################

#########################################
# Include lib SDL
set(LIB_SDL2 "")
list(APPEND LIB_SDL2
	engine/SDL/begin_code.h
	engine/SDL/close_code.h
	engine/SDL/SDL.h
	engine/SDL/SDL_assert.h
	engine/SDL/SDL_atomic.h
	engine/SDL/SDL_audio.h
	engine/SDL/SDL_bits.h
	engine/SDL/SDL_blendmode.h
	engine/SDL/SDL_clipboard.h
	engine/SDL/SDL_config.h
	engine/SDL/SDL_config_android.h
	engine/SDL/SDL_config_iphoneos.h
	engine/SDL/SDL_config_macosx.h
	engine/SDL/SDL_config_minimal.h
	engine/SDL/SDL_config_pandora.h
	engine/SDL/SDL_config_psp.h
	engine/SDL/SDL_config_windows.h
	engine/SDL/SDL_config_winrt.h
	engine/SDL/SDL_config_wiz.h
	engine/SDL/SDL_copying.h
	engine/SDL/SDL_cpuinfo.h
	engine/SDL/SDL_egl.h
	engine/SDL/SDL_endian.h
	engine/SDL/SDL_error.h
	engine/SDL/SDL_events.h
	engine/SDL/SDL_filesystem.h
	engine/SDL/SDL_gamecontroller.h
	engine/SDL/SDL_gesture.h
	engine/SDL/SDL_haptic.h
	engine/SDL/SDL_hints.h
	engine/SDL/SDL_image.h
	engine/SDL/SDL_joystick.h
	engine/SDL/SDL_keyboard.h
	engine/SDL/SDL_keycode.h
	engine/SDL/SDL_loadso.h
	engine/SDL/SDL_log.h
	engine/SDL/SDL_main.h
	engine/SDL/SDL_messagebox.h
	engine/SDL/SDL_mixer.h
	engine/SDL/SDL_mouse.h
	engine/SDL/SDL_mutex.h
	engine/SDL/SDL_name.h
	engine/SDL/SDL_opengl.h
	engine/SDL/SDL_opengl_glext.h
	engine/SDL/SDL_opengles.h
	engine/SDL/SDL_opengles2.h
	engine/SDL/SDL_opengles2_gl2.h
	engine/SDL/SDL_opengles2_gl2ext.h
	engine/SDL/SDL_opengles2_gl2platform.h
	engine/SDL/SDL_opengles2_khrplatform.h
	engine/SDL/SDL_pixels.h
	engine/SDL/SDL_platform.h
	engine/SDL/SDL_power.h
	engine/SDL/SDL_quit.h
	engine/SDL/SDL_rect.h
	engine/SDL/SDL_render.h
	engine/SDL/SDL_revision.h
	engine/SDL/SDL_rwops.h
	engine/SDL/SDL_scancode.h
	engine/SDL/SDL_sensor.h
	engine/SDL/SDL_shape.h
	engine/SDL/SDL_stdinc.h
	engine/SDL/SDL_surface.h
	engine/SDL/SDL_system.h
	engine/SDL/SDL_syswm.h
	engine/SDL/SDL_test.h
	engine/SDL/SDL_test_assert.h
	engine/SDL/SDL_test_common.h
	engine/SDL/SDL_test_crc32.h
	engine/SDL/SDL_test_font.h
	engine/SDL/SDL_test_fuzzer.h
	engine/SDL/SDL_test_harness.h
	engine/SDL/SDL_test_images.h
	engine/SDL/SDL_test_log.h
	engine/SDL/SDL_test_md5.h
	engine/SDL/SDL_test_memory.h
	engine/SDL/SDL_test_random.h
	engine/SDL/SDL_thread.h
	engine/SDL/SDL_timer.h
	engine/SDL/SDL_touch.h
	engine/SDL/SDL_ttf.h
	engine/SDL/SDL_types.h
	engine/SDL/SDL_version.h
	engine/SDL/SDL_video.h
	engine/SDL/SDL_vulkan.h
)

source_group(SDL_lib FILES ${LIB_SDL2} *.h)
target_sources(GameEngine PRIVATE ${LIB_SDL2})
#########################################

###################################################
###################################################
###################################################
