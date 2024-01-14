cmake_minimum_required(VERSION 3.12)
project(devicemonitoringserver CXX)

FILE(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/handlers/*.h ${CMAKE_CURRENT_SOURCE_DIR}/handlers/*.cpp
                  ${CMAKE_CURRENT_SOURCE_DIR}/server/*.h ${CMAKE_CURRENT_SOURCE_DIR}/server/*.cpp
				  ${CMAKE_CURRENT_SOURCE_DIR}/servermock/*.h ${CMAKE_CURRENT_SOURCE_DIR}/servermock/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
set(GCC_OPTIONS -g -O0 -Werror -Wall -Wextra -fsanitize=leak -fsanitize=undefined -fsanitize=address)
target_compile_options(${PROJECT_NAME} PRIVATE ${GCC_OPTIONS})
target_link_options(${PROJECT_NAME} PRIVATE ${GCC_OPTIONS})

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${PROJECT_NAME})
