cmake_minimum_required(VERSION 3.16)
project(GameEngine)

set(DEFAULT_CMAKE_BUILD_TYPE Release)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_CMAKE_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE ${DEFAULT_CMAKE_BUILD_TYPE}
      CACHE STRING "Choose the type of build." FORCE)

  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE
               PROPERTY STRINGS Debug Release MinSizeRel RelWithDebInfo)
endif()

add_executable(GameEngine "")

#set_target_properties(GameEngine
#    PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
#    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
#    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
#)

if(MSVC)
	set(MSVC_STATIC_RUNTIME ON CACHE BOOL "Visual Studio runtime type" FORCE)
	#add_definitions(-DEXCLUDE_ENTRY_POINT)
    set_target_properties(GameEngine PROPERTIES LINK_FLAGS "/INCREMENTAL /LTCG")
endif()

#TODO add /MT && /MTd into project after configure and "Link library dependences"

set_property(TARGET GameEngine PROPERTY CXX_STANDARD 17)
set_property(TARGET GameEngine PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET GameEngine PROPERTY CXX_EXTENSIONS OFF)
set_property(TARGET GameEngine PROPERTY CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set_property(TARGET GameEngine PROPERTY CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

target_include_directories(GameEngine PRIVATE sources)
target_include_directories(GameEngine PRIVATE engine)

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

install(TARGETS GameEngine RUNTIME DESTINATION bin)

# Include Game sources
target_sources(GameEngine PRIVATE
	sources/Game_sources/main.cpp
)

target_sources(GameEngine PRIVATE
	sources/Game_sources/include/GameWindow.h
	sources/Game_sources/include/GameInterface.h
	sources/Game_sources/include/LevelBase.h
	sources/Game_sources/include/Menu.h
	sources/Game_sources/include/Level1.h
	#sources/Game_sources/include/Level2.h
	#sources/Game_sources/include/Level3.h
	#sources/Game_sources/include/Level4.h
	#sources/Game_sources/include/Level5.h
	#sources/Game_sources/include/LevelController.h
)

target_sources(GameEngine PRIVATE
	sources/Game_sources/src/GameWindow.cpp
	sources/Game_sources/src/GameInterface.cpp
	sources/Game_sources/src/LevelBase.cpp
	sources/Game_sources/src/Menu.cpp
	sources/Game_sources/src/Level1.cpp
	#sources/Game_sources/src/Level2.cpp
	#sources/Game_sources/src/Level3.cpp
	#sources/Game_sources/src/Level4.cpp
	#sources/Game_sources/src/Level5.cpp
	#sources/Game_sources/src/LevelController.cpp
)

# Include Engine
target_sources(GameEngine PRIVATE
  	engine/include/Core.h
  	engine/include/base_defs.h
  	engine/include/Fps.h
  	engine/include/MouseInput.h
  	engine/include/KeyboardInput.h
  	engine/include/Camera.h
  	engine/include/Label.h
  	engine/include/Button.h
	engine/include/Vector2.h
	engine/include/Vector3.h
	engine/include/Color.h
	engine/include/Player.h
	engine/include/Utils.h
	engine/include/GameObject.h
	engine/include/ResourceManager.h
	engine/include/Animator.h
	engine/include/PassabilityMap.h
	engine/include/Character.h
	engine/include/NPC.h
	engine/include/PathFinder.h
	engine/include/MovingController.h
	engine/include/SoundManager.h
	engine/include/KeyboardBinds.h
	engine/include/BehaviourController.h
	engine/include/TextBubble.h
	engine/include/GameModeChangeController.h
	engine/include/Window.h
	engine/include/WindowManager.h
	engine/include/BaseObject.h
	engine/include/BaseWindow.h
)

target_sources(GameEngine PRIVATE
  	engine/src/MouseInput.cpp
  	engine/src/KeyboardInput.cpp
  	engine/src/Camera.cpp
  	engine/src/Label.cpp
  	engine/src/Button.cpp
  	engine/src/Vector2.cpp
  	engine/src/Vector3.cpp
  	engine/src/Color.cpp
  	engine/src/Player.cpp
	engine/src/GameObject.cpp
	engine/src/ResourceManager.cpp
	engine/src/Animator.cpp
	engine/src/PassabilityMap.cpp
	engine/src/NPC.cpp
	engine/src/PathFinder.cpp
	engine/src/MovingController.cpp
	engine/src/SoundManager.cpp
	engine/src/BehaviourController.cpp
	engine/src/TextBubble.cpp
	engine/src/GameModeChangeController.cpp
	engine/src/Window.cpp
	engine/src/WindowManager.cpp
	engine/src/BaseObject.cpp
	engine/src/BaseWindow.cpp
)

# Include lib pugi XML
target_sources(GameEngine PRIVATE
	engine/pugixml/pugiconfig.hpp
	engine/pugixml/pugixml.cpp
	engine/pugixml/pugixml.hpp
)


###################################################
###################################################
###################################################
