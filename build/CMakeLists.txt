cmake_minimum_required(VERSION 3.5)

#Set a normal variable to a given value
set(PROJECT_NAME $ENV{TITLE})
project(${PROJECT_NAME})

# Very important, otherwise your executable will be considered as a shared library by your OS and no as an executable
set (CMAKE_CXX_FLAGS "-no-pie")
set (SRC_DIR ${PROJECT_SOURCE_DIR}/../src)

set(PERMISSIONS OWNER_READ 
    OWNER_WRITE 
    OWNER_READ
    OWNER_EXECUTE 
    GROUP_EXECUTE 
    WORLD_EXECUTE
)

include_directories(${SRC_DIR})

# Select the sources files to use in the current directory
set( SOURCES
    ${SRC_DIR}/main.cpp

    #--Engine
    ${SRC_DIR}/Engine/Engine.cpp
    ${SRC_DIR}/Engine/EventHandler.cpp

    #--Features
    ${SRC_DIR}/Features/Network/Network.cpp
    ${SRC_DIR}/Features/TimeManager/TimeManager.cpp
    ${SRC_DIR}/Features/Particles/Particule.cpp
    ${SRC_DIR}/Features/Particles/ParticuleGenerator.cpp
    ${SRC_DIR}/Features/Particles/Ball.cpp
    ${SRC_DIR}/Features/NeuralNetwork/NeuralNetwork.cpp
    ${SRC_DIR}/Features/Matrix/Matrix.cpp

    #--Application
    ${SRC_DIR}/Application/App.cpp
    ${SRC_DIR}/Application/Masse.cpp
    ${SRC_DIR}/Application/Resolver.cpp
)

# //   headers file //
set( HEADERS
    #--Engine
    ${SRC_DIR}/Engine/Engine.hpp
    ${SRC_DIR}/Engine/EventHandler.hpp

    #--Features
    ${SRC_DIR}/Features/Network/Network.hpp
    ${SRC_DIR}/Features/TimeManager/TimeManager.hpp
    ${SRC_DIR}/Features/Particles/Particule.hpp
    ${SRC_DIR}/Features/Particles/ParticuleGenerator.hpp
    ${SRC_DIR}/Features/Particles/Ball.hpp
    ${SRC_DIR}/Features/Random/Random.hpp
    ${SRC_DIR}/Features/NeuralNetwork/NeuralNetwork.hpp
    ${SRC_DIR}/Features/Matrix/Matrix.hpp

    #--Application
    ${SRC_DIR}/Application/App.hpp
    ${SRC_DIR}/Application/Masse.hpp
    ${SRC_DIR}/Application/utils.hpp
    ${SRC_DIR}/Application/Resolver.hpp
)

add_executable(${PROJECT_NAME} # Name of the executable
    ${SOURCES}
    ${HEADERS})
    
target_link_libraries(${PROJECT_NAME}
    sfml-graphics
    sfml-window
    sfml-system 
    sfml-audio
    sfml-network
    pthread
)

install(FILES ${PROJECT_NAME}  DESTINATION ${PROJECT_SOURCE_DIR}/.. PERMISSIONS ${PERMISSIONS} )
