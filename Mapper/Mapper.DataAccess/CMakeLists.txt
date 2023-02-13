set (TARGET Mapper.DataAccess)

set(SOURCE_FILES
        Irepository.h
        Irepository.h
        Repository.cpp
        )

add_library(${TARGET} STATIC ${SOURCE_FILES})

target_link_libraries(${TARGET} 
        PUBLIC PostgreSQL::pq libpqxx::pqxx)

target_include_directories(${TARGET} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/)