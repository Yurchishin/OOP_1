#include <stdlib.h>
#include "scaninfo.h"

//function for printing SCAN_INFO
void print_scan_info(SCAN_INFO * scanner) {
    printf("\nManufactor: %s\n", scanner->manufactor);
    printf("Model: %s\n", scanner->model);
    printf("Year: %d\n", scanner->year);
    printf("Price: %.2f\n", scanner->price);
    printf("x_size: %d\n", scanner->x_size);
    printf("y_size: %d\n", scanner->y_size);
    printf("id: %d\n", scanner->id);
}

//function for getting size of SCAN_INFO array,(count of '\n' in csv_file)
int get_size_of_sca_info_array_from_csv_file(const char *path) {
    int i = 0;
    FILE * file = fopen(path, "rt");
    while (!feof(file)) {
        char buffer[BUFF_SIZE];
        fscanf(file, "%s", &buffer);
        i++;
    }
    fclose(file);
    return i;
}

//function that compare 2 strings
int compare_strings(char *str1, char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return 0;
    }
    int size_of_str1 = strlen(str1);
    int size_of_str2 = strlen(str2);
    if (size_of_str1 != size_of_str2) return 0;
    else {
        for (int i = 0; i < size_of_str1; i++) {
            if (str1[i] != str2[i]) {
                return 0;
            }
        }
    }
    return 1;
}

//function for compare 2 SCAN_INFO objects
int compare_scan_info(SCAN_INFO *a, SCAN_INFO *b) {
    if (compare_strings(a->manufactor, b->manufactor) && compare_strings(a->model, b->model) &&
        a->price == b->price &&  a->x_size == b->x_size && a->y_size == b->y_size &&
        a->year == b->year)  return 1;
    return 0;
}

//function for reset file
void reset_file(const char * filename) {
    FILE * file = fopen(filename, "wb");
    fclose(file);
}

//function for get object fields from str
void get_info_from_str(const char *str, int number, char **dest) {
    int start = 0;
    int string_size = strlen(str);
    int index = 0;
    int first_entry_index = 0;
    int size_of_word = 0;
    int first = 1;
    while (index < string_size) {
        if (str[index] == ';') {
            start++;
            index++;
        }
        if (start == number) {
            if (first) {
                first_entry_index = index;
                first = 0;
            }
            size_of_word++;
        } else {
            if (start > number) {
                break;
            }
        }
        index++;
    }
    *dest = (char *)malloc(sizeof(char) * (size_of_word + 1));
    for (int i = first_entry_index; i < first_entry_index + size_of_word; i++) {
        ( *dest )[i - first_entry_index] = str[i];
    }
    (*dest)[size_of_word] = '\0';
}

//function for setting words in object fields
void get_scan_info_from_str(SCAN_INFO *scanner, const char *buff, int *id) {
    get_info_from_str(buff, 0, &scanner[*id].manufactor);
    get_info_from_str(buff, 1, &scanner[*id].model);
    char * buffer;
    get_info_from_str(buff, 2, &buffer);
    scanner[*id].year = atoi(buffer);
    get_info_from_str(buff, 3, &buffer);
    scanner[*id].price = (float)atof(buffer);
    get_info_from_str(buff, 4, &buffer);
    scanner[*id].x_size = atoi(buffer);
    get_info_from_str(buff, 5, &buffer);
    scanner[*id].y_size = atoi(buffer);
    scanner[*id].id = *id;
    if (*id != 0 ) {
        for (int i = 0; i < *id; i++) {
            if (compare_scan_info(&scanner[*id], &scanner[i])) {
                *id = *id - 1;
                break;
            }
        }
    }
    *id = *id + 1;
}

