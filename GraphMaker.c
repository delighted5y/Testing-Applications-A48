#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "graffit.c"

User *queryByUsername(char *name)
{
    for (FriendNode *p = allUsers; NULL != p; p = p->next)
    {
        if (strcmp(p->user->name, name) == 0)
        {
            return p->user;
        }
    }
    return NULL;
}

int get_length(FriendNode *head)
{
    int length = 0;
    for (FriendNode *p = head; p != NULL; p = p->next)
    {
        length++;
    }
    return length;
}

void output_all_users()
{
    FILE *file = NULL;
    file = fopen("all_users.txt", "w");
    if (file == NULL)
    {
        printf("Failed to output to file!\n");
        return;
    }
    for (FriendNode *p = allUsers; p != NULL; p = p->next)
    {
        fprintf(file, "User name: %s\n", p->user->name);
        fprintf(file, "  Friends:\n");
        for (FriendNode *f = p->user->friends; f != NULL; f = f->next)
        {
            fprintf(file, "    %s\n", f->user->name);
        }
        fprintf(file, "  Brands:\n");
        for (BrandNode *b = p->user->brands; b != NULL; b = b->next)
        {
            fprintf(file, "    %s\n", b->brand_name);
        }
        fprintf(file, "----------\n");
    }
    printf("Graph outputted to all_users.txt.\n");
    fclose(file);
    return;
}

void output_all_brands()
{
    FILE *file = NULL;
    file = fopen("all_brands.txt", "w");
    if (file == NULL)
    {
        printf("Failed to output to file!\n");
        return;
    }
    for (int i = 0; i < MAT_SIZE; i++)
    {
        int index = get_brand_index(brand_names[i]);
        fprintf(file, "Brand name: %s\n", brand_names[i]);
        fprintf(file, "Brand idx: %d\n", index);
        fprintf(file, "Similar brands:\n");
        for (int j = 0; j < MAT_SIZE; i++)
        {
            if (brand_adjacency_matrix[index][j] == 1 && strcmp(brand_names[j], "") != 0)
            {
                fprintf(file, "   %s\n", brand_names[j]);
            }
        }
        fprintf(file, "----------\n");
    }
    printf("Graph outputted to all_brands.txt.\n");
    fclose(file);
    return;
}

void populate_graph(int users)
{
    char name[MAX_STR_LEN];
    for (int i = 0; i < users; i++)
    {
        sprintf(name, "%d", i);
        create_user(name);
    }
}

void generateGraph(int users, int comp)
{
    if (users <= 0 || comp <= 0 || comp > 10)
    {
        printf("Failed to generate user graph!\n");
        return;
    }
    char name[MAX_STR_LEN];
    char friend[MAX_STR_LEN];
    populate_graph(users);
    for (int i = 0; i < (comp * comp * users); i++)
    {
        if ((rand() % 10) <= comp)
        {
            sprintf(name, "%d", rand() % users);
            sprintf(friend, "%d", rand() % users);
            add_friend(queryByUsername(name), queryByUsername(friend));
        }
    }
    printf("Graph successfully generated.\n");
    return;
}

void generateGraphFile(int users, int comp)
{
    FILE *file = NULL;
    file = fopen("user_graph.txt", "w");
    if (file == NULL)
    {
        printf("Failed to output to file!\n");
        return;
    }
    if (users <= 0 || comp <= 0 || comp > 10)
    {
        printf("Failed to generate user graph!\n");
        return;
    }
    fprintf(file, "%d\n", users);
    for (int i = 0; i < (comp * comp * users); i++)
    {
        if ((rand() % 10) <= comp)
        {
            fprintf(file, "%d>%d\n", rand() % users, rand() % users);
        }
    }
    printf("user_graph.txt successfully generated.\n");
    fclose(file);
    return;
}

void rand_string(char *str, int size)
{
    const char bank[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (int i = 0; i < size; i++)
    {
        int key = rand() % (int)(sizeof(bank) - 1);
        str[i] = bank[key];
    }
    str[size] = '\0';
    return;
}

void generate_brand_file(int num_brands, int max_name_len, int similarity)
{
    if (num_brands <= 0)
    {
        printf("Please enter a positive number for brands.\n");
        return;
    }
    FILE *file = NULL;
    file = fopen("brand_graph.txt", "w");
    if (file == NULL)
    {
        printf("Failed to output to file!\n");
        return;
    }
    int matrix[num_brands][num_brands];
    for (int y = 0; y < num_brands; y++)
    {
        for (int x = 0; x < num_brands; x++)
        {
            matrix[y][x] = 0;
        }
    }
    char brand_name[MAX_STR_LEN];
    for (int i = 0; i < num_brands; i++)
    {
        rand_string(brand_name, max_name_len);
        fprintf(file, "%s", brand_name);
        if (i == num_brands - 1)
        {
            fprintf(file, "\n");
        }
        else
        {
            fprintf(file, ",");
        }
    }
    for (int i = 0; i < pow(similarity, sqrt(similarity)); i++)
    {
        if ((rand() % 10) <= similarity)
        {
            int x = rand() % num_brands;
            int y = rand() % num_brands;
            if (x != y)
            {
                matrix[x][y] = 1;
                matrix[y][x] = 1;
            }
        }
    }

    for (int y = 0; y < num_brands; y++)
    {
        for (int x = 0; x < num_brands; x++)
        {
            if (x == num_brands - 1)
            {
                fprintf(file, "%d\n", matrix[y][x]);
            }
            else
            {
                fprintf(file, "%d,", matrix[y][x]);
            }
        }
    }
    fclose(file);
    printf("brand_graph.txt successfully generated.\n");
    return;
}

void loadGraphFile(char *file_name)
{
    FILE *file = NULL;
    file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Failed to load to file!\n");
        return;
    }
    char line[MAX_STR_LEN];
    //create all users
    int num_users;
    fscanf(file, "%d", &num_users);
    populate_graph(num_users);
    char name[MAX_STR_LEN];
    char friend[MAX_STR_LEN];
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file))
    {
        int i = 0;
        while (line[i] != '>')
        {
            name[i] = line[i];
            i++;
        }
        name[i] = '\0'; //terminate
        i++;
        int j = 0;
        while (line[i] != '\n')
        {
            friend[j] = line[i];
            i++;
            j++;
        }
        friend[j] = '\0'; //terminate
        //printf("%s, %s\n", name, friend);
        add_friend(queryByUsername(name), queryByUsername(friend));
    }
    fclose(file);
    printf("%s succesfully loaded.\n", file_name);
    return;
}