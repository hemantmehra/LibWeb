# CMakeList.txt : CMake project for LibWeb, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (LibWeb
				"main.cpp" 
				"HTMLToken.h"
				"HTMLToken.cpp"
				"HTMLTokenizer.h"
				"HTMLTokenizer.cpp"
				"Attribute.h"
				"HTMLDocumentParser.h"
				"HTMLDocumentParser.cpp" "Forward.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LibWeb PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
add_subdirectory(DOM)
target_link_libraries(DOM)