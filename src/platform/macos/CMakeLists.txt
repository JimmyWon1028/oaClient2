#2026.10.12 modify by codex, bundle the shared app with official arm64 Framework and Helpers.
set(CEF_APP "${CEF_TARGET_OUT_DIR}/${CEF_TARGET}.app")
set(EXECUTABLE_NAME "${CEF_TARGET}")
set(PRODUCT_NAME "${CEF_TARGET}")
set(VERSION_SHORT "${PROJECT_VERSION}")
file(GLOB OA_IMAGES "${CMAKE_CURRENT_SOURCE_DIR}/assets/*.png")
set_source_files_properties(${OA_IMAGES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
add_executable(${CEF_TARGET} MACOSX_BUNDLE ${OA_COMMON_SOURCES} ${OA_IMAGES}
  src/platform/macos/main.mm src/platform/macos/platform.mm src/platform/macos/cef_platform.cpp)
SET_EXECUTABLE_TARGET_PROPERTIES(${CEF_TARGET})
target_compile_options(${CEF_TARGET} PRIVATE "$<$<COMPILE_LANGUAGE:OBJCXX>:-fobjc-arc;-fno-rtti;-fno-exceptions>")
set_target_properties(${CEF_TARGET} PROPERTIES OBJCXX_STANDARD 20 OBJCXX_STANDARD_REQUIRED YES)
target_include_directories(${CEF_TARGET} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(${CEF_TARGET} PRIVATE libcef_dll_wrapper ${CEF_STANDARD_LIBS} "-framework ScreenCaptureKit")
add_dependencies(${CEF_TARGET} libcef_dll_wrapper)
set_target_properties(${CEF_TARGET} PROPERTIES
  MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/src/platform/macos/Info.plist.in")
#2026.10.12 modify by codex, prevent the SDK ln -sf macro from following existing directory links on rebuild.
add_custom_command(TARGET ${CEF_TARGET} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E rm -rf "${CEF_APP}/Contents/Frameworks/Chromium Embedded Framework.framework"
  VERBATIM)
COPY_MAC_FRAMEWORK("${CEF_TARGET}" "${CEF_BINARY_DIR}" "${CEF_APP}")
COPY_SINGLE_FILE(${CEF_TARGET} "${CEF_ROOT}/LICENSE.txt" "${CEF_APP}/Contents/Resources/CEF-LICENSE.txt")

foreach(suffix_entry ${CEF_HELPER_APP_SUFFIXES})
  string(REPLACE ":" ";" suffix "${suffix_entry}")
  list(GET suffix 0 name_suffix)
  list(GET suffix 1 target_suffix)
  list(GET suffix 2 plist_suffix)
  set(helper_target "oaClient2_Helper${target_suffix}")
  set(helper_name "oaClient2 Helper${name_suffix}")
  set(HELPER_NAME "${helper_name}")
  set(HELPER_SUFFIX "${plist_suffix}")
  configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/platform/macos/helper-Info.plist.in"
    "${CMAKE_CURRENT_BINARY_DIR}/helper${target_suffix}.plist" @ONLY)
  add_executable(${helper_target} MACOSX_BUNDLE src/platform/macos/helper.cpp)
  SET_EXECUTABLE_TARGET_PROPERTIES(${helper_target})
  target_link_libraries(${helper_target} PRIVATE libcef_dll_wrapper ${CEF_STANDARD_LIBS})
  set_target_properties(${helper_target} PROPERTIES OUTPUT_NAME "${helper_name}"
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_BINARY_DIR}/helper${target_suffix}.plist")
  add_dependencies(${CEF_TARGET} ${helper_target})
  add_custom_command(TARGET ${CEF_TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
      "${CEF_TARGET_OUT_DIR}/${helper_name}.app" "${CEF_APP}/Contents/Frameworks/${helper_name}.app" VERBATIM)
endforeach()

find_package(Python3 REQUIRED COMPONENTS Interpreter)
add_custom_command(TARGET ${CEF_TARGET} POST_BUILD
  COMMAND "${Python3_EXECUTABLE}" "${CMAKE_CURRENT_SOURCE_DIR}/scripts/create-macos-icon.py"
    "${CMAKE_CURRENT_SOURCE_DIR}/assets/oaClient-256.png" "${CEF_APP}/Contents/Resources/oaClient.icns"
  COMMAND /usr/bin/codesign --force --deep --sign - "${CEF_APP}"
  VERBATIM)
