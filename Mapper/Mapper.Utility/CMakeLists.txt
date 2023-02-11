set (TARGET Mapper.Utility)

set(SOURCE_FILES
        enum_AirLine.h
        enum_History.h
        enum_Program.h
        feature.h
        feature.cpp
        logicOfProgram.cpp
        logicOfProgram.h)

add_library(${TARGET} STATIC ${SOURCE_FILES})

target_link_libraries(${TARGET} 
        PUBLIC libpqxx::pqxx)

target_include_directories(${TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
