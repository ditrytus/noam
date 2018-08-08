project(ast_callback_visitor)

add_executable(ast_callback_visitor astCallbackVisitor.cpp ../text-brackets/text_brackets.cpp)

target_link_libraries(ast_callback_visitor noam)