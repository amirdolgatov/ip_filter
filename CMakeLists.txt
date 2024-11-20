cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 17)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    set(PATCH_NUM $ENV{GITHUB_RUN_NUMBER})
else()
    set(PATCH_NUM 0)
endif()

project(ip_filter
        LANGUAGES CXX
        VERSION 0.0.${PATCH_NUM}
)

configure_file(version.h.in version.h.in)

add_subdirectory(filter_lib)
add_subdirectory(ip_filter)
add_subdirectory(test)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT amirdolgatov@gmail.com)
include(CPack)