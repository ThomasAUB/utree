set(UTREE_UNIT_TESTS utree_tests)

include(CTest)

file(GLOB TARGET_SRC "./tests.cpp" )

add_executable(${UTREE_UNIT_TESTS} ${TARGET_SRC})

add_test(${UTREE_UNIT_TESTS} ${UTREE_UNIT_TESTS})