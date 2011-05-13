INCLUDE(${PROJECT_SOURCE_DIR}/config/library_dirs.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/libraries.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/include_dirs.txt)	

include_directories(
	.
)

link_libraries(${target}
	rt
)

add_subdirectory(opencl)
add_subdirectory(oclutils)
#add_subdirectory(blas1)
#add_subdirectory(blas2)
add_subdirectory(blas3)

set(target oclblas)

link_libraries(${target}
	opencl
	oclutils
#	oclblas1
#	oclblas2
	oclblas3
)

# look automatically for source and header files...
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# define library...
add_library(${target}
	${sources}
)
