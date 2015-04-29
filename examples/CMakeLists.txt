function(example name)
	add_executable(${name} "${name}.cpp")
	target_link_libraries(${name} Mragpp)
	include_directories(${name}
		../src/
		../src/Scratch/src/)
endfunction()

example(basic)
