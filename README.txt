The program is compiled and ran using the Makefile.
The makefile contains 3 different targets: pairs, depsandapps, and clean.

pairs - The target "pairs" should, given an input file storing a list of departments with vacancies and
	a preference list of applicants, and a list of applicants with a preference list of departments,
	output a well-formed allocation of job applicants to departmental vacancies, and nothing else.

depsandapps - The target "depsandapps" should, given an input file storing a list of departments with 
	vacancies and a preference list of applicants, and a list of applicants with a preference list 
	of departments, output for each department its index, name, vacancies, and preference list. Also output
	for each applicant its index, name, and preference list.

clean - The target clean should remove all object files and executables from the the directory.


The following is an example of how to run the program:
	Make pairs
	./pairs JobsApplicants.txt
