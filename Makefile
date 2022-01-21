output: main.o autonomous.o evaluation.o external_data.o map.o miscellaneous.o movement.o placement.o command_line_ui.o bots.o
	gcc -o output main.o autonomous.o evaluation.o external_data.o map.o miscellaneous.o movement.o placement.o command_line_ui.o bots.o
	
main.o: evaluation.h map.h miscellaneous.h movement.h placement.h command_line_ui.h defines.h structures.h
	gcc -c main.c

command_line_ui.o: command_line_ui.h structures.h
	gcc -c command_line_ui.c

map.o: map.h structures.h
	gcc -c map.c

autonomous.o: autonomous.h structures.h defines.h bots.h
	gcc -c autonomous.c

miscellaneous.o: miscellaneous.h structures.h
	gcc -c miscellaneous.c

movement.o: movement.h structures.h
	gcc -c movement.c

placement.o: placement.h structures.h
	gcc -c placement.c

evaluation.o: evaluation.h structures.h
	gcc -c evaluation.c

bots.o: bots.h structures.h placement.h movement.h
	gcc -c bots.c

external_data.o: external_data.h structures.h
	gcc -c external_data.c

clean:
	rm *.o output

