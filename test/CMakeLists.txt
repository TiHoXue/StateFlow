find_package(GTest REQUIRED)

set(TEST_SOURCES
    StateMachineBaseTest.cpp
)

foreach(source IN LISTS TEST_SOURCES)
  get_filename_component(source_name ${source} NAME)
  add_executable(${source_name} ${source})
  target_link_libraries(${source_name} PRIVATE GTest::gtest_main stateflowlib)
  add_test(NAME ${source_name} COMMAND ${source_name})
endforeach()

enable_testing()