INCLUDE(${PROJECT_SOURCE_DIR}/config/library_dirs.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/libraries.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/include_dirs.txt)	

set(target opencl_test)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(${target} ${sources})

target_link_libraries(${target}
	opencl
)

add_test(${target} ${target})
