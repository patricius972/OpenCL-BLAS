set(target trimp-blas1)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(${target}
	${sources}
)

target_link_libraries(${target}
)
