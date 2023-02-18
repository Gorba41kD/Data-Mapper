set (TARGET Mapper.DataAccess)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CXX_EXTENSIONS off)

set(SOURCE_FILES
        Irepository.h
        Repository.cpp
        Repository.h
        )

add_library(${TARGET} STATIC ${SOURCE_FILES})

target_link_libraries(${TARGET} 
        PRIVATE libpqxx::pqxx PostgreSQL::pq
        PUBLIC Mapper.Utility
        )

target_include_directories(${TARGET}
       PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)
