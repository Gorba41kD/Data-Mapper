set(TARGET Mapper.Exe)

add_executable(${TARGET} main.cpp)

target_link_libraries(${TARGET} 
    PUBLIC Mapper.Model Mapper.Utility Mapper.DataAccess)
