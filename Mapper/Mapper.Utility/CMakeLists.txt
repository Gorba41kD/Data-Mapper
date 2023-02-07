set (TARGET Mapper.Utility)

set(SOURCE_FILES
        enum_AirLine.h
        enum_History.h
        enum_Program.h
        feature.h
        feature.cpp
        logicOfProgram.cpp
        logicOfProgram.h)

add_library(Utility STATIC ${SOURCE_FILES})