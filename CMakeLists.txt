###############################################################################
#
# This is a CMake template for the source top level directory. 
#
# Only some variables have to be set here, which are explained within the file.
#
# Author:  Rick-Rainer Ludwig
# Version: 1.0.0
# Date:    2008-11-07 20:32:00
#
###############################################################################

# minimum required CMake version...
cmake_minimum_required(VERSION 2.6)

#
# set global project information into variables...
# (to be changed)
#
set(PROJECT_NAME      "UPLA")     # no spaces allowed!
set(PROJECT_LONG_NAME "United Platform Linear Algebra Package") # long name if needed
set(PROJECT_FS_NAME   "upla")     # changed name for file system
set(PROJECT_VERSION   "0.0.1")
set(PROJECT_AUTHOR    "Rick-Rainer Ludwig")
set(PROJECT_OWNER     "Rick-Rainer Ludwig")
set(PROJECT_LIFE_TIME "2011")
set(PROJECT_BUGS_TO   "ludwig@puresol-technologies.com")
set(PARALLEL_MODE     "1")               # set 1 for enabled and 0 for disabled

#
# set project type... (C CXX Java)
# (to be changed)
#
set(PROJECT_TYPE C CXX)
enable_testing()

# set project name...
project(${PROJECT_NAME} ${PROJECT_TYPE})

#
# installation path...
# (to be changed)
#
set(CMAKE_INSTALL_PREFIX
  /usr
)

#
# share directory...
# (to be changed, if required only!)
#
set(SHARE_DIRECTORY
  ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_FS_NAME}
)

#
# verbosity... (ON/OFF)
# (to be changed, if required only)
#
set(CMAKE_VERBOSE_MAKEFILE ON)

#
# build type... (Debug, Profile, Release)
# (to be changed)
#
set(CMAKE_BUILD_TYPE Debug)

#
# compiler options for different release type...
# (to be changed, if required only)
#
set(CMAKE_C_FLAGS_DEBUG "-O0 -Wall -Werror -g3 -ansi -std=gnu99")
set(CMAKE_C_FLAGS_PROFILE "-O0 -Wall -Werror -pg -g3 -ansi  -std=gnu99-fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS_RELEASE "-O3 -pipe -fPIC -Wall -Werror -ansi -std=gnu99")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -Werror -g3 -ansi")
set(CMAKE_CXX_FLAGS_PROFILE "-O0 -Wall -Werror -pg -g3 -ansi -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -pipe -fPIC -Wall -Werror -ansi")
set(CMAKE_LD_FLAGS_PROFILE "-fprofile-arcs -ftest-coverage")

#
# subdirectories...
# (to be changed)
#
add_subdirectory(src build)
add_subdirectory(test build/test)

##############################################################################
## behind this line everything is standard! Do not change if not necessary! ##
##############################################################################

#
# create configuration file config.h...
#
configure_file(
  ${PROJECT_SOURCE_DIR}/config.h.in 
  ${PROJECT_SOURCE_DIR}/config.h
)

#
# doc...
# (make doc)
#
ADD_CUSTOM_TARGET(doc
  ./cmake_doc.sh)

#
# pretty...
# (make pretty)
#
ADD_CUSTOM_TARGET(pretty
  ./cmake_pretty.sh)

#
# coverage dashboard... 
# (make coverage)
#
ADD_CUSTOM_TARGET(coverage
  create_gcov.pl . gcov && create_dashboard.pl gcov html)

#
# uninstall support...
# (found at: http://www.cmake.org/Wiki/CMake_FAQ)
# (make uninstall)
#
CONFIGURE_FILE(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall
  "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
