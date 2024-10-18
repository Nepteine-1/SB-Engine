cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

#Set a normal variable to a given value
// set(CMAKE_CXX_FLAGS "-no-pie")
set(PROJECT_NAME SB_Engine)
project(${PROJECT_NAME})

# Very important, otherwise your executable will be considered as a shared library by your OS and no as an executable
# set (CMAKE_CXX_FLAGS "-no-pie")
set (SRC_DIR ${PROJECT_SOURCE_DIR}/../src)

set(SFML_STATIC_LIBRARIES TRUE) # Comment for static linking, uncomment for dynamic linking
set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/../library/SFML-2.6.1/lib/cmake)
find_package(SFML 2.6 COMPONENTS graphics window system audio network)

set(PERMISSIONS OWNER_READ 
    OWNER_WRITE 
    OWNER_READ
    OWNER_EXECUTE 
    GROUP_EXECUTE 
    WORLD_EXECUTE
)

include_directories(${SRC_DIR}
		    ${PROJECT_SOURCE_DIR}/../library/SFML-2.6.1/include
		    ${PROJECT_SOURCE_DIR}/../library)

# Select the sources files to use in the current directory
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/../src/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/../src/*.hpp)

add_executable(${PROJECT_NAME} # Name of the executable
    ${SOURCES}
    ${HEADERS})
    
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system 
    sfml-audio
    sfml-network
    #pthread
)

#install(FILES ${PROJECT_NAME}  DESTINATION ${PROJECT_SOURCE_DIR}/.. PERMISSIONS ${PERMISSIONS} )
