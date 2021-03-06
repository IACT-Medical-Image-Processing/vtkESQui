IF(VTK_PYTHON_INCLUDE_DIR)
  INCLUDE_DIRECTORIES("${PYTHON_INCLUDE_PATH}")
ENDIF(VTK_PYTHON_INCLUDE_DIR)

VTK_WRAP_PYTHON3(${PROJECT_NAME}${KIT}Python KitPython_SRCS "${Kit_SRCS}")
ADD_LIBRARY(${PROJECT_NAME}${KIT}PythonD ${KitPython_SRCS})
ADD_LIBRARY(${PROJECT_NAME}${KIT}Python MODULE ${PROJECT_NAME}${KIT}PythonInit.cxx)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}${KIT}PythonD ${PROJECT_NAME}${KIT} ${KIT_PYTHON_LIBS})
FOREACH(c ${Kit_LIBS})
  TARGET_LINK_LIBRARIES(${PROJECT_NAME}${KIT}PythonD ${c}PythonD)
ENDFOREACH(c)
TARGET_LINK_LIBRARIES(${PROJECT_NAME}${KIT}Python ${PROJECT_NAME}${KIT}PythonD)

# Python extension modules on Windows must have the extension ".pyd"
IF(WIN32 AND NOT CYGWIN)
  SET_TARGET_PROPERTIES(${PROJECT_NAME}${KIT}Python PROPERTIES SUFFIX ".pyd")
ENDIF(WIN32 AND NOT CYGWIN)

# Make sure that no prefix is set on the library
SET_TARGET_PROPERTIES(${PROJECT_NAME}${KIT}Python PROPERTIES PREFIX "")

# Compatibility for projects that still expect the "lib" prefix
IF(CYGWIN OR NOT WIN32)
  SET(suf ${CMAKE_SHARED_MODULE_SUFFIX})
  SET(src ${PROJECT_NAME}${KIT}Python${suf})
  SET(tgt ${LIBRARY_OUTPUT_PATH}/lib${PROJECT_NAME}${KIT}Python${suf})
  ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}${KIT}Python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${src} ${tgt})
ENDIF(CYGWIN OR NOT WIN32)
