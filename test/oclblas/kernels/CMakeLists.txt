add_executable(GetMatrixFloat GetMatrixFloat_test.c)

link_libraries(
  oclblas
)

add_test(
	GetMatrixFloat GetMatrixFloat
)
