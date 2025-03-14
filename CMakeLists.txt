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
set( MP4DECRYPT_HEADERS_DIR ${PROJECT_SOURCE_DIR}/include )

link_directories( ${PROJECT_SOURCE_DIR}/lib )

# Hide the console window in visual studio projects
if(MSVC)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
  set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

list( APPEND Qt5_DIR ${QT_DIRECTORY} )

find_package( Qt5 REQUIRED COMPONENTS Core Gui Multimedia Network OpenGL Svg Widgets )

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
file( GLOB MP4DECRYPT_HEADERS ${MP4DECRYPT_HEADERS_DIR}/mp4decrypt/*.h )

add_executable( ${library_name} ${SRC_FILES} )

set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${library_name} )

target_link_libraries( ${library_name} PRIVATE Qt5::Core Qt5::Gui Qt5::Multimedia Qt5::Network Qt5::OpenGL Qt5::Svg Qt5::Widgets
  avcodec.lib avdevice.lib avfilter.lib avformat.lib avutil.lib postproc.lib swresample.lib swscale.lib
  libxml2d.lib libxml2.lib
  libcurl.lib libcurl_debug.lib
  mp4decrypt_debug.lib mp4decrypt.lib
  OpenGL32.lib GLU32.lib
  Ws2_32.lib Crypt32.lib Wldap32.lib Normaliz.lib  # Needed for libcurl
)

target_include_directories( ${library_name} PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CURL_HEADERS_DIR}
  ${FFMPEG_HEADERS_DIR}
  ${LIBXML_HEADERS_DIR}
  ${MP4DECRYPT_HEADERS_DIR}
)
