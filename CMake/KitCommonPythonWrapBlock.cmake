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
