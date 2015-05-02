function(example name)
	add_executable(${name} "${name}.cpp" example.h)
	target_link_libraries(${name} Mragpp)
	include_directories(${name}
		../src/
		../src/Scratch/src/)
endfunction()

example(basic)
example(atlas)
example(spine)
