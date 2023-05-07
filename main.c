#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


User *cariUser(char *nama_user)
{
    User *user = malloc(sizeof(User));
    FILE *fp;

    fp = fopen("database/login.bin", "rb");
    if (fp == NULL)
    {
        printf("Error membuka file!\n");
        exit(1);
    }

    while (fread(user, sizeof(User), 1, fp))
    {
        if (strcmp(user->nama_user, nama_user) == 0)
        {
            fclose(fp);
            return user;
        }
    }

    fclose(fp);
    free(user);
    return NULL;
}

User loginUser(char *nama_user, char *kata_sandi)
{
    User userKosong = {"", ""};
    User *user;

    user = cariUser(nama_user);

    if (user != NULL && strcmp(user->kata_sandi, kata_sandi) == 0)
    {
        User userValid = *user;
        free(user);
        return userValid;
    }

    return userKosong;
}

int main(int argc, char *argv[])
{
    printHeader();

    if (argc == 4 && strcmp(argv[1], "daftar") == 0)
    {
        daftar(argv[2], argv[3]);
    }
    else if (argc == 4 && strcmp(argv[1], "login") == 0)
    {
        User user = loginUser(argv[2], argv[3]);
        if (strcmp(user.nama_user, "") == 0)
        {
            printf("Username atau kata sandi salah!\n");
            printf("Cara menggunakan: login <nama_user> <kata_sandi>\n", argv[0]);
            return 1;
        }

        printf("Selamat datang, %s! Mari mulai kuis, dan jawab dengan benar yaa!!!\n\n", user.nama_user);
        startKuis();
    }
    else
    {
        printf("Argumen tidak valid!\n");
        printf("Cara menggunakan:\n");
        printf("  Mendaftarkan user baru: %s daftar <nama_user> <kata_sandi>\n", argv[0]);
        printf("  Masuk dan mulai kuis: %s login <nama_user> <kata_sandi>\n", argv[0]);
        return 1;
    }

    return 0;
}
