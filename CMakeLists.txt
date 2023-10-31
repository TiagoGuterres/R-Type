cmake_minimum_required(VERSION 3.0)

project(rtype)

# set the C++ standard to C++ 23
set (CMAKE_CXX_STANDARD 23)

# Inclure le sous-module SFML
add_subdirectory(SFML)

# faire que les hpp se la sfml soit accessible
include_directories(SFML/include)

# thread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# glob recursive of all files in src/Server for the server executable
file(GLOB_RECURSE SERVER_SOURCES
     "src/Server/*.hpp"
     "src/Server/*.cpp"
)

# glob recursive of all files in src/Client for the client executable
file(GLOB_RECURSE CLIENT_SOURCES
     "src/Client/*.hpp"
     "src/Client/*.cpp"
)

# Votre code source pour l'exécutable server
add_executable(r-type_server ${SERVER_SOURCES})

# Votre code source pour l'exécutable client
add_executable(r-type_client ${CLIENT_SOURCES})

foreach(file ${SERVER_SOURCES})
    # print the file name
    message(STATUS "Found file: ${file}")
    if (file MATCHES ".*.hpp")
        get_filename_component(MYFILE_DIR ${file} DIRECTORY)
        include_directories(${MYFILE_DIR})
    endif()
    
endforeach()

foreach(file ${CLIENT_SOURCES})
    # print the file name
    message(STATUS "Found file: ${file}")
    if (file MATCHES ".*.hpp")
        get_filename_component(MYFILE_DIR ${file} DIRECTORY)
        include_directories(${MYFILE_DIR})
    endif()
endforeach()

# Lier votre exécutable avec les bibliothèques SFML
target_link_libraries(r-type_server sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
target_link_libraries(r-type_client sfml-graphics sfml-window sfml-system sfml-network sfml-audio)

# Link thread
# target_link_libraries(r-type_server pthread)
# target_link_libraries(r-type_client pthread)
