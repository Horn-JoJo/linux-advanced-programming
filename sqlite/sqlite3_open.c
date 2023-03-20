#include <stdio.h>
#include <sqlite3.h>

int main()
{
	sqlite3 *db = NULL;

	if (0 != sqlite3_open("./my.db", &db))
	{
		fprintf(stderr, "sqlite3_open fail : %s\n", sqlite3_errmsg(db));
		return -1;
	}
	
	printf("open database successfully.\n");
	sqlite3_close(db);

	return 0;
}
