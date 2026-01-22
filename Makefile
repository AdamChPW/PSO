.SILENT:
	start
	comp
	test
	
comp: 
	gcc -Wall -Wextra --pedantic src/*.c -o bin/pso 

start: comp
	bin/pso Test/mapa -p 5 -i 100 -n 5

test: comp
	bin/pso Test/mapa_100x100 -p 30 -i 100 -n 10
	