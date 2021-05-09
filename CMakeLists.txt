project("cryptolib" DESCRIPTION "Cryoto Library")


if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

set(SourceFiles
        src/algobjs/blowfish.cpp
        src/algobjs/textmanager.cpp
        src/crypters/decrypter.cpp
        src/crypters/encrypter.cpp
)

add_library(${PROJECT_NAME} STATIC ${SourceFiles})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src/algobjs
        ${CMAKE_CURRENT_SOURCE_DIR}/src/crypters
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(CMAKE_INSTALL_PREFIX
    "${CMAKE_SOURCE_DIR}/install"
    CACHE PATH "Where the library will be installed to" FORCE
)

set(public_headers
    include/cryptolib/blockmodes.hpp
    include/cryptolib/blowfish.hpp
    include/cryptolib/cryptobase.hpp
    include/cryptolib/decrypter.hpp
    include/cryptolib/encrypter.hpp
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

include(GNUInstallDirs)

# paths for binaries and headers
install(TARGETS ${PROJECT_NAME}
    EXPORT "${PROJECT_NAME}Config"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} # lib
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # bin
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # include
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME} # include/SomeLibrary
)
# CMake config name, namespace and path
install(
    EXPORT "${PROJECT_NAME}Config"
    FILE "${PROJECT_NAME}Config.cmake"
    NAMESPACE some::
    DESTINATION cmake
)
