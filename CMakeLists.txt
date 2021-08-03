#cmake_minimum_required(VERSION 3.13)
#project(bammiWeb)
#
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fexceptions")
#
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/target)
##set(CMAKE_EXECUTABLE_SUFFIX ".html")
#
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
##find_package(SDL2 REQUIRED)
##include_directories(bammi ${SDL2_INCLUDE_DIRS})
#
#add_executable(bammi "")
#
#
#add_subdirectory(src)
#add_subdirectory(third-party)
#target_include_directories(bammi PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
##target_link_libraries(bammi PUBLIC -L${CMAKE_CURRENT_SOURCE_DIR}/lib/)
#target_link_libraries(bammi PUBLIC SDL2)
#
#
##target_link_libraries(bammi ${SDL2_LIBRARIES})
#
##set_target_properties(bammi
##	PROPERTIES
##	LINK_FLAGS
##	"-O2 -s USE_SDL=2 -s USE_WEBGL2=1 -s ASSERTIONS=1 -s SINGLE_FILE"
#
##)
#MESSAGE(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

cmake_minimum_required(VERSION 3.13)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(Bammi)

link_directories(bammi PUBLIC ${CMAKE_SOURCE_DIR}/lib)

#find_package(SDL2 REQUIRED)
add_executable(bammi "")

target_include_directories(bammi PUBLIC ${CMAKE_SOURCE_DIR}/include/)

add_subdirectory(src)
target_link_libraries(bammi PUBLIC SDL2)
target_link_libraries(bammi PUBLIC SDL2main)
target_link_libraries(bammi PUBLIC SDL2_image)
target_link_libraries(bammi PUBLIC SDL2_ttf)