add_subdirectory(kernels)

set(sgemm_target oclblas_sgemm_test)
file(GLOB sgemm_sources ${CMAKE_CURRENT_SOURCE_DIR}/sgemm*.c)
add_executable(${sgemm_target} ${sgemm_sources})

set(dgemm_target oclblas_dgemm_test)
file(GLOB dgemm_sources ${CMAKE_CURRENT_SOURCE_DIR}/dgemm*.c)
	add_executable(${dgemm_target} ${dgemm_sources})

link_libraries(
  oclblas
)

add_test(
	${sgemm_target} ${sgemm_target}
)

#add_test(
#	${dgemm_target} ${dgemm_target}
#)
