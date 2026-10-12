cmake_minimum_required(VERSION 3.21)
project(oaClient2 VERSION 0.1.6 LANGUAGES C CXX)

if(APPLE)
  if(NOT CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
    message(FATAL_ERROR "macOS requires native Apple Silicon arm64; Rosetta is not supported.")
  endif()
  if(CMAKE_OSX_ARCHITECTURES AND NOT CMAKE_OSX_ARCHITECTURES STREQUAL "arm64")
    message(FATAL_ERROR "Only the arm64 architecture is supported on macOS.")
  endif()
  set(CMAKE_OSX_ARCHITECTURES arm64 CACHE STRING "Apple Silicon only" FORCE)
  set(PROJECT_ARCH arm64 CACHE STRING "CEF target architecture" FORCE)
  enable_language(OBJCXX)
elseif(NOT WIN32)
  message(FATAL_ERROR "Only Windows x64 and macOS arm64 are implemented.")
endif()
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
  message(FATAL_ERROR "The Windows prototype requires an x64 toolchain.")
endif()
if(NOT CEF_ROOT AND DEFINED ENV{CEF_ROOT})
  set(CEF_ROOT "$ENV{CEF_ROOT}")
endif()
if(NOT EXISTS "${CEF_ROOT}/include/cef_app.h")
  message(FATAL_ERROR "Set CEF_ROOT to the extracted, local CEF standard distribution for this platform.")
endif()
file(TO_CMAKE_PATH "${CEF_ROOT}" CEF_ROOT)
set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(USE_SANDBOX OFF CACHE BOOL "ERP client runs without the CEF sandbox by user request" FORCE)
list(APPEND CMAKE_MODULE_PATH "${CEF_ROOT}/cmake")
find_package(CEF REQUIRED)
if(APPLE)
  execute_process(COMMAND /usr/bin/lipo -archs
    "${CEF_ROOT}/Release/Chromium Embedded Framework.framework/Chromium Embedded Framework"
    OUTPUT_VARIABLE OA_CEF_ARCH OUTPUT_STRIP_TRAILING_WHITESPACE RESULT_VARIABLE OA_CEF_ARCH_RESULT)
  if(NOT OA_CEF_ARCH_RESULT EQUAL 0 OR NOT OA_CEF_ARCH STREQUAL "arm64")
    message(FATAL_ERROR "CEF_ROOT must contain the macosarm64 SDK; x86_64 and Universal are not supported.")
  endif()
endif()
add_subdirectory("${CEF_LIBCEF_DLL_WRAPPER_PATH}" "${CMAKE_BINARY_DIR}/libcef_dll_wrapper")
if(WIN32)
  ADD_LOGICAL_TARGET(libcef_lib "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")
endif()

set(CEF_TARGET oaClient2)
SET_CEF_TARGET_OUT_DIR()
set(OA_COMMON_SOURCES src/app/app.cpp src/common/ini.cpp)
#2026.10.12 modify by codex, compile the same app and common sources on both platforms.
if(WIN32)
  add_executable(${CEF_TARGET} WIN32
    ${OA_COMMON_SOURCES}
    src/platform/windows/cef_platform.cpp
    src/platform/windows/platform.cpp
    src/platform/windows/main.cpp
    src/platform/windows/app.rc
    src/platform/windows/application_images.rc
  )
  SET_EXECUTABLE_TARGET_PROPERTIES(${CEF_TARGET})
  target_include_directories(${CEF_TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
  target_link_libraries(${CEF_TARGET} PRIVATE
    libcef_lib libcef_dll_wrapper ${CEF_STANDARD_LIBS} shell32 ole32 user32 iphlpapi ws2_32 gdiplus gdi32 dwmapi
  )
  add_dependencies(${CEF_TARGET} libcef_dll_wrapper)
  set(CEF_RUNTIME_OUT_DIR "${CEF_TARGET_OUT_DIR}/cef")
  add_custom_command(TARGET ${CEF_TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CEF_RUNTIME_OUT_DIR}"
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CEF_RUNTIME_OUT_DIR}/oaClient2.exe" "${CEF_RUNTIME_OUT_DIR}/oaClient2.dll"
    VERBATIM
  )
  COPY_FILES(${CEF_TARGET} "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_RUNTIME_OUT_DIR}")
  COPY_FILES(${CEF_TARGET} "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_RUNTIME_OUT_DIR}")
  COPY_SINGLE_FILE(${CEF_TARGET} "${CEF_ROOT}/LICENSE.txt" "${CEF_RUNTIME_OUT_DIR}/CEF-LICENSE.txt")
  set_target_properties(${CEF_TARGET} PROPERTIES
    VS_DEBUGGER_COMMAND "$<TARGET_FILE_DIR:${CEF_TARGET}>/${CEF_TARGET}.exe"
  )

else()
  include(src/platform/macos/CMakeLists.txt)
endif()

include(CTest)
if(BUILD_TESTING)
  if(WIN32)
    add_executable(oaClient2_report_receiver WIN32 tests/report_receiver.cpp)
    target_compile_definitions(oaClient2_report_receiver PRIVATE UNICODE _UNICODE)
    target_compile_options(oaClient2_report_receiver PRIVATE /utf-8)
    target_link_libraries(oaClient2_report_receiver PRIVATE shell32)
    set_target_properties(oaClient2_report_receiver PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    add_executable(oaClient2_core_tests
      tests/core_tests.cpp tests/windows_tests.cpp src/common/ini.cpp src/platform/windows/platform.cpp
    )
    target_include_directories(oaClient2_core_tests PRIVATE src)
    target_compile_options(oaClient2_core_tests PRIVATE /utf-8)
    target_link_libraries(oaClient2_core_tests PRIVATE shell32 ole32 user32 iphlpapi ws2_32 gdiplus gdi32 dwmapi)
    add_dependencies(oaClient2_core_tests oaClient2_report_receiver)
  else()
    add_executable(oaClient2_core_tests tests/core_tests.cpp tests/macos_tests.cpp
      src/common/ini.cpp src/platform/macos/platform.mm)
    target_include_directories(oaClient2_core_tests PRIVATE src)
    target_compile_options(oaClient2_core_tests PRIVATE "$<$<COMPILE_LANGUAGE:OBJCXX>:-fobjc-arc>")
    target_link_libraries(oaClient2_core_tests PRIVATE "-framework Cocoa" "-framework ScreenCaptureKit")
  endif()
  add_test(NAME core COMMAND oaClient2_core_tests)
endif()
