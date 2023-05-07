#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct
{
    char nama_user[20];
    char kata_sandi[20];
} User;

void daftar();
User *cariUser(char *nama_user);
User loginUser(char *nama_user, char *kata_sandi);
void startKuis();
int main(int argc, char *argv[]);

void printHeader()
{
    printf("**************************************************\n");
    printf("*                                                *\n");
    printf("*   Selamat datang di game Who Wants to Be a     *\n");
    printf("*   Millionaire!                                 *\n");
    printf("*                                                *\n");
    printf("**************************************************\n\n");
}
void daftar(char *nama_user, char *kata_sandi)
{
    User userBaru;
    FILE *fp;

    strcpy(userBaru.nama_user, nama_user);
    strcpy(userBaru.kata_sandi, kata_sandi);

    fp = fopen("database/login.bin", "ab");
    if (fp == NULL)
    {
        printf("Error membuka file!\n");
        exit(1);
    }

    fwrite(&userBaru, sizeof(User), 1, fp);
    fclose(fp);

    printf("User berhasil didaftarkan!\n");
}


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

char kunciJawaban[] = {
        'a', 'c', 'b', 'b', 'c',
        'd', 'a', 'b', 'c', 'a'};
    char jawaban;
    int skor = 0;
    int jumlahPertanyaan = sizeof(pertanyaan) / sizeof(pertanyaan[0]);

    for (int i = 0; i < jumlahPertanyaan; i++)
    {

        printf("Pertanyaan %d: %s\n", i + 1, pertanyaan[i]);
        for (int j = 0; j < 4; j++)
        {
            printf("%c) %s\n", 'a' + j, pilihan[i][j]);
        }
        printf("Jawaban (a/b/c/d): ");
        scanf(" %c", &jawaban);
        if (jawaban == kunciJawaban[i])
        {
            skor += 10;
            printf("Jawaban benar! Kamu mendapat 10 poin.\n\n");
        }
        else
        {
            printf("Jawaban salah! Kamu tidak mendapat poin.\n\n");
        }
    }

    printf("Kamu telah menyelesaikan kuis! Skormu adalah: %d\n", skor);
}


