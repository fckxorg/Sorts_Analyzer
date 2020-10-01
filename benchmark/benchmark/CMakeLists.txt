add_library(Benchmark service.hpp stat.hpp service.cpp)

set_target_properties(Benchmark PROPERTIES LINKER_LANGUAGE CXX)
