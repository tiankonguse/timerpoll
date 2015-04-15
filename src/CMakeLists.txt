###################################################################
#
#	add by tiankonguse 20:37 2015/4/15
#
###################################################################

SET(CMAKE_CXX_FLAGS " -g -Wall -o2")

SET(timerpoll_lib_path ${PROJECT_SOURCE_DIR}/lib)
SET(timerpoll_src_path ${PROJECT_SOURCE_DIR}/src)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)

AUX_SOURCE_DIRECTORY(${timerpoll_src_path} X_SRC)
ADD_LIBRARY(timerpoll STATIC ${X_SRC})

SET_TARGET_PROPERTIES(timerpoll PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${timerpoll_lib_path}")
