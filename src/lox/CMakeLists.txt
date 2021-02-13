set(TARGET_NAME lox-core)

set(SOURCES 
    Error.cpp
    Lox.cpp
)

add_library(${TARGET_NAME} ${SOURCES})
target_precompile_headers(${TARGET_NAME} PRIVATE ${APP_INC}/loxpp_pch.h)
target_include_directories(${TARGET_NAME} PRIVATE ${APP_INC})