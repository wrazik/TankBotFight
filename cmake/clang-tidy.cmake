include_guard()

function(add_tidy_target TIDY_VERSION)
  set(options)
  set(oneValueArgs)
  set(multiValueArgs FILES)
  cmake_parse_arguments(add_tidy_target "${options}" "${oneValueArgs}"
                        "${multiValueArgs}" ${ARGN})

  find_program(CLANG_TIDY_BIN clang-tidy-${TIDY_VERSION} REQUIRED PATHS /usr/bin)
  find_program(RUN_CLANG_TIDY_BIN NAMES run-clang-tidy-${TIDY_VERSION}.py run-clang-tidy-${TIDY_VERSION} REQUIRED PATHS /usr/bin)

  if(CLANG_TIDY_BIN STREQUAL "CLANG_TIDY_BIN-NOTFOUND")
    message(FATAL_ERROR "unable to locate clang-tidy-${TIDY_VERSION}")
  endif()

  if(RUN_CLANG_TIDY_BIN STREQUAL "RUN_CLANG_TIDY_BIN-NOTFOUND")
    message(FATAL_ERROR "unable to locate run-clang-tidy-${TIDY_VERSION}.py")
  endif()

  list(
    APPEND
    RUN_CLANG_TIDY_BIN_ARGS
    -clang-tidy-binary
    ${CLANG_TIDY_BIN}
    -header-filter=.*
    -checks=clang-diagnostic-*,clang-analyzer-*,bugprone-*,cert-*,clang-analyzer-*,concurrency-*,cppcoreguidelines-*,hicpp-*,misc-*,modernize-*,performance-*,portability-*,readability-*
    -p=${CMAKE_BINARY_DIR}
    ${add_tidy_target_FILES}
    )

  add_custom_target(
    tidy
    COMMAND ${RUN_CLANG_TIDY_BIN} ${RUN_CLANG_TIDY_BIN_ARGS}
    COMMENT "running clang tidy")

endfunction(add_tidy_target)
