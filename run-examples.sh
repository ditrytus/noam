#!/bin/bash

BUILD_DIR=${BUILD_DIR:-build}

echo "Running examples:"
echo "Example: arithmetic"
${BUILD_DIR}/examples/arithmetic/arithmetic

echo "Example: ast-callback-visitor"
${BUILD_DIR}/examples/ast-callback-visitor/ast_callback_visitor

echo "Example: ast-visitor-base"
${BUILD_DIR}/examples/ast-visitor-base/ast-visitor-base

echo "Example: ast-visitor-result"
${BUILD_DIR}/examples/ast-visitor-result/ast_visitor_result

echo "Example: backus-naur-for"
${BUILD_DIR}/examples/backus-naur-form/backus-naur-form

echo "Example: reverse-polish-notation"
${BUILD_DIR}/examples/reverse-polish-notation/reverse-polish-notation

echo "Example: roman-numerals"
${BUILD_DIR}/examples/roman-numerals/roman-numerals

echo "Example: text-brackets"
${BUILD_DIR}/examples/text-brackets/text_brackets
