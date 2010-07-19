# Top-level CMakeLists.txt

# Required commands
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (OurAdventure)

# Should we enable tests?
OPTION (ENABLE_TESTS
        "Enable the building and running of unit tests." OFF)

# Project variables
ADD_DEFINITIONS ("-Wall -Wextra -ansi -pedantic")

SET (DEFAULT_CAVE_FILE ${CMAKE_INSTALL_PREFIX}/share/OurAdventure/cave.dat)
CONFIGURE_FILE (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
    )

# Executables
ADD_SUBDIRECTORY (src)

IF (ENABLE_TESTS)
  ADD_SUBDIRECTORY (tests)
  ENABLE_TESTING ()
ENDIF (ENABLE_TESTS)

# Install cave file
INSTALL (FILES ${CMAKE_CURRENT_SOURCE_DIR}/cave.dat
         DESTINATION share/OurAdventure)
