cmake_minimum_required(VERSION 3.28)
project(Project1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Project1
        main.cpp
        parser/parser.cpp
        graphs/edmondsKarp.cpp
        matching/matching.cpp
        graph_builder/graph_builder.cpp
        generate_assignments/generate_assignments.cpp
        risk_analysis/risk_analysis.cpp
        output_writer/output_writer.cpp
        menu/menu.cpp
)

target_include_directories(Project1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)