//function that inserting SCAN_INFO
void insertScanner(SCAN_INFO * scanners, const char * scanner_str, int id, int * size) {
    get_info_from_str(scanner_str, 0, &scanners[*size].manufactor);
    get_info_from_str(scanner_str, 1, &scanners[*size].model);
    char * buffer;
    get_info_from_str(scanner_str, 2, &buffer);
    scanners[*size].year = atoi(buffer);
    get_info_from_str(scanner_str, 3, &buffer);
    scanners[*size].price = (float)atof(buffer);
    get_info_from_str(scanner_str, 4, &buffer);
    scanners[*size].x_size = atoi(buffer);
    get_info_from_str(scanner_str, 5, &buffer);
    scanners[*size].y_size = atoi(buffer);
    scanners[*size].id = id;
    for (int i = 0; i < *size; i++) {
        if (compare_scan_info(&scanners[*size], &scanners[i])) {
            *size -= 1;
            break;
        }
    }
    *size += 1;
}

void create_db(const char * csv_file, const char * db_file) {
    reset_file(db_file);
    FILE * csv_file_ptr = fopen(csv_file, "rt");
    char buff[BUFF_SIZE];
    int size = get_size_of_sca_info_array_from_csv_file(csv_file);
    int currentIndex = 0;
    SCAN_INFO * scanners = (SCAN_INFO*)malloc(sizeof(SCAN_INFO) * size);
    while (!feof(csv_file_ptr)) {
        fscanf(csv_file_ptr, "%s", &buff);
        get_scan_info_from_str(scanners, buff, &currentIndex);
    }
    FILE * db_file_ptr = fopen(db_file, "ab");
    fwrite(&currentIndex, sizeof(int), 1, db_file_ptr);
    for (int i = 0; i < currentIndex; i++) {
        fwrite(&scanners[i], sizeof(SCAN_INFO), 1, db_file_ptr);
    }
    free(scanners);
    fclose(csv_file_ptr);
    fclose(db_file_ptr);
}

//function for swapping 2 SCAN_INFO
void swap_scan_info(SCAN_INFO * scan_info_1, SCAN_INFO * scan_info_2) {
    SCAN_INFO buff = * scan_info_1;
    *scan_info_1 = * scan_info_2;
    *scan_info_1 = buff;
}

//function for sorting array of SCAN_INFO by field
void sort(SCAN_INFO * scanners, char * field_name, int size) {
    if (compare_strings(field_name, "manufactor")) {
        for (int i = 0; i < size; i++) {
            int imin = i;
            for (int j = i + 1; j < size; j++) {
                int size1 = strlen(scanners[i].manufactor);
                int size2 = strlen(scanners[j].manufactor);
                for (int k = 0; k < (size1 < size2 ? size1 : size2); k++) {
                    if (scanners[imin].manufactor[k] > scanners[j].manufactor[k]) {
                        imin = j;
                    }
                    if (scanners[imin].manufactor[k] == scanners[j].manufactor[k]) {
                        continue;
                    }
                    break;
                }
            }
            if (imin != i) {
                swap_scan_info(&scanners[i], &scanners[imin]);
            }
        }
    }
    if (compare_strings(field_name, "model")) {
        for (int i = 0; i < size; i++) {
            int imin = i;
            for (int j = i + 1; j < size; j++) {
                int size1 = strlen(scanners[i].model);
                int size2 = strlen(scanners[j].model);
                for (int k = 0; k < (size1 < size2 ? size1 : size2); k++) {
                    if (scanners[imin].model[k] > scanners[j].model[k]) {
                        imin = j;
                    }
                    if (scanners[imin].model[k] == scanners[j].model[k]) {
                        continue;
                    }
                    break;
                }
            }
            if (imin != i) {
                swap_scan_info(&scanners[i], &scanners[imin]);
            }
        }
    }
    if (compare_strings(field_name, "year")) {
        for (int i = 0; i < size; i++) {
            int imin = i;
            for (int j = i + 1; j < size; j++) {
                if (scanners[imin].year > scanners[j].year) {
                    imin = j;
                    break;
                }
            }
            if (imin != i) {
                swap_scan_info(&scanners[i], &scanners[imin]);
            }
        }
    }
    if (compare_strings(field_name, "price")) {
        for (int i = 0; i < size; i++) {
            int imin = i;
            for (int j = i + 1; j < size; j++) {
                if (scanners[imin].price > scanners[j].price) {
                    imin = j;
                    break;
                }
            }
            if (imin != i) {
                swap_scan_info(&scanners[i], &scanners[imin]);
            }
        }
    }
    if (compare_strings(field_name, "id")) {
        for (int i = 0; i < size; i++) {
            int imin = i;
            for (int j = i + 1; j < size; j++) {
                if (scanners[imin].id > scanners[j].id) {
                    imin = j;
                    break;
                }
            }
            if (imin != i) {
                swap_scan_info(&scanners[i], &scanners[imin]);
            }
        }
    }
    if (compare_strings(field_name, "x_size")) {
        for (int i = 0; i < size; i++) {
            int imin = i;
            for (int j = i + 1; j < size; j++) {
                if (scanners[imin].x_size > scanners[j].x_size) {
                    imin = j;
                    break;
                }
            }
            if (imin != i) {
                swap_scan_info(&scanners[i], &scanners[imin]);
            }
        }
    }
    if (compare_strings(field_name, "y_size")) {
        for (int i = 0; i < size; i++) {
            int imin = i;
            for (int j = i + 1; j < size; j++) {
                if (scanners[imin].y_size > scanners[j].y_size) {
                    imin = j;
                    break;
                }
            }
            if (imin != i) {
                swap_scan_info(&scanners[i], &scanners[imin]);
            }
        }
    }
}

