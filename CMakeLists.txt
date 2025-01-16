cmake_minimum_required(VERSION 3.28)
project(VillageDefence LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://gitcode.com/gh_mirrors/sf/SFML.git # mirror of https://github.com/SFML/SFML.git
        GIT_TAG 3.0.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)
FetchContent_Declare(JSON
        GIT_REPOSITORY https://gitcode.com/gh_mirrors/js/json.git # mirror of https://github.com/nlohmann/json.git
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(JSON)

set(SOURCE_DIR src)
aux_source_directory(${SOURCE_DIR} SRC_FILES)
aux_source_directory(${SOURCE_DIR}/GUI GUI_FILES)
aux_source_directory(${SOURCE_DIR}/Utils UTILS_FILES)
aux_source_directory(${SOURCE_DIR}/Widgets WIDGETS_FILES)
add_executable(main ${SRC_FILES} ${GUI_FILES} ${UTILS_FILES} ${WIDGETS_FILES})

file(COPY res DESTINATION ${CMAKE_BINARY_DIR}/)

target_link_libraries(main PRIVATE SFML::Graphics) # SFML/Graphics.hpp
target_link_libraries(main PRIVATE SFML::Audio) # SFML/Audio.hpp
target_link_libraries(main PRIVATE nlohmann_json) # JSON
target_compile_features(main PRIVATE cxx_std_17)
