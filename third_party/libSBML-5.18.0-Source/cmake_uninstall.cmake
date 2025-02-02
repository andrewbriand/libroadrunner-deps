###############################################################################
#
# File                     : cmake_uninstall.cmake.in
# Description              : CMake uninstall script
# originally available from: http://www.cmake.org/Wiki/RecipeAddUninstallTarget
#
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright (C) 2013-2017 jointly by the following organizations:
#     1. California Institute of Technology, Pasadena, CA, USA
#     2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
#     3. University of Heidelberg, Heidelberg, Germany
#
# Copyright (C) 2009-2013 jointly by the following organizations:
#     1. California Institute of Technology, Pasadena, CA, USA
#     2. EMBL European Bioinformatics Institute (EMBL-EBI), Hinxton, UK
#
# Copyright (C) 2006-2008 by the California Institute of Technology,
#     Pasadena, CA, USA
#
# Copyright (C) 2002-2005 jointly by the following organizations:
#     1. California Institute of Technology, Pasadena, CA, USA
#     2. Japan Science and Technology Agency, Japan
#
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
#
###############################################################################

IF(NOT EXISTS "/home/abriand/libroadrunner-deps/third_party/libSBML-5.18.0-Source/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"/home/abriand/libroadrunner-deps/third_party/libSBML-5.18.0-Source/install_manifest.txt\"")
ENDIF(NOT EXISTS "/home/abriand/libroadrunner-deps/third_party/libSBML-5.18.0-Source/install_manifest.txt")

FILE(READ "/home/abriand/libroadrunner-deps/third_party/libSBML-5.18.0-Source/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
STRING(REGEX REPLACE " " ";" files "${files}")
STRING(REGEX REPLACE ";;" ";" files "${files}")

# addition files that wouldn't be deleted (since they are symlinks)
# and the actual file is listed before in the manifest
set(extra_files
  "/usr/local/lib/libsbml.5.dylib"
  "/usr/local/lib/libsbml.dylib"
  "/usr/local/lib/libsbml.5.so"
  "/usr/local/lib/libsbml.so"
)

FOREACH(file ${extra_files})

    EXEC_PROGRAM(
      "/usr/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )

ENDFOREACH(file)

# We also should delete a number of directories that we create with 
# make install, but only those that could not include files from others
SET(directories 
     "/usr/local/share/libsbml"
)
FOREACH(file ${files})
  get_filename_component(fileName ${file} NAME)
  get_filename_component(filePath ${file} PATH)
  
  # these are the files created by us
  foreach(pattern 
		".*/uninstall-libsbml-pkg.sh$"
		".*/include/sbml$"
		".*/lib/mono/libsbmlcsP$"
		".*/auto/libSBML$"
		".*/site-packages/libsbml$"
		".*/share/libsbml$"
		".*/bindings/csharp$"
		".*/bindings/java$"
		".*/bindings/python$"
		".*/bindings/r$"
		".*/bindings/ruby$"
		".*/bindings/perl$"
		".*/bindings/matlab$"
		".*/bindings/octave$"
		".*/examples$"
		)
  if("${filePath}" MATCHES ${pattern})
     list(FIND directories ${filePath} index)
	 if (index EQUAL "-1")
		list(APPEND directories ${filePath})
	 endif()
  endif()
  endforeach(pattern)
  
  IF(EXISTS "$ENV{DESTDIR}${file}")
    MESSAGE(STATUS "Uninstalling \"${fileName}\"")
    EXEC_PROGRAM(
      "/usr/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
    IF(NOT "${rm_retval}" STREQUAL 0)
      MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
    ENDIF(NOT "${rm_retval}" STREQUAL 0)
  ENDIF(EXISTS "$ENV{DESTDIR}${file}")
ENDFOREACH(file)

# Remove the directories found before.
foreach(dir ${directories})

  IF(EXISTS "$ENV{DESTDIR}${dir}")
    message(STATUS "Remove directory '${dir}'")
	EXEC_PROGRAM(
      "/usr/bin/cmake" ARGS "-E remove_directory \"$ENV{DESTDIR}${dir}\""
      OUTPUT_VARIABLE rm_out
      RETURN_VALUE rm_retval
      )
  endif()
  
endforeach(dir)