//function for getting idx file name
char * get_idx_file_name(const char * field) {
    if (compare_strings(field, "manufactor")) {
        return "/home/yurass/C/OOP/lab2/manufactor.idx";
    }
    if (compare_strings(field, "model")) {
        return "/home/yurass/C/OOP/lab2/model.idx";
    }
    if (compare_strings(field, "year")) {
        return "/home/yurass/C/OOP/lab2/year.idx";
    }
    if (compare_strings(field, "price")) {
        return "/home/yurass/C/OOP/lab2/price.idx";
    }
    if (compare_strings(field, "x_size")) {
        return "/home/yurass/C/OOP/lab2/x_size.idx";
    }
    if (compare_strings(field, "y_size")) {
        return "/home/yurass/C/OOP/lab2/y_size.idx";
    }
    if (compare_strings(field, "id")) {
        return "/home/yurass/C/OOP/lab2/id.idx";
    }
}

int make_index(const char * db_file, const char * field_name) {
    if (db_file == NULL || field_name == NULL) {
        return 0;
    }
    FILE * file = fopen(db_file, "rb");
    if (file == NULL) {
        return 0;
    }
    int size = 0;
    int currentIndex = 0;
    fread(&size, sizeof(int), 1, file);
    SCAN_INFO * scanners = (SCAN_INFO *)malloc(sizeof(SCAN_INFO) * size);
    while (!feof(file)) {
        fread(&scanners[currentIndex], sizeof(SCAN_INFO), 1, file);
        currentIndex++;
    }
    fclose(file);
    sort(scanners, field_name, size);
    char * file_name = get_idx_file_name(field_name);
    FILE * fileIDX = fopen(file_name, "wt");
    fclose(fileIDX);
    fileIDX = fopen(file_name, "at");
    if (fileIDX == NULL) {
        return 0;
    }
    for (int i = 0; i < size; i++) {
        fprintf(fileIDX, "%d ", scanners[i].id);
    }
    fclose(fileIDX);
    free(scanners);
    return 1;
}

void reindex(const char * db_file) {
    make_index(db_file, "manufactor");
    make_index(db_file, "model");
    make_index(db_file, "year");
    make_index(db_file, "price");
    make_index(db_file, "x_size");
    make_index(db_file, "y_size");
    make_index(db_file, "id");
}

