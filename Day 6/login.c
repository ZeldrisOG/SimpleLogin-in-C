#include <stdio.h>
#include <string.h>

// This is our secret key. Keep it consistent!
#define KEY 'X' 

void encrypt_decrypt(char *data) {
    for (int i = 0; i < strlen(data); i++) {
        data[i] = data[i] ^ KEY; // Flip bits using XOR
    }
}

int main() {
char inputUser[50], inputPass[50];
    char savedUser[50], savedPass[50];
    FILE *fptr;

printf("Username: ");
    scanf("%49s", inputUser);
    printf("Password: ");
    scanf("%49s", inputPass);

    // 1. Check for the Override command '*'
    if (inputUser[0] == '*' && inputPass[0] == '*') {
        // Remove the '*' from the strings before saving (shift the pointer by 1)
        char *finalUser = inputUser + 1;
        char *finalPass = inputPass + 1;

        encrypt_decrypt(finalUser); // Encrypt the username
        encrypt_decrypt(finalPass); // Encrypt the password


        fptr = fopen("C:\\Windows\\Temp\\login.txt", "w");

if (fptr == NULL) {
            printf("Error saving credentials.\n");
            return 1;
        }
        fprintf(fptr, "%s %s", finalUser, finalPass);
        fclose(fptr);
        printf("Credentials updated successfully!\n");
    } 
    else {
        // 2. Login Attempt: Read from file
        fptr = fopen("C:\\Windows\\Temp\\login.txt", "r");
        if (fptr == NULL) {
            printf("No credentials found. Please use * to create them.\n");
            return 1;
        }
        // Read the two strings from the file
        fscanf(fptr, "%s %s", savedUser, savedPass);
        fclose(fptr);
        encrypt_decrypt(savedUser); // Decrypt the username
        encrypt_decrypt(savedPass); // Decrypt the password
        // 3. Compare Input vs Saved
        if (strcmp(inputUser, savedUser) == 0 && strcmp(inputPass, savedPass) == 0) {
            printf("Access Granted! Welcome back.\n");
        } else {
            printf("Wrong credentials! Access Denied.\n");
        }
    }
    printf("\nPress Enter to exit...");
    fflush(stdin); // Clears the input buffer
    getchar();     // Waits for user to press Enter
    getchar();

    return 0;
}