#pragma once
#include <stdio.h>
#include <string.h>
#include <math.h>
//#pragma warning(disable : 4996)

#define BUFF_SIZE 64

typedef struct {
    int id;
    char * manufactor;
    int year;
    char * model;
    float price;
    int x_size;
    int y_size;
} SCAN_INFO;

typedef struct {
    int rec_nmb;
    SCAN_INFO *recs;
} RECORD_SET;

void create_db(const char * csv_file, const char * db_file);

int make_index(const char * db_file, const char * field_name);

void reindex(const char * db_file);

void del_scanner(const char * db_file, int id);

void add_scanner(const char * db_file, const char * scan_info);

void print_db(const char * db_file);

RECORD_SET * select_scan_info(const char * db_file, const char * field, const char * value);

void print_rec_set(RECORD_SET * rs);

RECORD_SET * get_recs_by_index(const char * db_file, char * indx_field);