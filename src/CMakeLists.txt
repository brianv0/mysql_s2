# set(MYSQL_INCLUDE_DIR "/usr/local/Cellar/mariadb/10.2.12/include/mysql" CACHE STRING "MySQL include directory")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
find_package(MySQL REQUIRED)

# Find brew openssl libraries
if (APPLE)
    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)
endif()

include_directories(${MYSQLS2_SOURCE_DIR}/src/s2geometry/src ${MYSQS2_SOURCE_DIR}/src/base64 ${MYSQL_INCLUDE_DIR})

add_library (mysqls2 SHARED mysqls2.cxx)
