set(target ocltest_test)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(${target} ${sources})

target_link_libraries(${target}
	ocltest
)

add_test(${target} ${target})
