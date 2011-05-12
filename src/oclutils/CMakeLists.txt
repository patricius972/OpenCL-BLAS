set(target oclutils)


INCLUDE(${PROJECT_SOURCE_DIR}/config/platforms/opencl/library_dirs.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/platforms/opencl/libraries.txt)	
INCLUDE(${PROJECT_SOURCE_DIR}/config/platforms/opencl/include_dirs.txt)	

link_libraries(${target}
)

#### behind this line everything is standard! Do not change if necessary! ####

# look automatically for source and header files...
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# define library...
add_library(${target}
	${sources}
)
