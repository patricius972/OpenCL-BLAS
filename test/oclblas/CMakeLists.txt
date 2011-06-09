INCLUDE(${PROJECT_SOURCE_DIR}/config/library_dirs.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/libraries.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/include_dirs.txt)	

link_libraries(
	testutils
	trimpblas
	oclblas
)

add_subdirectory(kernels)
add_subdirectory(blas3)
