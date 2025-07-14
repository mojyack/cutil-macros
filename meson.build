project('cutil-macros', 'cpp', version : '0.0', default_options : ['warning_level=3', 'werror=false', 'cpp_std=c++23'])
add_project_arguments('-Wfatal-errors', language: 'cpp')

executable('assert-test', files('src/assert-test.cpp'))
executable('print-test', files('src/print-test.cpp'))
executable('logger-test', files('src/logger-test.cpp'))
executable('coop-assert-test', files('src/coop-assert-test.cpp'),  dependencies : [dependency('coop')])
