# This is needed for fallbacks in situations where OpenCL does not 
# support double precision...
include_directories (
 ${PROJECT_SOURCE_DIR}/src/plugins/atlas/lib
)

link_libraries(${target}
	upla-base
	upla-atlas
	rt
	upla-opencl
)

add_subdirectory(oclutils)
#add_subdirectory(blas1)
#add_subdirectory(blas2)
add_subdirectory(blas3)

set(target oclblas)

link_libraries(${target}
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
