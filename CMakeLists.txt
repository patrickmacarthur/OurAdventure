# Top-level CMakeLists.txt

# Required commands
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (OurAdventure)

# Project variables
ADD_DEFINITIONS ("-Wall -Wextra -ansi -pedantic")

# Executables
ADD_SUBDIRECTORY (src)
