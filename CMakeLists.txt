set(PROJECT Data-Mapper)

cmake_minimum_required(VERSION 3.17.0)


list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

add_subdirectory(Mapper)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.0/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
            TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES
        libpq/14.5
        libpqxx/7.7.4)

conan_cmake_autodetect(settings)
conan_cmake_install(PATH_OR_REFERENCE .
        REMOTE conancenter
        BUILD missing
        INSTALL_FOLDER ${CMAKE_BINARY_DIR}/Conan
        SETTINGS ${settings})

list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR}/Conan)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

find_package(libpqxx REQUIRED)
