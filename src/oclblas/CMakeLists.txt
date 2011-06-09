INCLUDE(${PROJECT_SOURCE_DIR}/config/library_dirs.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/libraries.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/include_dirs.txt)	

link_libraries(${target}
	rt
	opencl
	oclblas1
	oclblas2
	oclblas3
)

add_subdirectory(blas1)
add_subdirectory(blas2)
add_subdirectory(blas3)

set(target oclblas)

# look automatically for source and header files...
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB kernels ${CMAKE_CURRENT_SOURCE_DIR}/kernels/*.ocl)

# define library...
add_library(${target} SHARED
	${sources}
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/oclStdKernels.h ${CMAKE_CURRENT_SOURCE_DIR}/oclStdKernels.c
    COMMAND perl ${CMAKE_CURRENT_SOURCE_DIR}/createHeader.pl
    DEPENDS ${kernels}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(oclStdKernels DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/oclStdKernels.h ${CMAKE_CURRENT_SOURCE_DIR}/oclStdKernels.c) 
add_dependencies(${target} oclStdKernels)
