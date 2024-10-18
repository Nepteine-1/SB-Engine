cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 11)

project($ENV{TITLE})

if(UNIX)
    set (CMAKE_CXX_FLAGS "-no-pie")
endif()

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE) # Comment for static linking, uncomment for dynamic linking
    set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/../library/SFML-2.6.1/lib/cmake)
    find_package(SFML 2.6 COMPONENTS graphics window system audio network)
    include_directories(${PROJECT_SOURCE_DIR}/../library/SFML-2.6.1/include
                        ${PROJECT_SOURCE_DIR}/../library)
endif()

set(PERMISSIONS OWNER_READ 
    OWNER_WRITE 
    OWNER_READ
    OWNER_EXECUTE 
    GROUP_EXECUTE 
    WORLD_EXECUTE
)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/../src)
include_directories(${SRC_DIR})

file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/../src/*.cpp)
file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/../src/*.hpp)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS})
    
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system 
    sfml-audio
    sfml-network
)

if(UNIX)
    install(FILES ${PROJECT_NAME}  DESTINATION ${PROJECT_SOURCE_DIR}/.. PERMISSIONS ${PERMISSIONS} )
endif()