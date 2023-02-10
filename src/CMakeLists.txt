#-Enabling files-#
FILE(GLOB SRC_FILES "./*.cpp")
FILE(GLOB HEAD_FILES "./*.h")
FILE(GLOB RC_FILES "./*.rc")
add_executable(SameGame ${SRC_FILES} ${HEAD_FILES} ${RC_FILES})
set_target_properties(SameGame PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /SAFESEH:NO")

#-Copy files to the binary directory-#
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})