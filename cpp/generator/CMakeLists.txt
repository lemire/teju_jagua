# SPDX-License-Identifier: APACHE-2.0
# SPDX-FileCopyrightText: 2021-2025 Cassio Neri <cassio.neri@gmail.com>

add_executable(teju_generator
  config.cpp
  generator.cpp
  main.cpp
)

target_include_directories(teju_generator PRIVATE
  "${CMAKE_SOURCE_DIR}"
)

target_link_libraries(teju_generator PRIVATE
  boost_multiprecision
  nlohmann_json::nlohmann_json
  teju
  common
)
