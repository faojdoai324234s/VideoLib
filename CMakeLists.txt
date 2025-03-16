cmake_minimum_required( VERSION 3.19 )

set( library_name VideoLib )

project( ${library_name} CXX )

set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTORCC ON )

set( CURL_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include )
set( FFMPEG_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include )
set( LIBXML_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include )
set( SDL3_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include )
set( MP4DECRYPT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include )

link_directories( ${PROJECT_SOURCE_DIR}/lib )

# Hide the console window in visual studio projects
if(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

find_package( Qt5 REQUIRED COMPONENTS Core Gui Multimedia Network OpenGL Svg Widgets )
find_package( OpenGL REQUIRED COMPONENTS GL GLU )
find_package( GLUT REQUIRED )

file( GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp ${PROJECT_SOURCE_DIR}/src/*.h ${PROJECT_SOURCE_DIR}/src/*.hpp ${PROJECT_SOURCE_DIR}/src/*.qrc )

file( GLOB CURL_HEADERS ${CURL_HEADERS_DIR}/curl/*.h )
file( GLOB FFMPEG_HEADERS
  ${FFMPEG_HEADERS_DIR}/libavcodec/*.h
  ${FFMPEG_HEADERS_DIR}/libavdevice/*.h
  ${FFMPEG_HEADERS_DIR}/libavfilter/*.h
  ${FFMPEG_HEADERS_DIR}/libavformat/*.h
  ${FFMPEG_HEADERS_DIR}/libavutil/*.h
  ${FFMPEG_HEADERS_DIR}/libpostproc/*.h
  ${FFMPEG_HEADERS_DIR}/libswresample/*.h
  ${FFMPEG_HEADERS_DIR}/libswscale/*.h
)
file( GLOB LIBXML_HEADERS ${LIBXML_HEADERS_DIR}/libxml/*.h ${LIBXML_HEADERS_DIR}/private/*.h ${LIBXML_HEADERS_DIR}/win32config.h ${LIBXML_HEADERS_DIR}/wsockcompat.h )
file( GLOB SDL3_HEADERS ${SDL3_HEADERS_DIR}/SDL3/*.h )
file( GLOB MP4DECRYPT_HEADERS ${MP4DECRYPT_HEADERS_DIR}/mp4decrypt/*.h )

add_executable( ${library_name} ${SRC_FILES} )

set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${library_name} )

if( UNIX AND NOT APPLE )
  set( LINK_LIBS
  libavcodec.so libavdevice.so libavfilter.so libavformat.so libavutil.so libpostproc.so libswresample.so libswscale.so
  libcurl.so libcurl-d.so
  libxml2d.so libxml2.so
  libSDL3.so libSDL3d.so
  libmp4decrypt.so libmp4decrypt_debug.so
  )
elseif( APPLE )
  set( LINK_LIBS
  libavcodec.dylib libavdevice.dylib libavfilter.dylib libavformat.dylib libavutil.dylib libpostproc.dylib libswresample.dylib libswscale.dylib
  libcurl.dylib libcurl-d.dylib
  libxml2d.dylib libxml2.dylib
  libSDL3.dylib libSDL3d.dylib
  libmp4decrypt.dylib libmp4decrypt_debug.dylib
  )
elseif( WIN32 )
  set( LINK_LIBS
  avcodec.lib avdevice.lib avfilter.lib avformat.lib avutil.lib postproc.lib swresample.lib swscale.lib
  libcurl.lib libcurl_debug.lib
  libxml2d.lib libxml2.lib
  SDL3.lib SDL3d.lib
  mp4decrypt_debug.lib mp4decrypt.lib
  Ws2_32.lib Crypt32.lib Wldap32.lib Normaliz.lib  # Needed for libcurl
  )
endif()

target_link_libraries( ${library_name} PRIVATE Qt5::Core Qt5::Gui Qt5::Multimedia Qt5::Network Qt5::OpenGL Qt5::Svg Qt5::Widgets OpenGL::GL OpenGL::GLU ${LINK_LIBS} )

target_include_directories( ${library_name} PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CURL_HEADERS_DIR}
  ${FFMPEG_HEADERS_DIR}
  ${LIBXML_HEADERS_DIR}
  ${SDL3_HEADERS_DIR}
  ${MP4DECRYPT_HEADERS_DIR}
)
