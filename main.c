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

