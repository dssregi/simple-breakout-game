find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

# Add a new static library target for the core component
add_library(core_lib STATIC 
   background.cpp
   entity.cpp
   ball.cpp
   paddle.cpp
   interactions.cpp
   brick.cpp
   game.cpp
)

# Link core_lib to the SFML Graphics module
# This is a PRIVATE dependency because other targets that link to core_lib
# don't need to know about its internal use of SFML.
target_link_libraries(core_lib PRIVATE SFML::Graphics)

# Tell the core library where its public headers are
#vtarget_include_directories(core_lib PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/../include/core
# )

# Add the path to the app's headers, as the core library needs to include them.
target_include_directories(core_lib PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include
)