void del_scanner(const char * db_file, int id) {
    int size = 0;
    int index_of_current_count = 0;
    int find = -1;
    FILE * db_file_ptr = fopen(db_file, "rb");
    fread(&size, sizeof(size), 1, db_file_ptr);
    SCAN_INFO * scanners = (SCAN_INFO *)malloc(sizeof(SCAN_INFO) * size);
    while (fread(&scanners[index_of_current_count], sizeof(SCAN_INFO), 1, db_file_ptr)) {
        index_of_current_count++;
    }
    fclose(db_file_ptr);
    for (int i = 0; i < size; i++) {
        if (scanners[i].id == id) {
            find = i;
            break;
        }
    }
    db_file_ptr = fopen(db_file, "wb");
    fclose(db_file_ptr);
    db_file_ptr = fopen(db_file, "ab");
    if (find != -1) {
        size--;
    }
    fwrite(&size, sizeof(size), 1, db_file_ptr);
    int idIndex = 0;
    for (int i = 0; i < index_of_current_count; i++) {
        if (i != find) {
            scanners[i].id = idIndex;
            fwrite(&(scanners[i]), sizeof(SCAN_INFO), 1, db_file_ptr);
            idIndex++;
        }
    }
    fclose(db_file_ptr);
    free(scanners);
    reindex(db_file);
}

void add_scanner(const char * db_file, const char * scan_info) {
    int size = 0;
    int index_of_current_count = 0;
    int min_id = 0;
    FILE * db_file_ptr = fopen(db_file, "rb");
    fread(&size, sizeof(size), 1, db_file_ptr);
    SCAN_INFO * scanners = (SCAN_INFO *)malloc(sizeof(SCAN_INFO) * (size + 1));
    while (fread(&scanners[index_of_current_count], sizeof(SCAN_INFO), 1, db_file_ptr)) {
        index_of_current_count++;
    }
    fclose(db_file_ptr);
    for (int i = 0; i < size; i++) {
        if (min_id == scanners[i].id) {
            min_id = scanners[i].id + 1;
        }
    }
    insertScanner(scanners, scan_info, min_id, &size);
    db_file_ptr = fopen(db_file, "wb");
    fclose(db_file_ptr);
    db_file_ptr = fopen(db_file, "ab");
    fwrite(&size, sizeof(size), 1, db_file_ptr);
    for (int i = 0; i < size; i++) fwrite(&(scanners[i]), sizeof(SCAN_INFO), 1, db_file_ptr);
    fclose(db_file_ptr);
    free(scanners);
    reindex(db_file);
}

void print_db(const char * db_file) {
    FILE * fileDataBase = fopen(db_file, "rb");
    int size = 0;
    int index_of_current_count = 0;
    fread(&size, sizeof(size), 1, fileDataBase);
    SCAN_INFO * scanners = (SCAN_INFO *)malloc(sizeof(SCAN_INFO) * size);
    while (fread(&scanners[index_of_current_count], sizeof(SCAN_INFO), 1, fileDataBase)) {
        index_of_current_count++;
    }
    fclose(fileDataBase);
    FILE * txt_file_ptr = fopen("/home/yurass/C/OOP/lab2/Scanners.txt", "wt");
    fclose(txt_file_ptr);
    txt_file_ptr = fopen("/home/yurass/C/OOP/lab2/Scanners.txt", "at");
    for (int i = 0; i < size; i++) {
        fprintf(txt_file_ptr, "%s;%s;%d;%lf;%d;%d;%d\n", scanners[i].manufactor, scanners[i].model, scanners[i].year,
                scanners[i].price, scanners[i].x_size, scanners[i].y_size, scanners[i].id);
    }
    fclose(txt_file_ptr);
}

