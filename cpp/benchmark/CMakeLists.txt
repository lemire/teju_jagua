# SPDX-License-Identifier: APACHE-2.0
# SPDX-FileCopyrightText: 2021-2025 Cassio Neri <cassio.neri@gmail.com>

add_executable(teju_benchmark
  main.cpp
)

target_include_directories(teju_benchmark PRIVATE
    "${CMAKE_SOURCE_DIR}"
    "${CMAKE_SOURCE_DIR}/cpp/common/include"
)

target_link_libraries(teju_benchmark PRIVATE
  common
  teju
  gtest
  nanobench
)
