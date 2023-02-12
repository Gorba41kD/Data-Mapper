set (SUBTARGET Mapper.Utility)
set(TARGET ${TARGET}.${SUBTARGET})

set (FOLDER Mapper.Utility)

set(SOURCE_FILES
        enum_AirLine.h
        enum_History.h
        enum_Program.h
        feature.h
        feature.cpp
        logicOfProgram.cpp
        logicOfProgram.h)

add_library(${TARGET} STATIC ${SOURCE_FILES})

set_target_properties(${TARGET} PROPERTIES FOLDER ${FOLDER})

target_link_libraries(${TARGET} 
        PUBLIC PostgreSQL::pq libpqxx::pqxx)

target_include_directories(${TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
