set(TARGET Mapper.Exe)

add_executable(${TARGET} main.cpp)

target_link_libraries(${TARGET} PRIVATE Models)
target_include_directories(${TARGET} PRIVATE "${PROJECT_SOURCE_DIR}/Mapper/Mapper.Model")

target_link_libraries(${TARGET} PRIVATE Utility)
target_include_directories(${TARGET} PRIVATE "${PROJECT_SOURCE_DIR}/Mapper/Mapper.Utility")

target_link_libraries(${TARGET} PRIVATE DataAccess)
target_include_directories(${TARGET} PRIVATE "${PROJECT_SOURCE_DIR}/Mapper/Mapper.DataAccess")