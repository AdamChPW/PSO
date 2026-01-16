.SILENT:
	start
	comp
	test
	
comp: 
	gcc -Wall -Wextra --pedantic src/*.c -o bin/pso 

start: comp
	bin/pso Test/mapa

test: comp
	bin/pso Test/mapa_100x100
	