
# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
#cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
#if (POLICY CMP0141)
 # cmake_policy(SET CMP0141 NEW)
 # set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

#project ("VideoProcessor")

# Include sub-projects.
#add_subdirectory ("VideoProcessor")
cmake_minimum_required(VERSION 3.8)
project(VideoProcessor)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Find OpenCV and GStreamer packages
set(OpenCV_DIR "C:/Users/danie/opencv/build/x64/vc16/lib")

set(PKG_CONFIG_EXECUTABLE "C:/gstreamer/1.0/msvc_x86_64/bin/pkg-config.exe")
set(GSTREAMER_DIR "C:/gstreamer/1.0/msvc_x86_64")
link_directories(${GSTREAMER_DIR}/lib)


find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

# Include OpenCV and GStreamer directories
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${GSTREAMER_INCLUDE_DIRS})

# Add source files
add_executable(VideoProcessor src/main.cpp)

# Link OpenCV and GStreamer libraries
target_link_libraries(VideoProcessor ${OpenCV_LIBS} ${GSTREAMER_LIBRARIES})

set(GSTREAMER_LIBRARIES
    ${GSTREAMER_DIR}/lib/gstreamer-1.0.lib
    ${GSTREAMER_DIR}/lib/gobject-2.0.lib
    ${GSTREAMER_DIR}/lib/glib-2.0.lib
    ${GSTREAMER_DIR}/lib/gmodule-2.0.lib
    ${GSTREAMER_DIR}/lib/gstapp-1.0.lib
    ${GSTREAMER_DIR}/lib/gstbase-1.0.lib
    ${GSTREAMER_DIR}/lib/gstcontroller-1.0.lib
    ${GSTREAMER_DIR}/lib/gstpbutils-1.0.lib
    ${GSTREAMER_DIR}/lib/gstvideo-1.0.lib
    ${GSTREAMER_DIR}/lib/gsttag-1.0.lib
    ${GSTREAMER_DIR}/lib/gstnet-1.0.lib
)
