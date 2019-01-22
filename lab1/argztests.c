/**********************************************************************

*file: argztests.c

*synopsis: just some tests for functions, that are defined in "argz.h".

* Just run "main"

*related files: none

*author: Rybak Yura

*written: 04/10/2018

*last modified: 09/10/2018

**********************************************************************/

#include "argz.h"

int main() {
    char *argz;
    size_t argz_len = 0;

    argz_create_sep("SHELL=/bin/bash:usr=monty:PWD=/bin/monty:LANG=en_US.UTF-8", ':', &argz, &argz_len);
    printf("Created argz:\n");
    argz_print(argz, argz_len);

    printf("\nargz_count test: %d\n", argz_count(argz, argz_len));

    printf("\nargz_add test: adding (argz_add):\n");
    argz_add(&argz, &argz_len, "(argz_add)");
    argz_print(argz, argz_len);

    printf("\nargz_count test: %d\n", argz_count(argz, argz_len));


    printf("\nargz_delete test: deleting '%s':\n", "usr=monty");
    argz_delete(&argz, &argz_len, "usr=monty");
    argz_print(argz, argz_len);

    printf("\nargz_count test: %d\n", argz_count(argz, argz_len));

    printf("\nargz_insert test: inserting '%s' before '%s':\n", "(argz_insert)", "LANG=en_US.UTF-8");
    argz_insert(&argz, &argz_len, "LANG=en_US.UTF-8", "(argz_insert)");
    argz_print(argz, argz_len);

    printf("\nargz_count test: %d\n", argz_count(argz, argz_len));


    printf("\nargz_next test:\n");
    char *entry = NULL;

    while (entry = argz_next(argz, argz_len, entry)) {
        printf("%s ", entry);
    }

    printf("\n\nargz_replace test: replacing '%s' to '%s':\n", "(argz_replace)", "PWD=/bin/monty");
    argz_replace(&argz, &argz_len, "PWD=/bin/monty", "(argz_replace)");
    argz_print(argz, argz_len);

    printf("\nargz_count  test: %d\n", argz_count(argz, argz_len));


    printf("\nTo exit press any key...");
    getchar();

    return 0;
}