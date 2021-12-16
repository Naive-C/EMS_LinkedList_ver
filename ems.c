#include "ems.h"

void create_file()
{
	if(APPEND_FILE){
		perror("APPEND FILE");
		exit(1);
	}

	fclose(fp);
}

void load_file(Employee* hd)
{
	Employee* tmp,
			* last;

	if(RD_FILE){
		create_file();
	}

	tmp = (Employee*)malloc(sizeof(Employee));
	fread(tmp, sizeof(Employee), 1, fp);
	if(feof(fp)==0){
		hd->link = tmp;
		last     = tmp; 
	}
	else{
		free(tmp);
	}

	for(;;){
		tmp = (Employee*)malloc(sizeof(Employee));
		fread(tmp, sizeof(Employee), 1, fp);

		if(feof(fp)==0){
			last->link = tmp;
			last       = tmp;
		}
		else{
			free(tmp);
			break;
		}
	}
	fclose(fp);
}

void init_record(Employee* record)
{
	record->id     = 0;
	record->salary = 0;
	sprintf(record->first_name, "null");
	sprintf(record->last_name , "null");
	record->link = NULL;
}

void view(Employee* hd)
{
	Employee* tmp = hd->link;

	//TODO: 헤더 출력
	printf("-------------------------------------------------------\n");
	printf("|ID        |First Name     |Last Name      |Salary    |\n");
	printf("-------------------------------------------------------\n");
	while(tmp != NULL){
	//TODO: sort구현
	    printf("|%-10zu|%-15s|%-15s|%-10zu|\n",
				tmp->id, tmp->first_name, tmp->last_name, tmp->salary);
		tmp = tmp->link;
	}
	printf("-------------------------------------------------------\n");
	free(tmp);

	while(getchar() != '\n'){
		continue;
	}
	getchar();
}

void add()
{
	Employee* record;
	record = (Employee*)malloc(sizeof(Employee));
	
	if(APPEND_FILE){
		perror("fopen employeefile");
		exit(1);
	}

	for(;;){
		printf(">> first name: ");
		scanf("%s", record->first_name);
		if(strcmp(record->first_name, ".") == 0) {break;}

		printf(">> last name : ");
		scanf("%s", record->last_name);
		if(strcmp(record->last_name, ".") == 0) {break;}

		printf(">> salary    : ");
		scanf("%lu", &record->salary);
		
		record->id = getpid();

		fwrite((char *) record, sizeof(Employee), 1, fp);
	}
	free(record);
	fclose(fp);
}

void search_option(Employee* hd)
{
    print_header(">> Choose Search Option");
    printf("          <1> ID <2> First Name <3> Last Name          \n");
    printf("-------------------------------------------------------\n");
    printf("                                               <0> Exit\n");
    printf("Choose Option: ");

unknown_char_search_menu_retry:
	while(getchar() != '\n'){
		continue;
	}
    switch(getchar()){
        case '1':
			search(hd, ID);
			break;
		case '2': 
			search(hd, F_NAME);
			break;
        case '3':
			search(hd, L_NAME);
			break;
		case '0': 
			main_menu("", hd);
            fclose(fp);
            break;
        default:
    		printf("Choose Option: ");
            goto unknown_char_search_menu_retry;
    } 
}

void search(Employee* hd, const char option)
{
	Employee* tmp = hd->link,
			* record;
	record = (Employee*)malloc(sizeof(Employee));

	bool id,
		 f_name,
		 l_name;
	
	switch(option){
		case ID:
			printf(">> Search ID		: ");
			scanf("%zu", &record->id	   );
			break;
		case F_NAME:
			printf(">> Search First Name: ");
			scanf("%s" , record->first_name);
			break;
		case L_NAME:	
			printf(">> Search Last Name : ");
			scanf("%s" , record->last_name );
			break;
	}

	printf("-------------------------------------------------------\n");
	printf("|ID        |First Name     |Last Name      |Salary    |\n");
	printf("-------------------------------------------------------\n");
	while(tmp != NULL){
		id     = (record->id == tmp->id);	
		f_name = (strcmp(record->first_name, tmp->first_name)) + 1;	
		l_name = (strcmp(record->last_name, tmp->last_name)) + 1;	
	
		if(id     == 1 && ID     == option 
		|| f_name == 1 && F_NAME == option 	
		|| l_name == 1 && L_NAME == option){
			printf("|%-10zu|%-15s|%-15s|%-10zu|\n",
				tmp->id, tmp->first_name, tmp->last_name, tmp->salary);
		}
		else{
			//TODO: 일치하는 직원이 없는 경우 처리
		}
		tmp = tmp->link;
	}
	printf("-------------------------------------------------------\n");
	free(tmp);

	while(getchar() != '\n'){
		continue;
	}
	getchar();
}

