cmake_minimum_required(VERSION 3.21)
project(Hydrus95 LANGUAGES CXX)

#enable_testing()
cmake_policy(SET CMP0077 NEW)
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILT_TYPE Release ... FORCE)
endif()

find_package(Qt6 COMPONENTS Widgets Core Concurrent Sql REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)



if(WIN32)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        find_program(TOOL_WINDEPLOYQT NAMES windeployqt.debug.bat)
    else()
        find_program(TOOL_WINDEPLOYQT NAMES windeployqt)
    endif()
endif()

message("CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")

if(${CMAKE_COMPILER_IS_GNUCXX})
set(FGL_WARNINGS "-Wall -Wextra -Wundef -Wnull-dereference -Wpedantic -Weffc++ -pedantic-errors -Wnoexcept -Wuninitialized -Wunused -Wunused-parameter -Winit-self -Wconversion -Wuseless-cast -Wextra-semi -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override  -Wformat-signedness -Wno-format-zero-length -Wmissing-include-dirs -Wshift-overflow=2 -Walloc-zero -Walloca -Wsign-promo -Wconversion -Wduplicated-branches -Wduplicated-cond -Wshadow -Wshadow=local -Wvirtual-inheritance -Wno-virtual-move-assign -Wunsafe-loop-optimizations -Wnormalized -Wpacked -Wredundant-decls -Wmismatched-tags -Wredundant-tags -Wctor-dtor-privacy -Wdeprecated-copy-dtor -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wzero-as-null-pointer-constant -Wconditionally-supported -Werror=pedantic -Wwrite-strings -Wunused-const-variable=2 -Wdouble-promotion -Wpointer-arith -Wcast-align=strict -Wcast-qual -Wconversion -Wsign-conversion -Wimplicit-fallthrough=1 -Wmisleading-indentation -Wdangling-else -Wdate-time -Wformat=2 -Wformat-overflow=2 -Wformat-signedness -Wformat-truncation=2 -Wswitch-default -Wstrict-overflow=5 -Wstringop-overflow=4 -Warray-bounds=2 -Wattribute-alias=2 -Wcatch-value=2 -Wplacement-new=2 -Wtrampolines -Winvalid-imported-macros -Winvalid-imported-macros")
set(FGL_CONFIG "-std=c++23 -fmax-errors=3 -fconcepts-diagnostics-depth=4 -Werror")
set(FGL_DEBUG "-Og -fverbose-asm -g -fstrict-aliasing -fno-omit-frame-pointer -fstack-check -ftrapv -fverbose-asm -femit-class-debug-always -rdynamic")

#Generates system specific stuff (IE requires AVX)
set(FGL_SYSTEM_SPECIFIC "-march=native -fgcse -fgcse-las -fgcse-sm -fdeclone-ctor-dtor -fdevirtualize-speculatively -ftree-loop-im -fivopts -ftree-loop-ivcanon -fira-hoist-pressure -fsched-pressure -fsched-spec-load -fipa-pta -flto=auto -s -ffat-lto-objects -fno-enforce-eh-specs -fstrict-enums -funroll-loops")
#Generates safe optimization flags
set(FGL_SYSTEM_SAFE "-O3 -fdevirtualize-at-ltrans -fdevirtualize-at-ltrans")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${FGL_CONFIG} ${FGL_DEBUG} -fsanitize=undefined")
set(CMAKE_CXX_FLAGS_SYSTEM "${CMAKE_CXX_FLAGS} ${FLG_CONFIG} -DNDEBUG ${FGL_SYSTEM_SAFE} ${FGL_SYSTEM_SPECIFIC}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${FGL_CONFIG} -DNDEBUG -s ${FGL_SYSTEM_SAFE}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} ${FGL_CONFIG} ${FGL_SYSTEM_SAFE}")
else()
    message("Note that you are compiling Hydrus95 with an unsupported compiler (Only GCC is offically supported) You can still make bug reports but MENTION YOUR COMPILER AND BUILD SYSTEM")
endif()

file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/ui/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/backend/*.cpp")

if(WIN32)
    add_executable(Hydrus95 WIN32 ${SOURCES} ${CMAKE_SOURCE_DIR}/src/main.cpp)
else()
if(${CMAKE_COMPILER_IS_GNUCXX})
    add_executable(Hydrus95 ${SOURCES} ${CMAKE_SOURCE_DIR}/src/main.cpp)
    set_target_properties(Hydrus95 PROPERTIES COMPILE_FLAGS ${CMAKE_CXX_FLAGS} ${FGL_WARNINGS})
else()
    add_executable(Hydrus95 ${SOURCES} ${CMAKE_SOURCE_DIR}/src/main.cpp)
endif()
endif()

target_include_directories(Hydrus95 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(REQUIRED_LIBS Qt6::Widgets Qt6::Core Qt6::Sql Qt6::Concurrent)

target_link_libraries(Hydrus95 ${REQUIRED_LIBS})

add_subdirectory(${CMAKE_SOURCE_DIR}/tests/unit_tests)

if(WIN32)
    add_custom_command(TARGET IDHAN POST_BUILD
            COMMAND ${TOOL_WINDEPLOYQT}
                    $<TARGET_FILE:IDHAN>
            COMMENT "Running windeployqt")
endif()


