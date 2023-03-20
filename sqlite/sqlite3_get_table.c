#include <stdio.h>
#include <sqlite3.h>

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
	char **resultp = NULL;
	int nrow, ncolumn;

	if (0 != sqlite3_get_table(db, "select * from stu", &resultp, &nrow, &ncolumn, &errmsg))
		fprintf(stderr, "sqlite3_get_table: %s\n", errmsg);	
#if 0
	int count = 0;
	for (int i = 0; i < nrow + 1; i++)
	{
		for (int j = 0; j < ncolumn; j++)
			printf("%-15s", resultp[count++]);
		puts("");
	}
#else
	for (int i = 0; i < nrow + 1; i++)
	{
		for (int j = 0; j < ncolumn; j++)
			printf("%-15s", resultp[i * ncolumn + j]);
		puts("");
	}
#endif

	sqlite3_close(db);
	return 0;
}
