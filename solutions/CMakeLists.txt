# Recursively add subdirectories as a convenience.
# https://stackoverflow.com/questions/31004421/does-cmake-support-include-directories-recursively
FILE(GLOB_RECURSE new_list *.cpp)
SET(dir_list "")
FOREACH(file_path ${new_list})
    GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
    SET(dir_list ${dir_list} ${dir_path})
ENDFOREACH()
LIST(REMOVE_DUPLICATES dir_list)

FOREACH(dir ${dir_list})
    add_subdirectory(${dir})
ENDFOREACH()
