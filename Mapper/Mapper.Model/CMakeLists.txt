set(TARGET Mapper.Model)

set(SOURCE_FILES
        AirLine.h
        AirLine.cpp
        Information.h
        Information.cpp
        Passport.h
        Passport.cpp
        Person.h
        Person.cpp)

add_library(${TARGET} STATIC ${SOURCE_FILES})

target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
