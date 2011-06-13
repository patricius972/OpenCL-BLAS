include_directories(
	${PROJECT_SOURCE_DIR}/src
	.
)

add_subdirectory(ocltest)
add_subdirectory(testutils)
add_subdirectory(trimp)
add_subdirectory(opencl)
add_subdirectory(oclblas)
