set(sgemm_target opencl_sgemm_test)
file(GLOB sgemm_sources ${CMAKE_CURRENT_SOURCE_DIR}/sgemm*.c)
file(GLOB sgemm_headers ${CMAKE_CURRENT_SOURCE_DIR}/sgemm*.h)
add_executable(${sgemm_target} ${sgemm_sources})

#set(dgemm_target opencl_dgemm_test)
#file(GLOB dgemm_sources ${CMAKE_CURRENT_SOURCE_DIR}/dgemm*.c)
#file(GLOB dgemm_headers ${CMAKE_CURRENT_SOURCE_DIR}/dgemm*.h)
#add_executable(${dgemm_target} ${dgemm_sources})

link_libraries(
  oclblas
)

add_test(
	${sgemm_target} ${sgemm_target}
#	${dgemm_target} ${dgemm_target}
)
