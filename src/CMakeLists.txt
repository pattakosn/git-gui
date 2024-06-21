#find_package(libgit2 CONFIG REQUIRED)
#find_package(PkgConfig REQUIRED)
#pkg_check_modules(LIBGIT2 REQUIRED IMPORTED_TARGET libgit2)
#target_link_libraries(main PRIVATE PkgConfig::LIBGIT2)
# vcpkg provides proprietary CMake targets:
find_package(unofficial-libgit2 CONFIG REQUIRED)
#target_link_libraries(main PRIVATE unofficial::libgit2::libgit2)

set(SOURCES git-gui.cpp mygit.cpp mygit.h)
add_executable(git-gui ${SOURCES})
target_link_libraries(git-gui PRIVATE unofficial::libgit2::libgit2)
