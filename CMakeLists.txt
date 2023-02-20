project(Data-Mapper)

cmake_minimum_required(VERSION 3.17.0)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CXX_EXTENSIONS off)



if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.0/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif()

#list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES
        libtool/2.4.6
        libpq/14.5
        libpqxx/7.7.4
        GENERATORS cmake_find_package_multi)

conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE .
        REMOTE conancenter
        BUILD missing
        INSTALL_FOLDER ${CMAKE_BINARY_DIR}/Conan
        SETTINGS ${settings})

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/Conan)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

link_directories(${CMAKE_SOURCE_DIR})

find_package(libpqxx REQUIRED)

add_subdirectory(Mapper)