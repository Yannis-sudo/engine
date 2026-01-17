cmake_minimum_required(VERSION 3.15)

# Projektname und Sprache festlegen
project(ChessEngine LANGUAGES CXX)

# C++‑Standard setzen (z. B. C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Quellcode‑Dateien hinzufügen
add_executable(engine
    # main dictonary
    src/bestmove.cpp
    src/minimax.cpp
    src/main.cpp

    # global
    global/src/bitboard.cpp
    global/src/board.cpp
    global/src/generatemovesvar.cpp
    global/src/makemove.cpp

    # generatemoves
    generatemoves/src/attacks.cpp
    generatemoves/src/generatemoves.cpp
    generatemoves/src/pawnattacks.cpp
    generatemoves/src/masks.cpp
    generatemoves/src/isgameover.cpp

    # evaluate
    evaluate/src/evaluate.cpp
    evaluate/src/positioneval.cpp
)


# Optional: Include‑Verzeichnisse angeben
target_include_directories(engine PRIVATE 
    ${PROJECT_SOURCE_DIR}/include 
    ${PROJECT_SOURCE_DIR}/global/include
    ${PROJECT_SOURCE_DIR}/generatemoves/include
    ${PROJECT_SOURCE_DIR}/evaluate/include
)

find_package(Threads)
find_package(ZLIB)
find_package(OpenSSL)

if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

if (MSVC)
    set(Boost_USE_STATIC_LIBS "On")
    find_package( Boost 1.70 COMPONENTS system thread regex REQUIRED )
else()
    find_package( Boost 1.70 COMPONENTS system thread REQUIRED )
endif()

include_directories(${Boost_INCLUDE_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}lib//include)

include_directories("${PROJECT_INCLUDE_DIR}")
