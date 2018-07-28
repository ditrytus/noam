project(ast_visitor_result)

include_directories(../../src)

add_executable(ast_visitor_result astVisitorResult.cpp)

target_link_libraries(ast_visitor_result noam)