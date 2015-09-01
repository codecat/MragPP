function(example name)
	add_executable(${name} "${name}.cpp" example.h)
	target_link_libraries(${name} Mragpp)
	include_directories(${name}
		../src/
		../src/Scratch/src/)
endfunction()

example(basic) # 01
example(atlas) # 02
example(spine) # 03
example(sound) # 04
example(music) # 05
example(shader) # 06
example(cubes) # 07
example(textures) # 08
