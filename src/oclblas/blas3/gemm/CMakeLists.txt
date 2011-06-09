set(target oclgemm)

# look automatically for source and header files...
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
file(GLOB kernels ${CMAKE_CURRENT_SOURCE_DIR}/kernels/*.ocl)

# define library...
add_library(${target}
	${sources}
)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/gemm_kernels.h ${CMAKE_CURRENT_SOURCE_DIR}/gemm_kernels.c
    COMMAND perl ${CMAKE_CURRENT_SOURCE_DIR}/createHeader.pl
    DEPENDS ${kernels}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(gemm_kernels DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/gemm_kernels.h ${CMAKE_CURRENT_SOURCE_DIR}/gemm_kernels.c) 
add_dependencies(${target} gemm_kernels)
