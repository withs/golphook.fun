cmake_minimum_required(VERSION 3.20)
project(golphook_fun)

set(CMAKE_CXX_STANDARD 20)

set(CONAN_DISABLE_CHECK_COMPILER TRUE)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Using fake windows conan")

    include(_fakewin/conan/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    include(conan/conanbuildinfo.cmake)
    conan_basic_setup()
endif()

file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE min exts/minhook/*.c)

add_library(${PROJECT_NAME} SHARED ${min} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC exts/minhook/include)
target_include_directories(${PROJECT_NAME} PUBLIC exts/directx/Include)

target_include_directories(${PROJECT_NAME} PUBLIC src/App)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Using fake windows headers")
    target_include_directories(${PROJECT_NAME} PUBLIC _fakewin/win/cppwinrt)
    target_include_directories(${PROJECT_NAME} PUBLIC _fakewin/win/shared)
    target_include_directories(${PROJECT_NAME} PUBLIC _fakewin/win/ucrt)
    target_include_directories(${PROJECT_NAME} PUBLIC _fakewin/win/um)
    target_include_directories(${PROJECT_NAME} PUBLIC _fakewin/win/winrt)

    target_include_directories(${PROJECT_NAME} PUBLIC _fakeWin/directx)

endif()

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/exts/directx/Lib/x86/d3dx9.lib)
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/exts/directx/Lib/x86/d3d9.lib)