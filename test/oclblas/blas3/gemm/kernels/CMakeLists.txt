set(sgemm_kernel sgemm_kernel_test)

file(GLOB sgemm_kernel_sources ${CMAKE_CURRENT_SOURCE_DIR}/sgemm*.c)
add_executable(${sgemm_kernel} ${sgemm_kernel_sources})

add_test(
	${sgemm_kernel} ${sgemm_kernel}
)

target_link_libraries(${sgemm_kernel}
	ocltest
)
