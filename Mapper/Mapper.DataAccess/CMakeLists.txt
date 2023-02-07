set (TARGET Mapper.DataAccess)

set(SOURCE_FILES
        Irepository.h
        Irepository.h
        Repository.cpp
        )

add_library(DataAccess STATIC ${SOURCE_FILES})

#target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/)