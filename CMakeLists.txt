# CMake version required. This must be the very first line, because it sets default policies affecting everything else
cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_FLAGS "-O3 -ffast-math -fomit-frame-pointer")
add_definitions(-DMAEMO)
# KDE Gear Version, managed by release script
set(RELEASE_SERVICE_VERSION_MAJOR "23")
set(RELEASE_SERVICE_VERSION_MINOR "07")
set(RELEASE_SERVICE_VERSION_MICRO "70")
set(RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

# Project name and version
project(Falkon VERSION ${RELEASE_SERVICE_VERSION})

# Find ECM, with nice error handling in case of failure
include(FeatureSummary)
find_package(ECM 5.78.0 CONFIG)
set_package_properties(ECM PROPERTIES TYPE REQUIRED DESCRIPTION "Extra CMake Modules." URL "https://invent.kde.org/frameworks/extra-cmake-modules")
feature_summary(WHAT REQUIRED_PACKAGES_NOT_FOUND FATAL_ON_MISSING_REQUIRED_PACKAGES)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Many includes from ECM, to get all the nice cmake functions and settings
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(ECMSetupVersion)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)
include(ECMPoQmTools)

# Output dirs (like ECM 5.38 does)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

if (UNIX AND NOT APPLE)
    set(FALKON_INSTALL_PLUGINDIR "${KDE_INSTALL_PLUGINDIR}/falkon")
else()
    set(FALKON_INSTALL_PLUGINDIR "${KDE_INSTALL_PLUGINDIR}")
endif()
if (IS_ABSOLUTE ${FALKON_INSTALL_PLUGINDIR})
    set(PLUGIN_PATH "${FALKON_INSTALL_PLUGINDIR}")
else()
    set(PLUGIN_PATH "${CMAKE_INSTALL_PREFIX}/${FALKON_INSTALL_PLUGINDIR}")
endif()
if (NOT WIN32)
    set(FALKON_PLUGIN_PATH "${PLUGIN_PATH}" CACHE PATH "Default plugin search path")
endif()

# Defines that are always set
add_definitions(-DQT_NO_URL_CAST_FROM_STRING -DQT_USE_QSTRINGBUILDER -DQT_NO_CAST_TO_ASCII)

# Mandatory: Qt5
set(QT_MIN_VERSION "5.15.0")
find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Widgets Network Sql QuickWidgets PrintSupport WebChannel)
find_package(Qt5WebEngine ${QT_MIN_VERSION} REQUIRED)
find_package(Qt5WebEngineWidgets ${QT_MIN_VERSION} REQUIRED)
if (BUILD_TESTING)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Test)
endif()
if (NOT DISABLE_DBUS)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS DBus)
endif()

if (UNIX AND NOT APPLE AND NOT NO_X11)
    add_definitions(-DQZ_WS_X11)
    find_package(XCB REQUIRED COMPONENTS XCB UTIL)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS X11Extras)
endif()
if (WIN32)
    add_definitions(-DW7API)
    find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS WinExtras)

    # taken from https://stackoverflow.com/a/40217291
    macro(get_WIN32_WINNT version)
        if (CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
            string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
            # Check for Windows 10, b/c we'll need to convert to hex 'A'.
            if ("${verMajor}" MATCHES "10")
                set(verMajor "A")
                string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
            endif ("${verMajor}" MATCHES "10")
            # Remove all remaining '.' characters.
            string(REPLACE "." "" ver ${ver})
            # Prepend each digit with a zero.
            string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
            set(${version} "0x${ver}")
        endif(CMAKE_SYSTEM_VERSION)
    endmacro(get_WIN32_WINNT)

    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
endif()

# Mandatory: OpenSSL
find_package(OpenSSL REQUIRED)



# Optional: PySide2
find_package(PySide2 "2.0.0")
find_package(Shiboken2 "2.0.0")
find_package(Python3 COMPONENTS Development)
set_package_properties(PySide2 PROPERTIES DESCRIPTION "Python plugins" TYPE OPTIONAL)
set_package_properties(Shiboken2 PROPERTIES DESCRIPTION "Python plugins" TYPE OPTIONAL)
set_package_properties(Python3 PROPERTIES DESCRIPTION "Python plugins" TYPE OPTIONAL)
if (PySide2_FOUND AND Shiboken2_FOUND AND Python3_FOUND)
    set(ENABLE_PYTHON_PLUGINS TRUE)
endif()

find_package(Intl)
if (Intl_FOUND)
    set(HAVE_LIBINTL TRUE)
endif()

# Git revision
if (EXISTS "${CMAKE_SOURCE_DIR}/.git")
  find_package(Git QUIET)
  if(GIT_FOUND)
    execute_process(
      COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      OUTPUT_VARIABLE GIT_REVISION
    )
    string(REGEX REPLACE "\n" "" GIT_REVISION "${GIT_REVISION}")
    set(FALKON_GIT_REVISION "${GIT_REVISION}")
  else()
    message(STATUS "Git revision could not be determined")
  endif()
endif()

configure_file(config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/src/config.h)

# Include dirs used everywhere
include_directories(
     ${CMAKE_SOURCE_DIR}/src/lib/3rdparty
     ${CMAKE_SOURCE_DIR}/src/lib/adblock
     ${CMAKE_SOURCE_DIR}/src/lib/app
     ${CMAKE_SOURCE_DIR}/src/lib/autofill
     ${CMAKE_SOURCE_DIR}/src/lib/bookmarks
     ${CMAKE_SOURCE_DIR}/src/lib/cookies
     ${CMAKE_SOURCE_DIR}/src/lib/downloads
     ${CMAKE_SOURCE_DIR}/src/lib/history
     ${CMAKE_SOURCE_DIR}/src/lib/navigation
     ${CMAKE_SOURCE_DIR}/src/lib/network
     ${CMAKE_SOURCE_DIR}/src/lib/notifications
     ${CMAKE_SOURCE_DIR}/src/lib/opensearch
     ${CMAKE_SOURCE_DIR}/src/lib/other
     ${CMAKE_SOURCE_DIR}/src/lib/plugins
     ${CMAKE_SOURCE_DIR}/src/lib/popupwindow
     ${CMAKE_SOURCE_DIR}/src/lib/preferences
     ${CMAKE_SOURCE_DIR}/src/lib/session
     ${CMAKE_SOURCE_DIR}/src/lib/sidebar
     ${CMAKE_SOURCE_DIR}/src/lib/tabwidget
     ${CMAKE_SOURCE_DIR}/src/lib/tools
     ${CMAKE_SOURCE_DIR}/src/lib/webengine
     ${CMAKE_SOURCE_DIR}/src/lib/webtab
)

# Finally, go into the subdirs
add_subdirectory(src)

#if (BUILD_TESTING)
#    add_subdirectory(autotests)
#    add_subdirectory(tests/benchmarks)
#endif()

# Tell releaseme that po is already taken care of
# SKIP_PO_INSTALL

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
