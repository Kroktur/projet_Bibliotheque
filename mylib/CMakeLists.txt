project(mylib)

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


set(HEADERS
${HEADER_DIR}/Consoleframebuffer.h
${HEADER_DIR}/DataBase.h
${HEADER_DIR}/Operand.h
${HEADER_DIR}/interpreter.h
${HEADER_DIR}/Command.h
${HEADER_DIR}/ObjectV2.h
${HEADER_DIR}/MediathequeV2.h
)
set(SOURCES
${SOURCE_DIR}/Consoleframebuffer.cpp
${SOURCE_DIR}/DataBase.cpp
${SOURCE_DIR}/Operand.cpp
${SOURCE_DIR}/interpreter.cpp
${SOURCE_DIR}/Command.cpp
${SOURCE_DIR}/ObjectV2.cpp
${SOURCE_DIR}/MediathequeV2.cpp
)

add_library(${PROJECT_NAME}

${SOURCES}
${HEADERS}
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")