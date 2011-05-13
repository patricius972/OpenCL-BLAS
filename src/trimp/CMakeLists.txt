add_subdirectory(blas1)
add_subdirectory(blas2)
add_subdirectory(blas3)

set(target trimpblas)

link_libraries(${target}
	trimpblas1
	trimpblas2
	trimpblas3
)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(${target} SHARED
	${sources}
)
