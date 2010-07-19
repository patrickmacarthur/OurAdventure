# Top-level CMakeLists.txt

# Required commands
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (OurAdventure)

# Should we enable tests?
OPTION (ENABLE_TESTS
        "Enable the building and running of unit tests." OFF)

# Project variables
ADD_DEFINITIONS ("-Wall -Wextra -ansi -pedantic")

# Executables
ADD_SUBDIRECTORY (src)

IF (ENABLE_TESTS)
  ADD_SUBDIRECTORY (tests)
  ENABLE_TESTING ()
ENDIF (ENABLE_TESTS)
