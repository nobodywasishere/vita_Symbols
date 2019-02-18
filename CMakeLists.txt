cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(vita_symbols)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Vita Symbols")
set(VITA_TITLEID  "VGEE00003")
set(VITA_VERSION  "01.00")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(
  common
)

add_executable(${PROJECT_NAME}.elf
  src/main.cpp
)

target_link_libraries(${PROJECT_NAME}.elf
  debugnet
  vita2d
  soloud
  pthread
  ScePgf_stub
  ScePvf_stub
  SceGxm_stub
  SceCtrl_stub
  SceTouch_stub
  SceAppUtil_stub
  SceDisplay_stub
  SceLibKernel_stub
  SceSysmodule_stub
  SceSysmem_stub
  ScePower_stub
  SceCommonDialog_stub
  SceRegistryMgr_stub
  SceHid_stub
  freetype
  png
  jpeg
  SceAudio_stub
  SceDisplay_stub
  SceIofilemgr_stub
  SceSysmodule_stub
  SceNet_stub
  SceNetCtl_stub
  SceHttp_stub
  SceSsl_stub
  jansson
  ${CURL_LIBRARIES}
  ${OPENSSL_LIBRARIES}
  c
  m
  z


)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME}.elf)
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE fonts/psexchar.pvf FILE fonts/psexchar.pvf
)
