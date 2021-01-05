# Minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# set CMake project name
project(WIXTEST)

set(BRLCAD_CMAKE_DIR "${CMAKE_SOURCE_DIR}/CMake")
list(APPEND CMAKE_MODULE_PATH "${BRLCAD_CMAKE_DIR}")

include(CTest)

add_executable(wixtest wixtest.c)
install(TARGETS wixtest
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  )
set_property(INSTALL "bin/$<TARGET_FILE_NAME:wixtest>"
  PROPERTY CPACK_START_MENU_SHORTCUTS "wixtest")
set_property(INSTALL "bin/$<TARGET_FILE_NAME:wixtest>"
  PROPERTY CPACK_DESKTOP_SHORTCUTS "wixtest"
  )

add_test(NAME wixcwd COMMAND wixtest)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Hello World")
set(CPACK_PACKAGE_VENDOR "Team")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/COPYING")
set(CPACK_PACKAGE_VERSION_MAJOR 1)
set(CPACK_PACKAGE_VERSION_MINOR 0)
set(CPACK_PACKAGE_VERSION_PATCH 0)

# By default, we want debugging information
set(CPACK_STRIP_FILES FALSE)

if (WIN32)

  find_package(NSIS)
  if (NSIS_FOUND)
    set(CPACK_GENERATOR ${CPACK_GENERATOR} NSIS)
    set(CPACK_NSIS_PACKAGE_NAME "WixCMake")
    set(CPACK_NSIS_INSTALL_DIRECTORY "WIXTEST ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
    set(CPACK_SOURCE_DIR "${CMAKE_SOURCE_DIR}")
    # There is a bug in NSIS that does not handle full unix paths properly. Make
    # sure there is at least one set of four (4) backslashes.
    set(CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/wix\\\\product.ico")
    set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
    set(CPACK_NSIS_DISPLAY_NAME "WixCMake")
    set(CPACK_NSIS_MODIFY_PATH ON)
  endif (NSIS_FOUND)

  find_package(Wix)
  if (Wix_FOUND)
    set(CPACK_GENERATOR ${CPACK_GENERATOR} WIX)
    set(CPACK_WIX_LICENSE_RTF "${CMAKE_SOURCE_DIR}/wix/License.rtf")
    set(CPACK_WIX_PRODUCT_ICON "${CMAKE_SOURCE_DIR}/wix/product.ico")
    set(CPACK_WIX_PROGRAM_MENU_FOLDER "WiX-CMake")
    set(CPACK_WIX_UI_BANNER "${CMAKE_SOURCE_DIR}/wix/banner.bmp")
    set(CPACK_WIX_UI_DIALOG "${CMAKE_SOURCE_DIR}/wix/dialog.bmp")
    if(CMAKE_CL_64)
      set(CPACK_PACKAGE_FILE_NAME "WixCMake_win64")
      set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "WixCMake win64")
    else(CMAKE_CL_64)
      set(CPACK_PACKAGE_FILE_NAME "WixCMake_win32")
      set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "WixCMake win32")
    endif(CMAKE_CL_64)

    # Custom add-ons from CMake build
    list(APPEND CPACK_WIX_CANDLE_EXTRA_FLAGS -dBUILD_GUI=1)
    set(CPACK_WIX_EXTRA_SOURCES
      "${CMAKE_SOURCE_DIR}/wix/install_dir.wxs"
      "${CMAKE_SOURCE_DIR}/wix/cmake_extra_dialog.wxs"
      )
    set(CPACK_WIX_UI_REF "CMakeUI_InstallDir")
    set(CPACK_WIX_PATCH_FILE
      "${CMAKE_SOURCE_DIR}/wix/patch_path_env.xml"
      "${CMAKE_SOURCE_DIR}/wix/patch_desktop_shortcut.xml"
      )
  endif (Wix_FOUND)

else ()

  set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
  set(CPACK_GENERATOR TGZ)

endif ()

include(CPack)



# Local Variables:
# tab-width: 8
# mode: cmake
# indent-tabs-mode: t
# End:
# ex: shiftwidth=2 tabstop=8
