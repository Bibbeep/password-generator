#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

struct Config {
    int len;
    bool isUpper, isLower, isNumeric, isSymbol;
    char* password;
} user;

void showBanner() {
    printf("+------------------------------+\n");
    printf("|      PASSWORD GENERATOR      |\n");
    printf("+------------------------------+\n");
}

/**
 * Generates uppercase alphabet character based on ASCII code
 * @param {int} activator Decides whether to activate the function to return the result (0/1)
 * @returns {int} the ASCII code between 65 and 90 or 0 if not activated
 */
int generateUpper(int activator) {
    if (!activator) {
        return 0;
    }

    return rand() % (90 - 65 + 1) + 65;
}

/**
 * Generates lowercase alphabet character based on ASCII code
 * @param {int} activator Decides whether to activate the function to return the result (0/1)
 * @returns {int} the ASCII code between 97 and 122 or 0 if not activated
 */
int generateLower(int activator) {
    if (!activator) {
        return 0;
    }
    
    return rand() % (122 - 97 + 1) + 97;
}

/**
 * Generates numeric character based on ASCII code
 * @param {int} activator Decides whether to activate the function to return the result (0/1)
 * @returns {int} the ASCII code between 48 and 57 or 0 if not activated
 */
int generateNumber(int activator) {
    if (!activator) {
        return 0;
    }

    return rand() % (57 - 48 + 1) + 48;
}

/**
 * Generates symbol character based on ASCII code
 * @param {int} activator Decides whether to activate the function to return the result (0/1)
 * @returns {int} the ASCII code of 33 - 47, 58 - 64, 91 - 96, 123 - 126, or 0 if not activated
 */
int generateSymbol(int activator) {
    if (!activator) {
        return 0;
    }
    
    int random = rand() % 4;
    switch (random) {
        case 0: return rand() % (47 - 33 + 1) + 33;
        case 1: return rand() % (64 - 58 + 1) + 58;
        case 2: return rand() % (96 - 91 + 1) + 91;
        case 3: return rand() % (126 - 123 + 1) + 123;
    }
    return 0;
}

/**
 * Randomizes a integer of ASCII value between enabled configuration
 * @param {int} upp Decides whether to enable the uppercase alphabets in the result
 * @param {int} low Decides whether to enable the lowercase alphabets in the result
 * @param {int} num Decides whether to enable the numerics in the result
 * @param {int} sym Decides whether to enable the symbols in the result
 * @returns {int} the ASCII code between the enabled configuration
 */
int generateRandomNumber(int upp, int low, int num, int sym) {
    int arr[4] = {
        generateUpper(upp),
        generateLower(low),
        generateNumber(num),
        generateSymbol(sym)
    };

    int sum = upp + low + num + sym;
    int* arrResult = (int*) malloc(sum * sizeof(int));
    int j = 0;

    for (int i = 0; i < 4; i++) {
        if (arr[i] != 0) {
            arrResult[j] = arr[i];
            j++;
        }
    }

    int k = rand() % sum;
    int result = arrResult[k];
    free(arrResult);

    return result;
}

/**
 * Generates a string of password
 * @param {int} upp Decides whether to enable the uppercase alphabets in the result
 * @param {int} low Decides whether to enable the lowercase alphabets in the result
 * @param {int} num Decides whether to enable the numerics in the result
 * @param {int} sym Decides whether to enable the symbols in the result
 * @param {int} len The length of the returned string of password
 * @returns {int} string of password
 */
char* generatePassword(int upp, int low, int num, int sym, int len) {
    char* pw = (char*) malloc((len+1) * sizeof(char));
    for (int i = 0; i < len+1; i++) {
        pw[i] = 0;
        pw[i]+=generateRandomNumber(upp, low, num, sym);
    }
    pw[len] = '\0';

    return pw;
}

int main(int argc, char **argv) {
    srand(time(NULL));
    int status = -1;
    int menu = 0;
    user.len = 12;
    user.isUpper = false;
    user.isLower = true;
    user.isNumeric = false;
    user.isSymbol = false;

    do {
        system("cls");
        showBanner();
        switch (menu) {
            case 0:
                printf("Password Length: ");
                scanf("%d", &user.len);
                menu = 1;
                break;

            case 1:
                int ans;
                printf("Password configuration [0/1]\n");
                printf("Uppercase: ");
                scanf("%d", &ans);
                user.isUpper = ans;
                
                printf("Lowercase: ");
                scanf("%d", &ans);
                user.isLower = ans;

                printf("Numbers: ");
                scanf("%d", &ans);
                user.isNumeric = ans;

                printf("Symbols: ");
                scanf("%d", &ans);
                user.isSymbol = ans;

                menu = 2;
                break;

            case 2:
                int ans2;

                user.password = generatePassword(user.isUpper, user.isLower, user.isNumeric, user.isSymbol, user.len);
                printf("Your password: %s\n\n0. Exit Program\n1. Regenerate\n2. Change Length\n3. Change Configuration\n>", user.password);
                scanf("%d", &ans2);

                switch (ans2) {
                    case 0:
                        menu = -1;
                        break;

                    case 1:
                        break;

                    case 2:
                        menu = 0;
                        break;
                    
                    case 3:
                        menu = 1;
                        break;
                    default:
                        break;
                }
                break;

            default:
                printf("Press any key to exit program...");
                printf("%c", getch());
                system("cls");
                status = 0;
                break;
        }
    } while (status != 0);

    return 0;
}