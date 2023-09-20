cmake_minimum_required(VERSION 3.0.2 FATAL_ERROR)
project(qb VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/qbdevice-api-7.x.x/serial)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/qbdevice-api-7.x.x/qbrobotics-driver)

include_directories(include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs)
message(${PROJECT_NAME})
# Build Settings
add_executable(${PROJECT_NAME}
  # src/main.cpp
  src/hand_controller.cpp
  # src/hand_controller_backup0911.cpp
  )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/libs//qbdevice-api-7.x.x/build/qbrobotics-driver/libqbrobotics_driver.a # FIXME: why specify type?
  ${CMAKE_CURRENT_SOURCE_DIR}/libs//qbdevice-api-7.x.x/build/serial/libSerial.a
)

# C++ Settings

if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
 set_target_properties(
   ${PROJECT_NAME}
   PROPERTIES
     CXX_STANDARD 14
     CXX_STANDARD_REQUIRED ON
      COMPILE_FLAGS "-m64"
      LINK_FLAGS "-m64")
else()
 set_target_properties(
   ${PROJECT_NAME}
   PROPERTIES
     CXX_STANDARD 14
     CXX_STANDARD_REQUIRED ON
      COMPILE_FLAGS "-m32"
      LINK_FLAGS "-m32")
endif()

# Installation
install(
  TARGETS
    ${PROJECT_NAME}
  RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}
)