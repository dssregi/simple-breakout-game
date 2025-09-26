# Create the executable
add_executable(breakout main.cpp)

# Find SFML with its required components
# The COMPONENTS part is crucial for finding the correct libraries
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Link your executable to the SFML libraries
target_link_libraries(breakout PRIVATE 
   SFML::Graphics 
   SFML::Window 
   SFML::System
   core_lib
)

target_compile_features(breakout PRIVATE cxx_std_17)
target_compile_options(breakout PRIVATE 
    -Wall 
    -Wextra 
    -Wpedantic
)

target_include_directories(breakout PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../../include>
)
