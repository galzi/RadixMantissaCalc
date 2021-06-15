#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Exercise 1
char* decToBin(int num) {
    int remain = num, location, index = 0, tmp;

    if (num == 0) { // Edge case: log(0) is invalid
        return "0";
    }

    char *s = (char *)malloc(((int)floor(log2(remain)) + 1 + 1) * sizeof(char)); // last '1' is for null char
    location = (int)floor(log2(num));

    while (remain > 0) {
        s[index++] = '1';
        remain -= pow(2, location);

        if (remain != 0) { // avoid log2(0)
            tmp = (int)floor(log2(remain)) + 1;
            while (location > tmp) {
                location--;
                s[index++] = '0';
            }

            location = (int)floor(log2(remain));
        }
    }
    s[index] = '\0';
    return s;
}

char* binToDec(char* num) { // int
    int location = strlen(num) - 1, i, sum = 0;
    char *s;

    if (strcmp(num, "0") == 0) { // Edge case: log(0) is invalid
        return "0";
    }

    for (i = 0; i < strlen(num) - 1; i++) {
        sum += (num[i] - '0') * pow(2, location--);
    }

    s = (char *)malloc(((int)floor(log10(sum)) + 1 + 1) * sizeof(char));
    s[(int)floor(log10(sum)) + 1] = '\0'; // null char

    for (i = (int)floor(log10(sum)); sum != 0; i--) { /* i >= 0 */
        s[i] = sum % 10 + '0';
        sum /= 10;
    }
    return s;
}

char* binToHex(char* num) {
    int i, j, m = 4 * (int)ceil((float)strlen(num) / 4);
    char *s = (char *)malloc(((int)ceil((float)strlen(num) / 4) + 1) * sizeof(char)), tmp[5], *s1 = NULL;

    s[(int)ceil((float)strlen(num) / 4)] = '\0';

    s1 = (char *)malloc((4 * (int)ceil((float)strlen(num) / 4) + 1) * sizeof(char)); // (char *) malloc(strlen(str1) + strlen(str2) + 1));
    s1[0] = '\0';

    for (i = strlen(num); m - i > 0; i++) {
        strcat(s1, "0");
    }
    strcat(s1, num);

    for (i = 0; i < strlen(s1) / 4; i++) {
        strncpy(tmp, s1 + i * 4, 4);
        tmp[4] = '\0';

        if (strcmp(tmp, "0000") == 0) {
            s[i] = '0';
        }
        else if (strcmp(tmp, "0001") == 0) {
            s[i] = '1';
        }
        else if (strcmp(tmp, "0010") == 0) {
            s[i] = '2';
        }
        else if (strcmp(tmp, "0011") == 0) {
            s[i] = '3';
        }
        else if (strcmp(tmp, "0100") == 0) {
            s[i] = '4';
        }
        else if (strcmp(tmp, "0101") == 0) {
            s[i] = '5';
        }
        else if (strcmp(tmp, "0110") == 0) {
            s[i] = '6';
        }
        else if (strcmp(tmp, "0111") == 0) {
            s[i] = '7';
        }
        else if (strcmp(tmp, "1000") == 0) {
            s[i] = '8';
        }
        else if (strcmp(tmp, "1001") == 0) {
            s[i] = '9';
        }
        else if (strcmp(tmp, "1010") == 0) {
            s[i] = 'A';
        }
        else if (strcmp(tmp, "1011") == 0) {
            s[i] = 'B';
        }
        else if (strcmp(tmp, "1100") == 0) {
            s[i] = 'C';
        }
        else if (strcmp(tmp, "1101") == 0) {
            s[i] = 'D';
        }
        else if (strcmp(tmp, "1110") == 0) {
            s[i] = 'E';
        }
        else if (strcmp(tmp, "1111") == 0) {
            s[i] = 'F';
        }
    }

    free(s1);
    return s;
}

// Exercise 2
char* toBin(double num, int precision, int *dotOffset, int state) {
    double remain = num;
    int location, index, tmp, i;
    char *s;

    s = (char *)malloc((precision + 1) * sizeof(char));

    for (i = 0; i < precision; i++) {
        s[i] = '0';
    }
    s[precision] = '\0';


    if (num == 0) { // Edge case: log(0) is invalid
        *dotOffset = 0;
        return s;
    }

    *dotOffset = location = (int)floor(log2(num));
    index = !state ? 0 : (int)strlen(s) - (int)floor(log2(num)) - 1;

    while ((remain > 0) && (index < (int)strlen(s))) {
        s[index++] = '1';
        remain -= pow(2, location);

        if (remain != 0) { // avoid log2(0)
            tmp = (int)floor(log2(remain)) + 1;
            while (location > tmp) {
                location--;
                index++;
            }

            location = (int)floor(log2(remain));
        }
    }

    if ((!state) && (location - (int)floor(log2(num)) == -1 * precision)) { // round up in case one digit after the last which can be saved is 1
        for (i = (int)strlen(s) - 1; (s[i] == '1') && (i >= 0); s[i--] = '0'); // precision - 1;
        s[i] = '1';
    }
    return s;
}

