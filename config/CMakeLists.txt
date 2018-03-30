set(Config_SRC
    Config.hpp
    Config.cpp
    str_proc.hpp
    str_proc.cpp)

set(LIBRARY_TARGET_NAME config)

add_library(config STATIC ${Config_SRC})
set_target_properties(config PROPERTIES VERSION
    ${${PROJECT_NAME}_VERSION}
    PUBLIC_HEADER "Config.hpp")

target_include_directories(${LIBRARY_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
                                                         "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>")

#target_include_directories(config PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(test)

install(TARGETS ${LIBRARY_TARGET_NAME}
        EXPORT  ${PROJECT_NAME}
        LIBRARY       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT shlib
        ARCHIVE       DESTINATION "${CMAKE_INSTALL_LIBDIR}"                            COMPONENT lib
        RUNTIME       DESTINATION "${CMAKE_INSTALL_BINDIR}"                            COMPONENT bin
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${LIBRARY_TARGET_NAME}" COMPONENT dev)

set_property(GLOBAL APPEND PROPERTY ${PROJECT_NAME}_TARGETS ${LIBRARY_TARGET_NAME})
