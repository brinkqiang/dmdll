cmake_minimum_required(VERSION 3.21)

project(dmdll)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(cmake/ModuleImport.cmake)
include(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

ModuleImportAll("thirdparty")

LibImport("libC" "src/libC")

DllImportDepends("libA" "src/libA" "libC")
DllImportDepends("libB" "src/libB" "libC")

DllImportDepends("dmdll" "src/dmdll_module" "")

if(PROJECT_IS_TOP_LEVEL)
    ExeImport("test" "dmdll")
endif()

