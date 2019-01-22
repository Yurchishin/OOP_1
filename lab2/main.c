#include <stdio.h>
#include <stdlib.h>
#include "scaninfo.h"

const char * csv_file = "/home/yurass/C/OOP/lab2/scanners.csv";

const char * db_file = "/home/yurass/C/OOP/lab2/scanners.db";

int main() {
    printf("\n\tDatabase : '%s'\n", db_file);
    create_db(csv_file, db_file);
    make_index(db_file, "structure");
    printf("\n\tDatabase has been written in Scanner.txt\n");
    print_db(db_file);
    printf("\n\t reindex\n");
    reindex(db_file);
    printf("\n\tAdd SCAN_INFO '%s'\n", "QW;QWERTY;1234;999;422;99");
    add_scanner(db_file, "QW;QWERTY;1234;999;422;998");
    printf("\n\tDatabase has been written in Scanner.txt\n");
    print_db(db_file);
    printf("\n\tDelete SCAN_INFO with id = %d\n", 5);
    del_scanner(db_file, 5);
    printf("\n\tDatabase has been written in Scanner.txt\n");
    print_db(db_file);
    RECORD_SET * rs = select_scan_info(db_file, "manufactor", "ASUS");
    printf("\n\tPrint RecordSet field = '%s', value = '%s':\n", "manufactor", "ASUS");
    print_rec_set(rs);
    free(rs->recs);
    free(rs);
    rs = get_recs_by_index(db_file, "manufacturer");
    printf("\n\tPrint RecordSet field = '%s':\n", "manufactor");
    print_rec_set(rs);
    free(rs->recs);
    free(rs);
    rs = get_recs_by_index(db_file, "model");
    printf("\n\tPrint RecordSet field = '%s':\n", "model");
    print_rec_set(rs);
    free(rs->recs);
    free(rs);
    printf("\nPress any key to continue...");
    getchar();
}