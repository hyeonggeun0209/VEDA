# Install script for directory: /Users/jinurung/VEDA/Linux/vote/build/lib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcast.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib" TYPE STATIC_LIBRARY FILES "/Users/jinurung/VEDA/Linux/vote/build/build/lib/libcast.a")
  if(EXISTS "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcast.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcast.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcast.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommon.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib" TYPE STATIC_LIBRARY FILES "/Users/jinurung/VEDA/Linux/vote/build/build/lib/libcommon.a")
  if(EXISTS "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommon.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommon.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommon.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libvector_cast.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib" TYPE STATIC_LIBRARY FILES "/Users/jinurung/VEDA/Linux/vote/build/build/lib/libvector_cast.a")
  if(EXISTS "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libvector_cast.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libvector_cast.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libvector_cast.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libvector_viewer.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib" TYPE STATIC_LIBRARY FILES "/Users/jinurung/VEDA/Linux/vote/build/build/lib/libvector_viewer.a")
  if(EXISTS "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libvector_viewer.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libvector_viewer.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libvector_viewer.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libviewer.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib" TYPE STATIC_LIBRARY FILES "/Users/jinurung/VEDA/Linux/vote/build/build/lib/libviewer.a")
  if(EXISTS "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libviewer.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libviewer.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libviewer.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommunity.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib" TYPE STATIC_LIBRARY FILES "/Users/jinurung/VEDA/Linux/vote/build/build/lib/libcommunity.a")
  if(EXISTS "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommunity.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommunity.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommunity.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommon.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib" TYPE STATIC_LIBRARY FILES "/Users/jinurung/VEDA/Linux/vote/build/build/lib/libcommon.a")
  if(EXISTS "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommon.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommon.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommon.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommunity.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/Users/jinurung/VEDA/Linux/vote/build/lib/../lib" TYPE STATIC_LIBRARY FILES "/Users/jinurung/VEDA/Linux/vote/build/build/lib/libcommunity.a")
  if(EXISTS "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommunity.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommunity.a")
    execute_process(COMMAND "/Library/Developer/CommandLineTools/usr/bin/ranlib" "$ENV{DESTDIR}/Users/jinurung/VEDA/Linux/vote/build/lib/../lib/libcommunity.a")
  endif()
endif()

