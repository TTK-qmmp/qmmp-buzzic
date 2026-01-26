cmake_minimum_required(VERSION 3.0)

project(buzzic)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-multichar")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-multichar")

set(HEADERS
    Buzzic2.h
    Instruments.h
    Operations.h
)

set(SOURCES
    Buzzic2.cpp
    Instruments.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}${STATIC_LIB_SUFFIX})

install(TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT library
)

install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/lib${PROJECT_NAME})
