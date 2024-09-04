# Add main.cpp file of the project root directory as a source file
project(simple_signal_slot_project)
set(SOURCE_LIB_FILES simple_signal_slot.cpp simple_signal_slot.h 
	implement/simple_implement_signal_slot.cpp 
	implement/simple_implement_signal_slot.h)

set(SOURCE_BINCPP_FILES test/main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable

#add_compile_definitions(EXPORT_DLL_API_SIMPLE_LOG simple_signal_slot_lib)
#add_compile_definitions(_CRT_SECURE_NO_WARNINGS simple_signal_slot_lib)
include_directories(./ ./implement)
add_library(simple_signal_slot_lib SHARED ${SOURCE_LIB_FILES})
target_compile_definitions(simple_signal_slot_lib PRIVATE EXPORT_DLL_API_SIMPLE_SIGNAL_SLOT=1)
target_compile_definitions(simple_signal_slot_lib PUBLIC _CRT_SECURE_NO_WARNINGS=1)




include_directories(./)
add_executable(simple_signal_slot_example ${SOURCE_BINCPP_FILES})
target_compile_definitions(simple_signal_slot_example PUBLIC _CRT_SECURE_NO_WARNINGS=1)

#include_directories(./)



target_link_libraries(simple_signal_slot_example 
	simple_signal_slot_lib
)