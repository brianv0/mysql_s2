set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
find_package(MySQL REQUIRED)

# Find brew openssl libraries
if (APPLE)
    set(OPENSSL_ROOT_DIR /usr/local/opt/openssl)
endif()

include_directories(${MYSQLS2_SOURCE_DIR}/src
        ${MYSQLS2_SOURCE_DIR}/src/s2geometry/src
        ${MYSQLS2_SOURCE_DIR}/src/geos/capi
        ${MYSQLS2_SOURCE_DIR}/src/geos/include
        ${MYSQS2_SOURCE_DIR}/src/base64
        ${MYSQL_INCLUDE_DIR})

add_subdirectory(s2geometry)
add_subdirectory(geos EXCLUDE_FROM_ALL)
add_library (mysqls2 SHARED mysqls2.cxx)
target_link_libraries(mysqls2 s2 geos)
