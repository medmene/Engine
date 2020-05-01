cmake_minimum_required(VERSION 3.13)
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


set_property(TARGET GameEngine PROPERTY CXX_STANDARD 17)
set_property(TARGET GameEngine PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET GameEngine PROPERTY CXX_EXTENSIONS OFF)

target_include_directories(GameEngine PRIVATE sources)
target_include_directories(GameEngine PRIVATE engine)

target_link_libraries(GameEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/engine/SDL/SDL2.lib)
target_link_libraries(GameEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/engine/SDL/SDL2main.lib)
target_link_libraries(GameEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/engine/SDL/SDL2_image.lib)
target_link_libraries(GameEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/engine/SDL/SDL2_ttf.lib)


install(TARGETS GameEngine RUNTIME DESTINATION bin)

# Include Game sources
target_sources(GameEngine PRIVATE
	sources/Game_sources/main.cpp
)

target_sources(GameEngine PRIVATE
	sources/Game_sources/include/GameWindow.h
	sources/Game_sources/include/Level1.h
)

target_sources(GameEngine PRIVATE
	sources/Game_sources/src/GameWindow.cpp
	sources/Game_sources/src/Level1.cpp
)

# Include Engine
target_sources(GameEngine PRIVATE
  	engine/include/Core.h
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
	engine/include/Physics.h
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
	engine/src/Physics.cpp
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
