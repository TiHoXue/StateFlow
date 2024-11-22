add_library(stateflowlib STATIC StateBase.cpp)

target_include_directories(stateflowlib PUBLIC ${PROJECT_SOURCE_DIR}/include)
