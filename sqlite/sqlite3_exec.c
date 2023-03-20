#include <stdio.h>
#include <sqlite3.h>

int callback(void *para, int f_num, char **f_value, char **f_name)
{
	printf("%s\n", (char *)para);

	for (int i = 0; i < f_num; i++)
		printf("%-15s", f_name[i]);
	puts(" ");

	for (int i = 0; i < f_num; i++)
		printf("%-15s", f_value[i]);
	puts(" ");
	puts(" ");

	return 0;
}

int main()
{
	sqlite3 *db = NULL;

	if (0 != sqlite3_open("./my.db", &db))
	{
		fprintf(stderr, "sqlite3_open: %s\n", sqlite3_errmsg(db));
		return -1;
	}
	
	printf("open database successfully.\n");


	char *errmsg = NULL;
#if 0
	if (0 != sqlite3_exec(db, "insert into stu values('Jann', 150, 188)", NULL, NULL, &errmsg))
		fprintf(stderr, "sqlite3_exec: %s\n", errmsg);
#else
	if (0 != sqlite3_exec(db, "select name, high from stu", callback, "hello", &errmsg))
		fprintf(stderr, "sqlite3_exec: %s\n", errmsg);
#endif 

	sqlite3_close(db);
	return 0;
}
