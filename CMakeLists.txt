PROJECT(pnetlib)
SET(CMAKE_C_FLAGS "-ggdb -O0")
ADD_EXECUTABLE(pnet main.c pnet-error.c pnet-connection.c pnet-tcp-connection.c)

TARGET_LINK_LIBRARIES(pnet pthread  )
