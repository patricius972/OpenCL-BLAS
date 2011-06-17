INCLUDE(${PROJECT_SOURCE_DIR}/config/library_dirs.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/libraries.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/include_dirs.txt)	

link_libraries(
	opencl
	testutils
	trimpblas
	oclblas
)

#add_subdirectory(blas1)
#add_subdirectory(blas2)
add_subdirectory(blas3)
