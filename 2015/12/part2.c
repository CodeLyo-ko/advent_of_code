#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"
#include "json.c"

static int process_value(json_value* value, int depth, int* is_red);
static int process_object(json_value* value, int depth)
{
    int total = 0;
    int has_red = 0;
    int is_red = 0;

    int length, x;
    if (value == NULL) {
        return 0;
    }
    length = value->u.object.length;
    for (x = 0; x < length; x++) {
        total += process_value(value->u.object.values[x].value, depth+1, &is_red);

        if (is_red) {
            has_red = 1;
        }
    }

    printf("%d\n", total);
    return has_red?0:total;
}

static int process_array(json_value* value, int depth)
{
    int temp;
    int total = 0;
    int length, x;
    if (value == NULL) {
        return 0;
    }
    length = value->u.array.length;
    for (x = 0; x < length; x++) {
        total += process_value(value->u.array.values[x], depth, &temp);
    }
    return total;
}

static int process_value(json_value* value, int depth, int* is_red)
{
    if (value == NULL) {
            return 0;
    }
    switch (value->type) {
            case json_none:
                    printf("none\n");
                    break;
            case json_null:
                    printf("null\n");
                    break;
            case json_object:
                    return process_object(value, depth+1);
                    break;
            case json_array:
                    return process_array(value, depth+1);
                    break;
            case json_integer:
                    return value->u.integer;
                    break;
            case json_double:
                    return value->u.dbl;
                    break;
            case json_string:
                    if (!strcmp(value->u.string.ptr, "red")) {
                        *is_red = 1;
                    }
                    break;
            case json_boolean:
                    break;
    }
    return 0;
}

int main() {
    char* input = malloc(45000 * sizeof(char));
    fgets(input, 45000, stdin);

    json_char* json = (json_char*)input;
    json_value* value = json_parse(json, strlen(input));

    if (value == NULL) {
        printf("feur\n");
        exit(0);
    }

    int temp;

    int total = process_value(value, 0, &temp);

    printf("%d\n", total);

    return 0;
}
