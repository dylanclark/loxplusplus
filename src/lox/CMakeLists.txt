set(TARGET_NAME lox-core)

set(SOURCES 
    Error.cpp
    Eval.cpp
    Lox.cpp
    Object.cpp
    Parser.cpp
    Print.cpp
    Scanner.cpp
    Tokens.cpp
)

set(SOURCES_INC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_library(${TARGET_NAME} ${SOURCES})

target_precompile_headers(${TARGET_NAME} 
    PRIVATE 
        ${APP_INC}/loxpp_pch.h
)

target_include_directories(${TARGET_NAME} 
    PRIVATE 
        ${APP_INC}
        ${SOURCES_INC}
)