antirag: main.o admin.o antirag.o auth.o globals.o raginfo.o utils.o victim.o volunteer.o volunteerrecruitment.o
	gcc main.o admin.o antirag.o auth.o globals.o raginfo.o utils.o victim.o volunteer.o volunteerrecruitment.o -o antirag

main.o: main.c
	gcc -c main.c

admin.o: admin.c
	gcc -c admin.c

antirag.o: antirag.c
	gcc -c antirag.c

auth.o: auth.c
	gcc -c auth.c

globals.o: globals.c
	gcc -c globals.c

raginfo.o: raginfo.c
	gcc -c raginfo.c

utils.o: utils.c
	gcc -c utils.c

victim.o: victim.c
	gcc -c victim.c

volunteer.o: volunteer.c
	gcc -c volunteer.c

volunteerrecruitment.o: volunteerrecruitment.c
	gcc -c volunteerrecruitment.c

clean:
	del *.o
	del antirag.exe