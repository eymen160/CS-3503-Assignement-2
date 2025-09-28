#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert.c"

void run_test(const char* func, char* input1, char* input2, char* expected, FILE* fout) {
    char output[100] = "";

    if (strcmp(func, "oct_to_bin") == 0) {
        oct_to_bin(input1, output);
    } else if (strcmp(func, "oct_to_hex") == 0) {
        oct_to_hex(input1, output);
    } else if (strcmp(func, "hex_to_bin") == 0) {
        hex_to_bin(input1, output);
    } else if (strcmp(func, "to_sign_magnitude") == 0) {
        int n = atoi(input1);
        to_sign_magnitude(n, output);
    } else if (strcmp(func, "to_ones_complement") == 0) {
        int n = atoi(input1);
        to_ones_complement(n, output);
    } else if (strcmp(func, "to_twos_complement") == 0) {
        int n = atoi(input1);
        to_twos_complement(n, output);
    } else {
        fprintf(fout, "Unknown function: %s\n", func);
        return;
    }

    fprintf(fout, "%s %s => %s [%s]\n", func, input1, output, strcmp(output, expected) == 0 ? "PASS" : "FAIL");
}

int main() {
    FILE* fin = fopen("A2_tests.txt", "r");
    FILE* fout = fopen("output.txt", "w");

    if (!fin || !fout) {
        printf("File error.\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), fin)) {
        if (line[0] == '#' || strlen(line) < 2) continue;

        char func[50], input1[50], input2[50] = "", expected[100];
        int fields = sscanf(line, "%s %s %s %s", func, input1, input2, expected);

        if (fields == 3)
            run_test(func, input1, NULL, input2, fout);
        else if (fields == 4)
            run_test(func, input1, input2, expected, fout);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
