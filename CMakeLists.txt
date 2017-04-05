cmake_minimum_required(VERSION 2.8)
project(csvfilter)
add_definitions( -std=c++11 )
find_package(Boost COMPONENTS regex program_options)
include_directories( ${Boost_INCLUDE_DIRS})
add_executable(csvfilter ${CMAKE_SOURCE_DIR}/main.cpp )
target_link_libraries(csvfilter ${Boost_LIBRARIES} )

# Install targets.
install( TARGETS csvfilter
    RUNTIME DESTINATION bin
    )
