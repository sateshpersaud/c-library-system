/**
 * This program was created to manage the textbook loan records of Queen's College
 * as part of my Caribbean Advanced Proficiency  Examinations (CAPE) Internal Assessment
 * of June 2016.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void main_menu(char* return_message);
void add_new_book();
void view_books();
void search_books();
void preform_book_search(int search_option, char* search_scope);
void add_new_student();
void view_students();
void search_students();
void preform_student_search(int search_option, char* search_scope);
void loan_book();
void view_overdue_books();
void return_book();
int date_to_timestamp(int year, int month, int date);
void print_header(char *page);

FILE *books, *students, *loans;

time_t now;

struct add_book {
	char title[150];
	char author[150];
	char publisher[150];
	char subject[150];
	char amount[150];
	char id[150];
	char date_added[150];
};
struct add_book book;

struct add_student {
	char name[150];
	char grade[150];
	char id[150];
	char date_added[150];
};
struct add_student student;

struct loan_book {
	char student_id[150];
	char book_id[150];
	char id[150];
	char date_loaned[150];
	int date_to_return;
};
struct loan_book loan;

int main()
{
	main_menu("");
	return 0;
}

void main_menu(char* return_message)
{
	// Set the window size to 105 columns wide and 43 lines long
	system("mode CON: COLS=105 LINES=43");

	// Set the window title
	system("TITLE Queen's College Textbook Loan Management System");

	print_header("");
	printf("                                   .--.                   .---.\n");
	printf("                               .---|__|           .-.     |~~~|\n");
	printf("                            .--|===|--|           |_|     |~~~|--.\n");
	printf("                            ||||===|  |       .---!~|  .--|   |--|\n");
	printf("                            ||||   |  |       |===| |--|  |   |  |\n");
	printf("                            | ||   |  |       |   | |__|  |   |  |\n");
	printf("                            | ||   |  |       |===| |==|  |   |  |\n");
	printf("                            |  |   |__|       |   |_|__|  |~~~|__|\n");
	printf("                            |--|===|--|       |===|~|--|  |~~~|--|\n");
	printf("                            `--^---'--'       `---^-^--^--^---'--'\n\n\n");
	printf("                        -------------------------------------------------\n\n");
	printf("                   >> BOOKS <<             >> STUDENTS <<            >> LOANS <<\n\n\n");
	printf("                 <1> Add New Book        <4> Add New Student       <7> Loan Book\n\n");
	printf("                 <2> View Books          <5> View Students         <8> View Overdue Books\n\n");
	printf("                 <3> Search Books        <6> Search Students       <9> Return Book\n\n");
	printf("                         ................................................\n\n");
	printf("                                                                        <0> Exit\n");
	printf("                                       %s      \n\n\n", return_message);
	printf("                             Choose An Option: ");

 main_menu_options_retry:
	switch (getch()) {
	case '1':
		add_new_book();
		break;

	case '2':
		(books = fopen("Books.txt", "r")) == NULL ? main_menu("No Book Records Exist") : view_books();
		break;

	case '3':
		(books = fopen("Books.txt", "r")) == NULL ? main_menu("No Book Records Exist") : search_books();
		break;

	case '4':
		add_new_student();
		break;

	case '5':
		(students = fopen("Students.txt", "r")) == NULL ? main_menu("No Student Records Exist") : view_students();
		break;

	case '6':
		(students = fopen("Students.txt", "r")) == NULL ? main_menu("No Student Records Exist") : search_students();
		break;

	case '7':
		(students = fopen("Students.txt", "r")) == NULL ? main_menu("No Student Records Exist") :
		(books = fopen("Books.txt", "r")) == NULL ? main_menu("No Book Records Exist") : loan_book();
		break;

	case '8':
		(loans = fopen("Loans.txt", "r")) == NULL ? main_menu("No Loan Records Exist") : view_overdue_books();
		break;

	case '9':
		(loans = fopen("Loans.txt", "r")) == NULL ? main_menu("No Loan Records Exist") : return_book();
		break;

	case '0':
		exit(0);
		break;

	default:
		// Simply restart the switch if the user enters an invalid option
		goto main_menu_options_retry;
	}
}

void add_new_book()
{
	print_header("       Books >> Add New Book >>\n\n\n\n");

	time(&now);

	printf("            >> Title: ");
	fflush(stdin);
	scanf("%[^\n]", book.title);

	printf("\n           >> Author: ");
	fflush(stdin);
	scanf("%[^\n]", book.author);

	printf("\n        >> Publisher: ");
	fflush(stdin);
	scanf("%[^\n]", book.publisher);

	printf("\n          >> Subject: ");
	fflush(stdin);
	scanf("%[^\n]", book.subject);

	printf("\n               >> ID: ");
	fflush(stdin);
	scanf("%[^\n]", book.id);

	printf("\n           >> Amount: ");
	fflush(stdin);
	scanf("%[^\n]", book.amount);

	print_header("       Books >> New Book >>\n\n\n");
	printf("             >> Title: %s\n\n", &book.title);
	printf("            >> Author: %s\n\n", &book.author);
	printf("         >> Publisher: %s\n\n", &book.publisher);
	printf("           >> Subject: %s\n\n", &book.subject);
	printf("                >> ID: %s\n\n", &book.id);
	printf("            >> Amount: %s\n\n", &book.amount);
	printf("        >> Date Added: %s\n", strcpy(book.date_added, ctime(&now)));
	printf("         -------------------------------------------------------------------------------\n\n");
	printf("                   Are you sure you wish to Add this Record?\n\n");
	printf("                           <Y> Yes            <N> No\n\n\n ");
	printf("                              Choose an Option: ");

 add_new_book_confirmation_retry:
	// Convert the user entry to lower case in case their caps lock is on
	switch (tolower(getch())) {
	case 'y':
		fprintf(books = fopen("Books.txt", "a+"), "%s\n%s\n%s\n%s\n%s\n%s\n%s",
			&book.title, &book.author, &book.publisher, &book.subject, &book.id, &book.amount, &book.date_added);
		fclose(books);
		main_menu("Record Added Successfully");
		break;

	case 'n':
		main_menu("");
		break;

	default:
		goto add_new_book_confirmation_retry;
	}
}

void view_books()
{
	// Increase the number of lines to allow for a long list of records
	system("mode CON: COLS=105 LINES=500");

	print_header("       Books >> View Books >>\n\n");

	int counter = 0;

	while (!feof(books)) {
		fscanf(books, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
		       &book.title, &book.author, &book.publisher, &book.subject, &book.id, &book.amount, &book.date_added);

		counter++;

		printf("\n             >> Title: %s\n", &book.title);
		printf("            >> Author: %s\n", &book.author);
		printf("         >> Publisher: %s\n", &book.publisher);
		printf("           >> Subject: %s\n", &book.subject);
		printf("                >> ID: %s\n", &book.id);
		printf("            >> Amount: %s\n", &book.amount);
		printf("        >> Date Added: %s\n\n", &book.date_added);
		printf("         -------------------------------------------------------------------------------\n");
	}
	printf("\n                                  %d %s Available\n\n", counter, counter < 2 ? "Record" : "Records");
	printf("                        Press any Key to Return to the Main Menu");

	getch();
	fclose(books);
	main_menu("");
}

void search_books()
{
	print_header("       Books >> Search Books >>\n\n\n");
	printf("    <1> Everywhere\n\n    <2> Titles\n\n    <3> Authors\n\n    <4> Publishers\n\n    <5> Subjects\n\n    <6> IDs\n\n    <0> Cancel\n\n\n");
	printf("        Choose an Option: ");

 search_books_options_retry:
	switch (getch()) {
	case '1':
		preform_book_search(1, "Everywhere");
		break;

	case '2':
		preform_book_search(2, "Titles");
		break;

	case '3':
		preform_book_search(3, "Authors");
		break;

	case '4':
		preform_book_search(4, "Publishers");
		break;

	case '5':
		preform_book_search(5, "Subjects");
		break;

	case '6':
		preform_book_search(6, "IDs");
		break;

	case '0':
		fclose(books);
		main_menu("");
		break;

	default:
		goto search_books_options_retry;
	}
}

void preform_book_search(int search_option, char* search_scope)
{
	system("mode CON: COLS=105 LINES=500");

	print_header("       Books >> Search Books >> ");
	printf(" %s >>\n\n\n", search_scope);

	char search[20], *title_search, *author_search, *publisher_search, *subject_search,
	     *id_search, temp_title[100], temp_author[100], temp_publisher[100], temp_subject[100], temp_id[100];

	int counter = 0;

	fflush(stdin);
	printf("         >> Search: ");
	scanf("%[^\n]", search);
	// Convert the user entry to lower case to allow for case insensitive search
	strlwr(search);

	// Move the file pointer back to the start of the file
	// A previous search may have moved the pointer somewhere inside the file so we need to reset it
	fseek(books, 0, SEEK_END);
	rewind(books);

	while (!feof(books)) {
		fscanf(books, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
		       &book.title, &book.author, &book.publisher, &book.subject, &book.id, &book.amount, &book.date_added);

		// Copy the attribute to a temporary variable, convert it to lower case and compare it with the search term the user entered
		title_search = strstr(strlwr(strcpy(temp_title, book.title)), search);

		author_search = strstr(strlwr(strcpy(temp_author, book.author)), search);

		publisher_search = strstr(strlwr(strcpy(temp_publisher, book.publisher)), search);

		subject_search = strstr(strlwr(strcpy(temp_subject, book.subject)), search);

		id_search = strstr(strlwr(strcpy(temp_id, book.id)), search);

		if ((search_option == 1 && (title_search != NULL || author_search != NULL || publisher_search != NULL || subject_search != NULL)) ||
		    (search_option == 2 && title_search != NULL) ||
		    (search_option == 3 && author_search != NULL) ||
		    (search_option == 4 && publisher_search != NULL) ||
		    (search_option == 5 && subject_search != NULL) ||
		    (search_option == 6 && id_search != NULL)) {
			counter++;

			printf("\n             >> Title: %s\n", &book.title);
			printf("            >> Author: %s\n", &book.author);
			printf("         >> Publisher: %s\n", &book.publisher);
			printf("           >> Subject: %s\n", &book.subject);
			printf("                >> ID: %s\n", &book.id);
			printf("            >> Amount: %s\n", &book.amount);
			printf("        >> Date Added: %s\n\n", &book.date_added);
			printf("         -------------------------------------------------------------------------------\n");
		}
	}

	printf("\n\n                              %d %s Found for \"%s\"\n\n\n", counter, counter < 2 ? "Result" : "Results", search);
	printf("         <1> Search again in %s     <2> New Search     <0> Return to Main Menu\n\n\n", search_scope);
	printf("                  Choose an Option: ");

 preform_book_search_options_retry:
	switch (getch()) {
	case '1':
		preform_book_search(search_option, search_scope);
		break;

	case '2':
		search_books();
		break;

	case '0':
		fclose(books);
		main_menu("");
		break;

	default:
		goto preform_book_search_options_retry;
	}
}

void add_new_student()
{
	print_header("       Students >> Add New Student >>\n\n\n");

	time(&now);

	printf("\n            >> Name: ");
	fflush(stdin);
	scanf("%[^\n]", student.name);

	printf("\n           >> Grade: ");
	fflush(stdin);
	scanf("%[^\n]", student.grade);

	printf("\n              >> ID: ");
	fflush(stdin);
	scanf("%[^\n]", student.id);

	print_header("       Students >> New Student >>\n\n\n");
	printf("            >> Name: %s\n\n", &student.name);
	printf("           >> Class: %s\n\n", &student.grade);
	printf("              >> ID: %s\n\n", &student.id);
	printf("      >> Date Added: %s\n\n", strcpy(student.date_added, ctime(&now)));
	printf("         -------------------------------------------------------------------------------\n");
	printf("\n\n                   Are you sure you wish to Add this Record?\n\n");
	printf("                          <Y> Yes            <N> No\n\n\n");
	printf("                               Choose an Option: ");

 add_new_student_options_retry:
	switch (tolower(getch())) {
	case 'y':
		fprintf(students = fopen("Students.txt", "a+"), "%s\n%s\n%s\n%s", &student.name, &student.grade, &student.id, &student.date_added);
		fclose(students);
		main_menu("Record Added Successfully");
		break;

	case 'n':
		main_menu("");
		break;

	default:
		goto add_new_student_options_retry;
	}
}

void view_students()
{
	system("mode CON: COLS=105 LINES=999");

	print_header("       Students >> View Students >>\n\n");

	int counter = 0;

	while (!feof(students)) {
		fscanf(students, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n", &student.name, &student.grade, &student.id, &student.date_added);

		counter++;

		printf("            >> Name: %s\n", &student.name);
		printf("           >> Grade: %s\n", &student.grade);
		printf("              >> ID: %s\n", &student.id);
		printf("      >> Date Added: %s\n", &student.date_added);
		printf("\n         -------------------------------------------------------------------------------\n\n");
	}
	printf("\n                                  %d %s Available", counter, counter < 2 ? "Record" : "Records");
	printf("\n\n                        Press any Key to Return to the Main Menu");

	getch();
	fclose(students);
	main_menu("");
}

void search_students()
{
	print_header("       Students >> Search Students >>\n\n\n");
	printf("    <1> Everywhere\n\n    <2> Names\n\n    <3> Grades\n\n    <4> IDs\n\n    <0> Cancel\n\n\n");
	printf("        Choose an Option: ");

 search_scope_retry:
	switch (getch()) {
	case '1':
		preform_student_search(1, "Everywhere");
		break;

	case '2':
		preform_student_search(2, "Names");
		break;

	case '3':
		preform_student_search(3, "Grades");
		break;

	case '4':
		preform_student_search(4, "IDs");
		break;

	case '0':
		fclose(students);
		main_menu("");
		break;

	default:
		goto search_scope_retry;
	}
}

void preform_student_search(int search_option, char* search_scope)
{
	system("mode CON: COLS=105 LINES=500");

	print_header("       Students >> Search Students >> ");
	printf("%s >>\n\n\n", search_scope);

	char search[20], *name_search, *grade_search, *id_search, temp_name[100], temp_grade[100], temp_id[100];

	int counter = 0;

	fflush(stdin);
	printf("         >> Search: ");
	scanf("%[^\n]", search);
	strlwr(search);

	fseek(students, 0, SEEK_END);
	rewind(students);

	while (!feof(students)) {
		fscanf(students, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n", &student.name, &student.grade, &student.id, &student.date_added);

		name_search = strstr(strlwr(strcpy(temp_name, student.name)), search);

		grade_search = strstr(strlwr(strcpy(temp_grade, student.grade)), search);

		id_search = strstr(strlwr(strcpy(temp_id, student.id)), search);

		if ((search_option == 1 && (name_search != NULL || grade_search != NULL || id_search != NULL)) ||
		    (search_option == 2 && name_search != NULL) ||
		    (search_option == 3 && grade_search != NULL) ||
		    (search_option == 4 && id_search != NULL)) {
			counter++;

			printf("\n              >> Name: %s\n", &student.name);
			printf("             >> Grade: %s\n", &student.grade);
			printf("                >> ID: %s\n", &student.id);
			printf("        >> Date Added: %s\n\n", &student.date_added);
			printf("         -------------------------------------------------------------------------------\n");
		}
	}
	printf("\n\n                              %d %s Found for \"%s\"\n\n\n", counter, counter < 2 ? "Result" : "Results", search);
	printf("         <1> Search again in %s     <2> New Search     <0> Return to Main Menu\n\n\n", search_scope);
	printf("                  Choose an Option: ");

 preform_student_search_options_retry:
	switch (getch()) {
	case '1':
		preform_student_search(search_option, search_scope);
		break;

	case '2':
		search_students();
		break;

	case '0':
		fclose(students);
		main_menu("");
		break;

	default:
		goto preform_student_search_options_retry;
	}
}

void loan_book()
{
	system("mode CON: COLS=105 LINES=50");

	print_header("       Loans >> Loan Book >>\n\n\n");

	time(&now);

	int found_book = 0, found_student = 0, year = 0, month = 0, date = 0;

	char student_id[150], book_id[150];

	fflush(stdin);
	printf("       >> Student ID: ");
	scanf("%[^\n]", student_id);

	fseek(students, 0, SEEK_END);
	rewind(students);

	while (!feof(students)) {
		fscanf(students, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n", &student.name, &student.grade, &student.id, &student.date_added);

		if (strcmp(student_id, student.id) == 0) {
			printf("\n\n              >> Name: %s\n\n             >> Class: %s", &student.name, &student.grade);
			found_student = 1;
			strcpy(loan.student_id, student.id);
		}
	}
	if (found_student != 1) {
		printf("\n\n\n                  No student with ID: %s Found\n\n\n\n", student_id);
		printf("           <1> New Loan              <0> Main Menu\n\n\n                 Choose an Option: ");

 loan_book_student_options_retry:
		switch (getch()) {
		case '1':
			loan_book();

			break;

		case '0':
			main_menu("");
			break;

		default:
			goto loan_book_student_options_retry;
		}
	}
	fflush(stdin);
	printf("\n\n\n         >> Book ID: ");
	scanf("%[^\n]", book_id);

	fseek(books, 0, SEEK_END);
	rewind(books);

	while (!feof(books)) {
		fscanf(books, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
		       &book.title, &book.author, &book.publisher, &book.subject, &book.id, &book.amount, &book.date_added);

		if (strcmp(book_id, book.id) == 0) {
			printf("\n\n             >> Title: %s\n\n            >> Author: %s\n\n         >> Publisher: %s\n\n           >> Subject: %s",
			       &book.title, &book.author, &book.publisher, &book.subject);
			found_book = 1;
			strcpy(loan.book_id, book.id);
		}
	}
	if (!found_book) {
		printf("\n\n\n                  No Book with ID: %s Found\n\n\n\n", book_id);
		printf("           <1> New Loan              <0> Main Menu\n\n\n                 Choose an Option: ");

 loan_book_book_options_retry:
		switch (getch()) {
		case '1':
			loan_book();
			break;

		case '0':
			fclose(students);
			fclose(books);
			main_menu("");
			break;

		default:
			goto loan_book_book_options_retry;
		}
	}
	printf("\n\n     >> Date to Return\n\n");
	printf("           Year(YYYY): ");
	scanf("%d", &year);
	printf("            Month(MM): ");
	scanf("%d", &month);
	printf("             Date(DD): ");
	scanf("%d", &date);
	loan.date_to_return = date_to_timestamp(year, month, date);

	printf("\n\n         -------------------------------------------------------------------------------\n\n");
	printf("                   Are you sure you wish to Add this Record?\n\n");
	printf("                          <Y> Yes            <N> No\n\n\n");
	printf("                               Choose an Option: ");

 loan_book_confirm_loan_options_retry:
	switch (tolower(getch())) {
	case 'y':
		fprintf(loans = fopen("Loans.txt", "a+"), "%s\n%s\n%s%s\n%s%d\n",
			&loan.student_id, &loan.book_id, &loan.student_id, &loan.book_id, strcpy(loan.date_loaned, ctime(&now)), loan.date_to_return);
		fclose(loans);
		main_menu("Book Loaned Successfully");
		break;

	case 'n':
		main_menu("");
		break;

	default:
		goto loan_book_confirm_loan_options_retry;
	}
}

void view_overdue_books()
{
	system("mode CON: COLS=105 LINES=500");
	print_header("       Loans >> View Overdue Books >>\n\n\n");

	int counter = 0, current_time = time(NULL);

	books = fopen("Books.txt", "r");

	students = fopen("Students.txt", "r");

	while (!feof(loans)) {
		fscanf(loans, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%ld\n", &loan.student_id, &loan.book_id, &loan.id, &loan.date_loaned, &loan.date_to_return);

		if (loan.date_to_return < current_time) {
			fseek(students, 0, SEEK_END);
			rewind(students);

			while (!feof(students)) {
				fscanf(students, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n", &student.name, &student.grade, &student.id, &student.date_added);

				if (strcmp(loan.student_id, student.id) == 0) {
					printf("           >> Student");
					printf("\n\n              >> Name: %s\n\n             >> Class: %s\n\n", &student.name, &student.grade);
				}
			}
			fseek(books, 0, SEEK_END);
			rewind(books);

			while (!feof(books)) {
				fscanf(books, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n",
				       &book.title, &book.author, &book.publisher, &book.subject, &book.id, &book.amount, &book.date_added);

				if (strcmp(loan.book_id, book.id) == 0) {
					printf("           >> Book");
					printf("\n\n             >> Title: %s\n\n            >> Author: %s\n\n         >> Publisher: %s\n\n           >> Subject: %s",
					       &book.title, &book.author, &book.publisher, &book.subject);
				}
			}
			time_t date_to_return_timestamp = loan.date_to_return;
			printf("\n\n\n       >> Date Loaned: %s", &loan.date_loaned);
			printf("\n\n    >> Date to Return: %s", ctime(&date_to_return_timestamp));
			printf("\n\n         -------------------------------------------------------------------------------\n\n");
			counter++;
		}
	}
	printf("\n                                  %d %s Available", counter, counter == 1 ? "Record" : "Records");
	printf("\n\n                        Press any Key to Return to the Main Menu");

	fclose(books);
	fclose(students);
	fclose(loans);

	getch();
	main_menu("");
}

void return_book()
{
	print_header("       Loans >> Return Book >>\n\n\n\n");

	FILE *loans2;

	int found = 0;

	char student_id[150], book_id[150], loan_id[150];

	fflush(stdin);
	printf("         >> Student ID: ");
	scanf("%[^\n]", student_id);
	fflush(stdin);

	printf("\n\n\n            >> Book ID: ");
	scanf("%[^\n]", book_id);
	strcpy(loan_id, student_id);
	// Concatenate the student ID and book ID to determine the loan ID
	strcat(loan_id, book_id);

	fseek(loans, 0, SEEK_END);
	rewind(loans);

	while (!feof(loans)) {
		fscanf(loans, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n", &loan.student_id, &loan.book_id, &loan.id, &loan.date_loaned, &loan.date_to_return);

		if (strcmp(loan.id, loan_id) == 0) {
			found = 1;
		}
	}
	if (found == 1) {
		printf("\n\n                                    Loan Found\n");
		printf("\n\n         -------------------------------------------------------------------------------\n\n");
		printf("                   Are you sure you wish to Return this Book?\n\n");
		printf("                          <Y> Yes            <N> No\n\n\n");
		printf("                               Choose an Option: ");
 return_book_confirm_return_options_retry:
		switch (tolower(getch())) {
		case 'y':
			fseek(loans, 0, SEEK_END);
			rewind(loans);
			loans2 = fopen("Loans2.txt", "a+");

			while (!feof(loans)) {
				fscanf(loans, "%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n", &loan.student_id, &loan.book_id, &loan.id, &loan.date_loaned, &loan.date_to_return);

				if (strcmp(loan.id, loan_id) != 0) {
					fprintf(loans2, "%s\n%s\n%s\n%s\n%s\n", &loan.student_id, &loan.book_id, &loan.id, &loan.date_loaned, &loan.date_to_return);
				}
			}
			fclose(loans);
			remove("Loans.txt");
			long savedOffset = ftell(loans2);
			fseek(loans2, 0, SEEK_END);
			if (ftell(loans2) == 0) {
				fclose(loans2);
				remove("Loans2.txt");
			}
			fclose(loans2);
			rename("Loans2.txt", "Loans.txt");
			main_menu("Book Returned Successfully");
			break;

		case 'n':
			fclose(loans);
			main_menu("");
			break;

		default:
			goto return_book_confirm_return_options_retry;
		}
	}else  {
		printf("\n\n\n                              No Record Found\n\n\n\n");
		printf("           <1> Return Another Book              <0> Main Menu\n\n\n                 Choose an Option: ");

 return_book_not_found_options_retry:
		switch (getch()) {
		case '1':
			return_book();
			break;

		case '0':
			fclose(loans);
			main_menu("");
			break;

		default:
			goto return_book_not_found_options_retry;
		}
	}
}

int date_to_timestamp(int year, int month, int date)
{
	struct tm return_date;

	return_date.tm_year = year - 1900;
	return_date.tm_mon = month - 1;
	return_date.tm_mday = date;
	return_date.tm_hour = 0;
	return_date.tm_min = 0;
	return_date.tm_sec = 0;
	return_date.tm_isdst = 0;
	return mktime(&return_date);
}

void print_header(char *page)
{
	system("cls");
	printf("\n\n          ******************************************************************************\n\n\n");
	printf("                          QUEEN'S COLLEGE TEXTBOOK LOAN MANAGEMENT SYSTEM\n\n\n");
	printf("          ******************************************************************************\n\n");
	printf(page);
}
