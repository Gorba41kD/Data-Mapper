set(TARGET Mapper.Exe)

add_executable(${TARGET} main.cpp)

target_link_libraries(${TARGET} 
    INTERFACE Mapper.Model Mapper.Utility Mapper.DataAccess)

target_link_libraries(${TARGET} 
        INTERFACE PostgreSQL::pq libpqxx::pqxx)
