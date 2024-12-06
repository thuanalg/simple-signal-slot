# Add main.cpp file of the project root directory as a source file
project(simple_signal_slot_project)
set(SOURCE_LIB_FILES simple_signal_slot.cpp simple_signal_slot.h 
	implement/simple_implement_signal_slot.cpp 
	implement/simple_implement_signal_slot.h)
	
#project(simplelog)
set(SOURCE_SIMPLELOG_LIB_FILES simplelog/simplelog.c 
	simplelog/simplelog.h simplelog/simplelog_config.h)	

set(SOURCE_BINCPP_FILES test/main.cpp)
set(SOURCE_BIN_TMP_FILES tmp/main.c)

# Add executable target with source files listed in SOURCE_FILES variable

#add_compile_definitions(EXPORT_DLL_API_SIMPLE_LOG simple_signal_slot_lib)
#add_compile_definitions(_CRT_SECURE_NO_WARNINGS simple_signal_slot_lib)
include_directories(./ ./implement)
add_library(simple_signal_slot_lib SHARED ${SOURCE_LIB_FILES})
target_compile_definitions(simple_signal_slot_lib PRIVATE EXPORT_DLL_API_SIMPLE_SIGNAL_SLOT=1)
target_compile_definitions(simple_signal_slot_lib PUBLIC _CRT_SECURE_NO_WARNINGS=1)
if(DEFINED UNIX_LINUX)
	target_compile_definitions(simple_signal_slot_lib PUBLIC UNIX_LINUX=1)
endif()

add_library(simpleloglib SHARED ${SOURCE_SIMPLELOG_LIB_FILES})
target_compile_definitions(simpleloglib PRIVATE EXPORT_DLL_API_SIMPLE_LOG=1)
target_compile_definitions(simpleloglib PUBLIC _CRT_SECURE_NO_WARNINGS=1)
if(DEFINED UNIX_LINUX)
	target_compile_definitions(simpleloglib PUBLIC UNIX_LINUX=1)
endif()




include_directories(./ ./simplelog)
add_executable(simple_signal_slot_example ${SOURCE_BINCPP_FILES})
target_compile_definitions(simple_signal_slot_example PUBLIC _CRT_SECURE_NO_WARNINGS=1)
if(DEFINED UNIX_LINUX)
	target_compile_definitions(simple_signal_slot_example PUBLIC UNIX_LINUX=1)
endif()

add_executable(ztest ${SOURCE_BIN_TMP_FILES})
target_compile_definitions(ztest PUBLIC _CRT_SECURE_NO_WARNINGS=1)

include_directories(./simplelog)
target_link_libraries(simple_signal_slot_lib 
	simpleloglib
)

target_link_libraries(simple_signal_slot_example 
	simple_signal_slot_lib
	simpleloglib
)