#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 100

void oct_to_bin(char *oct, char *out) {
    int len = strlen(oct);
    int out_index = 0;
    for (int i = 0; i < len; i++) {
        int digit = oct[i] - '0';
        for (int j = 2; j >= 0; j--) {
            out[out_index++] = ((digit >> j) & 1) + '0';
        }
    }
    out[out_index] = '\0';
}

void oct_to_hex(char *oct, char *out) {
    char bin[MAX] = "";
    oct_to_bin(oct, bin);

    int len = strlen(bin);
    int padding = (4 - (len % 4)) % 4;

    char padded_bin[MAX] = "";
    memset(padded_bin, '0', padding);
    padded_bin[padding] = '\0';
    strcat(padded_bin, bin);

    int hex_len = strlen(padded_bin) / 4;
    int out_index = 0;

    for (int i = 0; i < hex_len; i++) {
        int val = 0;
        for (int j = 0; j < 4; j++) {
            val = val * 2 + (padded_bin[i * 4 + j] - '0');
        }
        out[out_index++] = "0123456789ABCDEF"[val];
    }
    out[out_index] = '\0';
}

void hex_to_bin(char *hex, char *out) {
    int len = strlen(hex);
    int out_index = 0;
    for (int i = 0; i < len; i++) {
        char c = hex[i];
        int val;
        if (c >= '0' && c <= '9') val = c - '0';
        else if (c >= 'A' && c <= 'F') val = c - 'A' + 10;
        else if (c >= 'a' && c <= 'f') val = c - 'a' + 10;
        else continue;
        for (int j = 3; j >= 0; j--) {
            out[out_index++] = ((val >> j) & 1) + '0';
        }
    }
    out[out_index] = '\0';
}

void to_sign_magnitude(int n, char *out) {
    unsigned int mask = 1 << 30;
    if (n < 0) {
        out[0] = '1';
        n = -n;
    } else {
        out[0] = '0';
    }
    for (int i = 1; i < 32; i++) {
        out[i] = ((n & mask) ? '1' : '0');
        mask >>= 1;
    }
    out[32] = '\0';
}

void to_ones_complement(int n, char *out) {
    unsigned int un;
    if (n >= 0) {
        un = n;
    } else {
        un = ~(-n);
    }
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((un >> i) & 1) + '0';
    }
    out[32] = '\0';
}

void to_twos_complement(int n, char *out) {
    unsigned int un = (unsigned int)n;
    for (int i = 31; i >= 0; i--) {
        out[31 - i] = ((un >> i) & 1) + '0';
    }
    out[32] = '\0';
}
