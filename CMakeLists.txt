cmake_minimum_required(VERSION 3.28)
project(VillageDefence LANGUAGES CXX)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://gitcode.com/gh_mirrors/sf/SFML.git # accelerate https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)
FetchContent_Declare(JSON
        GIT_REPOSITORY https://gitcode.com/gh_mirrors/js/json.git # accelerate https://github.com/nlohmann/json.git
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

if (CMAKE_GENERATOR MATCHES "Visual Studio")
    file(COPY res DESTINATION ${CMAKE_BINARY_DIR}/Debug)
    file(COPY res DESTINATION ${CMAKE_BINARY_DIR}/Release)
elseif (CMAKE_GENERATOR STREQUAL "Ninja")
    file(COPY res DESTINATION ${CMAKE_BINARY_DIR}/)
endif ()

target_link_libraries(main PRIVATE sfml-graphics) # SFML/Graphics.hpp
target_link_libraries(main PRIVATE sfml-audio) # support for SFML/Audio.hpp
target_link_libraries(main PRIVATE nlohmann_json) # support JSON
target_compile_features(main PRIVATE cxx_std_17)

if (WIN32)
    add_custom_command(
            TARGET main
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
            VERBATIM)
endif ()
