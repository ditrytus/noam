project(ast_visitor_base)

include_directories(../../src)

add_executable(ast_visitor_base astVisitorBase.cpp)

target_link_libraries(ast_visitor_base noam)