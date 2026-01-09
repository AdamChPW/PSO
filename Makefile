.SILENT:
	start
	comp
	
comp:
	gcc -Wall -Wextra --pedantic src/*.c -o bin/pso 

start: comp

test: comp
	bin/pso Test/mapa