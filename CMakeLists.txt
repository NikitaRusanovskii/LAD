cmake_minimum_required(VERSION 3.20)
project(LAD_APP)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(external)

### Здесь загрузка библиотек с гита, трогать не рекомендую ###
include(FetchContent)
FetchContent_Declare(
    ixwebsocket
    GIT_REPOSITORY "https://github.com/machinezone/IXWebSocket"
    GIT_TAG master
)
FetchContent_Declare(
  nlohmann_json
  GIT_REPOSITORY "https://github.com/nlohmann/json.git"
  GIT_TAG v3.11.3
)

set(USE_TLS OFF CACHE BOOL "" FORCE)
set(USE_ZLIB ON CACHE BOOL "" FORCE)
set(ZLIB_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/external/zlib" CACHE PATH "" FORCE)
set(ZLIB_LIBRARY zlibstatic CACHE STRING "" FORCE)
set(ZLIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/zlib" CACHE PATH "" FORCE)

FetchContent_MakeAvailable(ixwebsocket nlohmann_json)
### --------------------------------------------------------###

target_link_libraries(ixwebsocket PRIVATE ZLIB::ZLIB)

add_library(lad_lib STATIC
    src/CommandIO.cpp
    src/Helpers.cpp
    src/Interpretator.cpp
    src/Reciever.cpp
    src/Memory.cpp
    src/RegularStorage.cpp
    src/Grid.cpp
    include/CommandIO.h
    include/Helpers.h
    include/Interpretator.h
    include/Reciever.h
    include/token_converter.h
    include/tokenizator.h
    include/Memory.h
    include/RegularStorage.h
    include/Grid.h
)	

target_include_directories(lad_lib PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_executable(LAD_APP "src/LAD_AP v.2.0.0.cpp")
target_link_libraries(LAD_APP PRIVATE
                        lad_lib
                        ixwebsocket
                        nlohmann_json)

### Переключайте переменную BUILD_TESTS на OFF, если не нужно собирать тесты ###
if(BUILD_TESTS)
    include(FetchContent)
    
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.x
    )
    
    FetchContent_MakeAvailable(googletest)
    
    add_executable(TEST_APP tests/test_token_converter.cpp)
    
    target_link_libraries(TEST_APP PRIVATE 
        lad_lib
        GTest::gtest_main
        GTest::gmock_main
    )
    
    target_include_directories(TEST_APP PRIVATE include)
    
    include(GoogleTest)
    gtest_discover_tests(TEST_APP
        TEST_PREFIX "LAD_"
        TEST_SUFFIX ""
        PROPERTIES LABELS "LAD"
    )
endif()