char* convert(char* num, int mantissaSize, int expSize, int expAdd) {
    char *sign = NULL, *exp = NULL, *mantissa = NULL, *str = NULL;
    int sum = 0, dotOffset = 0, i, j, k, *e = NULL;

    sign = (char *)malloc(2 * sizeof(char)); // for joining strings at the end
    sign[1] = '\0';

    // Sign
    if (num[0] == '-') {
        sign[0] = '1';
    }
    else {
        sign[0] = '0';
    }

    if (strcmp(num, "0") == 0) { // what about 0...0?
        mantissa = (char *)malloc((mantissaSize + 1) * sizeof(char));
        exp = (char *)malloc((expSize + 1) * sizeof(char));

        for (i = 0; i < mantissaSize; mantissa[i] = '0', i++);
        for (i = 0; i < expSize; exp[i] = '0', i++);
    }
    else if ((strcmp(num, "inf") == 0) || (strcmp(num, "-inf") == 0)) {
        mantissa = (char *)malloc((mantissaSize + 1) * sizeof(char));
        exp = (char *)malloc((expSize + 1) * sizeof(char));

        for (i = 0; i < mantissaSize; mantissa[i] = '1', i++);
        for (i = 0; i < expSize; exp[i] = '1', i++);
    }
    else {
        // Mantissa
        mantissa = toBin(fabs(atof(num)), mantissaSize + 1, &dotOffset, 0);
        for (i = 0; i < (int)strlen(mantissa); sum += mantissa[i] == '1' ? 1 : 0, i++); // sum exponent values from binary representation
        e = (int *)malloc(sum * sizeof(int));

        for (i = 0, j = dotOffset, k = 0; i < (int)strlen(mantissa); i++, j--) {
            if (mantissa[i] == '1') {
                e[k++] = j;
            }
        }

        for (i = 0; i < sum; e[i] -= dotOffset, i++);
        free(e);

        // Exponent
        exp = toBin(dotOffset + expAdd, expSize, &k, 1); // dotOffset is unnecessary here
        str = (char *)malloc((13 + mantissaSize + expSize) * sizeof(char));
        str[0] = '\0';
    }

    strcat(str, "s: ");
    strcat(str, sign);
    strcat(str, "\n");

    strcat(str, "e: ");
    strcat(str, exp);
    strcat(str, "\n");

    strcat(str, "m: ");
    strcat(str, mantissa + 1);
    strcat(str, "\0");

    free(sign);
    free(mantissa);
    free(exp);

    return str;
}

// Exercise 3
double calcAbsoluteError(double real, double approximate) {
    return fabs(real - approximate);
}

double calcRelativeError(double real, double approximate) {
    return fabs((real - approximate) / real);
}

void printDelta(FILE *output, double x, double x0) {
    fprintf(output, "absolute delta: %0.6lf\nrelative delta : %0.6lf\n\n", calcAbsoluteError(x, x0), calcRelativeError(x, x0));
}

// Main
int main() {
    FILE *input = fopen("input.txt", "r"), *output = fopen("output.txt", "w");
    char buff[255], *str;
    int i, j, offset;
    double x0;

    if (input == NULL) {
        printf("input.txt file doesn't exist.");
    }

    while (fgets(buff, 255, input) != NULL) {
        for (i = 0; buff[i] != ':'; i++);
        buff[i] = '\0';

        for (str = buff + i + 1; str == ' '; str++);
        offset = str - (buff + i) + 1;

        for (j = 0; *(buff + i + offset + j) != '\n' && *(buff + i + offset + j) != '\0'; j++);
        *(buff + i + offset + j) = '\0';

        // Exercise 1
        if (strcmp(buff, "dec to bin") == 0) {
            str = decToBin(atoi(buff + i + offset));
            fputs("0b", output);
        }
        else if (strcmp(buff, "bin to dec") == 0) {
            str = binToDec(buff + i + offset);

        }
        else if (strcmp(buff, "dec to hex") == 0) {
            str = binToHex(decToBin(atoi(buff + i + offset)));
            fputs("0x", output);
        } // Exercise 2
        else if (strcmp(buff, "to float") == 0) {
            str = convert(buff + i + offset, 23, 8, 127);
        }
        else if (strcmp(buff, "to double") == 0) {
            str = convert(buff + i + offset, 52, 11, 1023);
        }

        fputs(str, output);
        fputs("\n\n", output);
        free(str);
    }

    // Exercise 3
    printDelta(output, sin(0.5), 0.4794);

    for (i = 0, j = 1, x0 = 0; i <= 20; x0 += 1.0 / j, j *= i + 1, i++);
    printDelta(output, M_E, x0);

    for (i = 1, x0 = 0; i <= 20; x0 += (pow(-1, i + 1)) / (2 * i - 1), i++);
    x0 *= 4;
    printDelta(output, M_PI, x0);

    fclose(input);
    fclose(output);

    return 0;
}