void modify(Employee *hd)
{
	Employee *origin = hd->link;	
	Employee *modify;

	modify = (Employee*)malloc(sizeof(Employee));

	short id = 0;

	FILE* tmp_fp;
	if((tmp_fp = fopen("tmp", "a")) == NULL){
		exit(1);
	}

	printf(">> ID: ");
	scanf("%zu", &modify->id);
	//TODO: 일치하는 직원이 없는 경우 출력
	
	printf(">> ID: ");
	scanf("%s", modify->first_name);

	printf(">> ID: ");
	scanf("%s", modify->last_name);

	printf(">> ID: ");
	scanf("%zu", &modify->salary);

	while(origin != NULL){
		//TODO: 입력한 데이터와 부합하는 데이터 삭제
		if(id == origin->id){
			printf("id: %zu\n"		 , modify->id		 );
			printf("first_name: %s\n", modify->first_name);
			printf("last_name: %s\n" , modify->last_name );
			printf("salary: %lu\n"   , modify->salary    );
			fwrite(modify, sizeof(Employee), 1, fp);	
		}
		fwrite(origin, sizeof(Employee), 1, fp);	
		origin = origin->link;
	}
	free(origin);

	//TODO: 재확인 구현
	remove("employeefile");
	rename("tmp", "employeefile");
}

void delete(Employee *hd)
{
	Employee *tmp = hd->link;
	size_t id = 0;

	printf(">> ID: ");
	scanf("%zu", &id);

	while(tmp != NULL){
		//TODO: 입력한 데이터와 부합하는 데이터 삭제
		if(id == tmp->id){
			printf("id: %zu\n"		 , tmp->id		  );
			printf("first_name: %s\n", tmp->first_name);
			printf("last_name: %s\n" , tmp->last_name );
			printf("salary: %lu\n"   , tmp->salary    );
		}
		fwrite(tmp, sizeof(Employee), 1, fp);	
		tmp = tmp->link;
	}
	free(tmp);

	//TODO: 재확인 구현
	remove("employeefile");
	rename("tmp", "employeefile");
}

void main_menu(const char *msg, Employee* hd)
{
	system("clear");
	print_header("");
    printf("       ▄   ▄  ▄▄   ▄ ▄▄▄   ▄▄▄▄   ▄▄  ▄▄▄  ▄  ▄        \n");
    printf("       █▀▄▀█ █  █  ▄ █  █  █ █ █ █▄▄█ █  █ █  █        \n");
    printf("       █   █ ▀▄▄▀▄ █ █  █  █ █ █ ▀▄▄  █  █ ▀▄▄▀▄       \n");
    printf("-------------------------------------------------------\n");
    printf("                  <1> View Employees	               \n");
    printf("                  <2> Search Employee                  \n");
    printf("                  <3> Add Employee                     \n");
    printf("                  <4> Modify Employee                  \n");
    printf("                  <5> Delete Employee                  \n");
    printf("-------------------------------------------------------\n");
    printf("                                               <0> exit\n");
    printf("Choose Option: ");

unknown_char_main_menu_retry:
	fflush(stdin);
    switch(getchar()){
        case '1':
			view(hd);
			break;
		case '2':
			search_option(hd);
			break;
        case '3':
			add();
			break;
		case '4':
			modify(hd);
			break;
		case '5':
			delete(hd);
			break;
		case '0': 
			exit(0);
        default:
    		printf("Choose Option: ");
			goto unknown_char_main_menu_retry;
    }   
}

void print_header(const char* current_page)
{ size_t center = (27 - (strlen(current_page) / 2));
	system("clear");
    printf("-------------------------------------------------------\n");
	for(size_t i = 0; i < center; ++i){
		printf(" ");
	}
	printf("%s\n", current_page);
    printf("-------------------------------------------------------\n");
}

int main()
{
	Employee *hd;
	hd = (Employee*)malloc(sizeof(Employee));

	if(!RD_FILE){
		init_record(hd);
		load_file(hd);
	}

	for(;;){
		main_menu("", hd);
	}

	Employee* tmp = hd,
			* tmp2;
	while(tmp != NULL){
		tmp2 = tmp->link;
		free(tmp);
		tmp = tmp2;
	}
}