RECORD_SET * select_scan_info(const char * db_file, const char * field, const char * value) {
    RECORD_SET * selected = (RECORD_SET *)malloc(sizeof(RECORD_SET));
    int size = 0;
    int index_of_current_count = 0;
    int real_size = 0;
    FILE * db_file_ptr = fopen(db_file, "rb");
    fread(&size, sizeof(int), 1, db_file_ptr);
    selected->recs = (SCAN_INFO *)malloc(sizeof(SCAN_INFO) * size);
    SCAN_INFO *scanners = (SCAN_INFO *)malloc(sizeof(SCAN_INFO) * size);
    while (fread(&(scanners[index_of_current_count]), sizeof(SCAN_INFO), 1, db_file_ptr)) {
        index_of_current_count++;
    }
    fclose(db_file_ptr);
    for (int i = 0; i < size; i++) {
        if (compare_strings("manufactor", field)) {
            if (compare_strings(scanners[i].manufactor, value)) {
                selected->recs[real_size] = scanners[i];
                real_size++;
            }
        }
        if (compare_strings("model", field)) {
            if (compare_strings(scanners[i].model, value)) {
                selected->recs[real_size] = scanners[i];
                real_size++;
            }
        }
        if (compare_strings("year", field)) {
            int yearValue = atoi(value);
            if (scanners[i].year == yearValue) {
                selected->recs[real_size] = scanners[i];
                real_size++;
            }
        }
        if (compare_strings("price", field)) {
            float priceValue = atof(value);
            if (scanners[i].price == priceValue) {
                selected->recs[real_size] = scanners[i];
                real_size++;
            }
        }
        if (compare_strings("x_size", field)) {
            int x_sizeValue = atoi(value);
            if (scanners[i].x_size == x_sizeValue) {
                selected->recs[real_size] = scanners[i];
                real_size++;
            }
        }
        if (compare_strings("y_size", field)) {
            int y_sizeValue = atoi(value);
            if (scanners[i].y_size == y_sizeValue) {
                selected->recs[real_size] = scanners[i];
                real_size++;
            }
        }
        if (compare_strings("id", field)) {
            int idValue = atoi(value);
            if (scanners[i].id == idValue) {
                selected->recs[real_size] = scanners[i];
                real_size++;
            }
        }
    }
    selected->rec_nmb = real_size;
    free(scanners);
    return selected;
}

void print_rec_set(RECORD_SET * rs) {
    int size = rs->rec_nmb;
    for (int i = 0; i < size; i++) {
        print_scan_info(&( rs->recs[i] ));
    }
}

//function for getting index id of array
int * get_index_id_of_array(const char *indx_field, int size) {
    int *indexs = (int *)malloc(sizeof(int) * size);
    int index = 0;
    FILE * fileIDX = fopen(get_idx_file_name(indx_field), "rt");
    for (int i = 0; i < size; i++) {
        fscanf(fileIDX, "%d", &(indexs[index]));
        index++;
    }
    return indexs;
}

RECORD_SET * get_recs_by_index(const char * db_file, char * indx_field) {
    int size_of_scan_info = 0;
    int current_index = 0;
    RECORD_SET *rs = (RECORD_SET *)malloc(sizeof(RECORD_SET));
    FILE * db_file_ptr = fopen(db_file, "rb");
    fread(&size_of_scan_info, sizeof(int), 1, db_file_ptr);
    int * idx_array = get_index_id_of_array(indx_field, size_of_scan_info);
    SCAN_INFO * scan_info_array_buufer = (SCAN_INFO *)malloc(size_of_scan_info * sizeof(SCAN_INFO));
    for (int i = 0; i < size_of_scan_info; i++) {
        fseek(db_file_ptr, sizeof(int) + idx_array[i] * sizeof(SCAN_INFO), SEEK_SET);
        fread(&(scan_info_array_buufer[current_index]), sizeof(SCAN_INFO), 1, db_file_ptr);
        current_index++;
    }
    fclose(db_file_ptr);
    rs->recs = scan_info_array_buufer;
    rs->rec_nmb = size_of_scan_info;
    free(idx_array);
    return rs;
}