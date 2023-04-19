set (TARGET Mapper.Arch)

set(SOURCE_FILES
       Arch.cpp
       BaseDataType.h
       IRepository.h
       Passport.h
       ContainerOfModels.h
       Person.h
       Connector.h
       Repository.h 
       Timer.h 
       ThreadPool.h)

add_executable(${TARGET} Arch.cpp)

target_link_libraries(${TARGET} 
        PUBLIC PostgreSQL::pq libpqxx::pqxx)

target_include_directories(${TARGET}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)

