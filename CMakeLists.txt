cmake_minimum_required(VERSION 3.2)

PROJECT(dmdll)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

SET(DMDLL_VERSION_MAJOR "1")
SET(DMDLL_VERSION_MINOR "0")
SET(DMDLL_VERSION_PATCH "1")
SET(DMDLL_VERSION "${DMDLL_VERSION_MAJOR}.${DMDLL_VERSION_MINOR}.${DMDLL_VERSION_PATCH}")

MESSAGE(STATUS "VERSION: ${DMDLL_VERSION}")

OPTION(USE_DMDLL "use dmdll" OFF)
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/dmdll_config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/dmdll_config.h)

ModuleImportAll("thirdparty")
LibImport("dmdll_module" "src/dmdll_module")
ExeImport("test" "dmdll_module")

#ADD_CUSTOM_COMMAND(
#TARGET dmdlltest
#PRE_BUILD
#COMMAND ${CMAKE_COMMAND} -E copy_if_different
#${CMAKE_CURRENT_SOURCE_DIR}/config/test.csv
#$<TARGET_FILE_DIR:dmdlltest>
#)

#INSTALL(DIRECTORY include/ DESTINATION include)
#INSTALL(TARGETS dmdll
#        RUNTIME DESTINATION bin
#        LIBRARY DESTINATION lib
#        ARCHIVE DESTINATION lib)

#SET(DMDLL_LIBS "dmdll")
#MARK_AS_ADVANCED(${DMDLL_LIBS})