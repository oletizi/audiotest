cmake_minimum_required(VERSION 3.15)
project(audiotest C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH /usr/local/lib/cmake/)
include_directories(/usr/local/include/)
link_directories(/usr/local/lib/)
find_package(SndFile REQUIRED)

add_executable(audiotest
        src/main.c src/sndfile_utils.c src/sndfile_utils.h src/sndio_utils.c src/sndio_utils.h)

target_link_libraries(audiotest soundio SndFile)

# print all the cmake variables
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
