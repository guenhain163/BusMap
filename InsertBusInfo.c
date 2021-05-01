#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main()
{
    int price;
    char busCode[10], runTime[100], distance[100], firstStation[100], lastStation[100];

    sqlite3 *db;
    int rc;
    char *sql, *zErrMsg = 0;

    /* Open file */
    FILE *f = fopen("BusInfo.txt", "r");
    if(f == NULL)
    {
        printf("Error File!");
    }

    /* Open database */
    rc = sqlite3_open("bus.db", &db);
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Read file data */
    while (!feof(f))
    {
        fscanf(f, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d\n", busCode, runTime, firstStation, lastStation, distance, &price);
        /* Create SQL statement */
        asprintf(&sql, "INSERT INTO BusInfo(Buscode, RunTime, FirstStation, LastStation, Frequency, Fare)" \
                "VALUES('%s', '%s', '%s', '%s', '%s', %d);", busCode, runTime, firstStation, lastStation, distance, price);
        rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
        if(rc != SQLITE_OK){
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        else
        {
            fprintf(stdout, "Records created successfully\n");
        }
    
    }

    fclose(f);
    sqlite3_close(db);

    return 0;
}

