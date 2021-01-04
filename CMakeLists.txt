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

# If we're not on Windows, set the install prefix and create
# TGZ packages by default.  If we are on Windows, try WiX.
if (WIN32)
  find_package(Wix)
  if (Wix_FOUND)
    set(CPACK_GENERATOR WIX)
    set(CPACK_WIX_LICENSE_RTF "${CMAKE_SOURCE_DIR}/wix/License.rtf")
    set(CPACK_WIX_PRODUCT_ICON "${CMAKE_SOURCE_DIR}/wix/product.ico")
    set(CPACK_WIX_PROGRAM_MENU_FOLDER "WiX-CMake")
    set(CPACK_WIX_UI_BANNER "${CMAKE_SOURCE_DIR}/wix/banner.bmp")
    set(CPACK_WIX_UI_DIALOG "${CMAKE_SOURCE_DIR}/wix/dialog.bmp")
    if(CMAKE_CL_64)
      set(CPACK_PACKAGE_FILE_NAME "WixCMake_${BRLCAD_VERSION}_win64")
      set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "WixCMake ${BRLCAD_VERSION} win64")
    else(CMAKE_CL_64)
      set(CPACK_PACKAGE_FILE_NAME "WixCMake_${BRLCAD_VERSION}_win32")
      set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "WixCMake ${BRLCAD_VERSION} win32")
    endif(CMAKE_CL_64)
  else (Wix_FOUND)
    message(FATAL_ERROR "Building on Windows, but unable to find WiX.")
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
