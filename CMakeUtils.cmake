set(CODE_ROOT ${CMAKE_CURRENT_LIST_DIR})
set(PLATFORM "")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(CMAKE_CL_64)
	set(PLATFORM_POSTFIX "x64")
else(CMAKE_CL_64)
	set(PLATFORM_POSTFIX "")
endif(CMAKE_CL_64)

if(UNIX OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
	add_definitions(-DPLATFORM_LINUX)
	set(LINUX 1)
endif(UNIX OR CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)

if(APPLE)
	add_definitions(-DPLATFORM_APPLE)
endif(APPLE)

if(WIN32)
	add_definitions(-DPLATFORM_WIN)
	add_definitions(/W0)
	add_definitions(/MP8)
endif(WIN32)

macro(add_source_group FILTER_NAME SOURCE_PATH TARGET_LIST)
   file(TO_NATIVE_PATH ${FILTER_NAME} NEW_FILTER_NAME)
   if (WIN32 OR LINUX)
      file(GLOB TEMP_SRC
         "${SOURCE_PATH}/*.h"
         "${SOURCE_PATH}/*.inl"
         "${SOURCE_PATH}/*.cpp"
         "${SOURCE_PATH}/*.c"
         "${SOURCE_PATH}/*.cxx"
         "${SOURCE_PATH}/*.cc"
      )
   endif(WIN32 OR LINUX)
   if (APPLE)
      file(GLOB TEMP_SRC
         "${SOURCE_PATH}/*.h"
         "${SOURCE_PATH}/*.cpp"
         "${SOURCE_PATH}/*.mm"
         "${SOURCE_PATH}/*.c"
         "${SOURCE_PATH}/*.cxx"
         "${SOURCE_PATH}/*.cc"
      )
   endif(APPLE)
#message("${NEW_FILTER_NAME}" ${TEMP_SRC})
   source_group("${NEW_FILTER_NAME}" FILES ${TEMP_SRC})
   list(APPEND ${TARGET_LIST} "${TEMP_SRC}")
endmacro(add_source_group)
