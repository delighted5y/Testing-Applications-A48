#include <stdlib.h>
#include "GraphMaker.c"
#include <string.h>

void getInt(char *prompt, int *var)
{
    printf("%s = ", prompt);
    scanf("%d", var);
    getchar();
}

void getStr(char *prompt, char *var)
{
    printf("%s = ", prompt);
    fgets(&var[0], 1024, stdin);
    int i = strlen(&var[0]);
    if (var[i - 1] == '\n')
        var[i - 1] = '\0';
}

int main()
{
    int choice;
    char brandFile[MAX_STR_LEN];
    char userFile[MAX_STR_LEN];
    strcpy(brandFile, ""); //zero out file name
    userFile[0]= '\0';// try different ways to set to empty string
    char username[MAX_STR_LEN];
    char brand_name[MAX_STR_LEN];
    char friend_name[MAX_STR_LEN];
    srand(time(NULL)); // seed the rand;
    choice = 0;

    while (choice != 17)
    {
        if (strcmp(userFile, "") == 0)
        {
            printf("                         No graph file loaded\n");
        }
        else
        {
            printf("                         Loaded graph file: %s\n", userFile);
        }
        if (strcmp(brandFile, "") == 0)
        {
            printf("                         No brand matrix loaded\n");
        }
        else
        {
            printf("                         Loaded brand matrix: %s\n", brandFile);
        }
        printf("Please select from among the following options:\n");
        printf("0 - Create new user\n");
        printf("1 - Add a new friend\n");
        printf("2 - Delete a friend\n");
        printf("3 - Follow a brand\n");
        printf("4 - Unfollow a brand\n");
        printf("5 - Print all users\n");
        printf("6 - Print all brands\n");
        printf("7 - Print user info\n");
        printf("8 - Print brand info\n");
        printf("9 - Print all users' info\n");
        printf("10 - Load brand matrix file\n");
        printf("11 - Load user graph from file\n");
        printf("12 - Get mutual friends\n");
        printf("13 - Get Suggested friends\n");
        printf("14 - Follow Suggest friends\n");
        printf("15 - Follow Suggest brands\n");
        printf("16 - Get degrees of connection\n");
        printf("17 - Delete Graph and exit\n");
        printf("18 - Generate user graph\n");
        printf("19 - Generate user graph file\n");
        printf("20 - Generate brand graph file\n");
        printf("21 - Output all brands' info to file\n");
        printf("22 - Output all users' info to file\n");

        getInt("Enter choice", &choice);
        printf("------------------------------------------------\n");

        if (choice == 0)
        {
            getStr("Username", username);
            if (NULL != create_user(username))
            {
                printf("Successfully created user.\n");
            }
        }

        if (choice == 1)
        {
            getStr("Who wants to add a friend:", username);
            getStr("The friend to add:", friend_name);
            User *user = queryByUsername(username);
            User *friend = queryByUsername(friend_name);
            add_friend(user, friend);
        }

        if (choice == 2)
        {
            getStr("Who wants to delete a friend:", username);
            getStr("The friend to delete:", friend_name);
            User *user = queryByUsername(username);
            User *friend = queryByUsername(friend_name);
            remove_friend(user, friend);
        }

        if (choice == 3)
        {
            getStr("Who wants to follow a brand:", username);
            getStr("The brand to follow:", brand_name);
            User *user = queryByUsername(username);
            follow_brand(user, brand_name);
        }

        if (choice == 4)
        {
            getStr("Who wants to unfollow a brand:", username);
            getStr("The brand to unfollow:", brand_name);
            User *user = queryByUsername(username);
            unfollow_brand(user, brand_name);
        }

        if (choice == 5)
        {
            printf("------------------All Users------------------\n");
            for (FriendNode *p = allUsers; NULL != p; p = p->next)
            {
                printf("%s\n", p->user->name);
            }
            printf("---------------------End---------------------\n");
        }
        if (choice == 6)
        {
            printf("------------------All Brands------------------\n");
            for (int i = 0; i < MAT_SIZE; i++)
            {
                printf("%s\n", brand_names[i]);
            }
            printf("---------------------End---------------------\n");
        }
        if (choice == 7)
        {
            getStr("Who's info do you want to print:", username);
            User *user = queryByUsername(username);
            print_user_data(user);
        }

        if (choice == 8)
        {
            getStr("Which brand's info do you want to print:", brand_name);
            print_brand_data(brand_name);
        }

        if (choice == 9)
        {
            for (FriendNode *p = allUsers; p != NULL; p = p->next)
            {
                print_user_data(p->user);
            }
        }
        if (choice == 10)
        {
            printf("Please note that an invalid filename will break the program.\n");
            getStr("Please enter filename:", brandFile);
            populate_brand_matrix(brandFile);
        }
        if (choice == 11)
        {
            printf("This will clear the existing graph.\n");
            getStr("Please enter filename:", userFile);
            loadGraphFile(userFile);
        }
        if (choice == 12)
        {
            getStr("User1:", username);
            getStr("User2:", friend_name);
            User *a = queryByUsername(username);
            User *b = queryByUsername(friend_name);
            int mutual = get_mutual_friends(a, b);
            if (mutual < 0)
            {
                printf("Failed to get mutual friends.\n");
            }
            else
            {
                printf("%s and %s has %d mutual friends.\n", a->name, b->name, mutual);
            }
        }
        if (choice == 13)
        {
            getStr("Suggest friend for:", username);
            User *tmp = get_suggested_friend(queryByUsername(username));
            if (NULL == tmp)
            {
                printf("Failed to suggest friends!\n");
            }
            else
            {
                printf("Suggest friend: %s\n", tmp->name);
            }
        }
        if (choice == 14)
        {
            int num;
            getStr("Who wants to follow suggest friends:", username);
            getInt("Number of suggested friends to follow:", &num);
            int added = add_suggested_friends(queryByUsername(username), num);
            if (added < 0)
            {
                printf("Failed to add suggested friends!\n");
            }
            else
            {
                printf("Successfully followed %d suggested friends.\n", added);
            }
        }
        if (choice == 15)
        {
            int num;
            getStr("Who wants to follow suggest brands:", username);
            getInt("Number of suggested brands to follow:", &num);
            int added = follow_suggested_brands(queryByUsername(username), num);
            if (added < 0)
            {
                printf("Failed to add suggested brands!\n");
            }
            else
            {
                printf("Successfully followed %d suggested brands.\n", added);
            }
        }
        if (choice == 16)
        {
            printf("Enter two users to get there degree of connection.\n");
            getStr("User1:", username);
            getStr("User2:", friend_name);
            User *a = queryByUsername(username);
            User *b = queryByUsername(friend_name);
            int num = get_degrees_of_connection(a, b);
            if (num < 0)
            {
                printf("failed to get the degree of connection!\n");
            }
            else
            {
                printf("The degree of connection between %s and %s is %d.\n", a->name, b->name, num);
            }
        }

        if (choice == 18)
        {
            int num_users = 0;
            int comp = 0;
            printf("This will clear the existing graph.\n");
            getInt("Number of users to generate", &num_users);
            getInt("Complexity of relationships:\nEnter a number from 1 to 9 where 1 means least number of relationships and 9 means most number of relationships:\nComplexity", &comp);
            userFile[0] = '\0';
            generateGraph(num_users, comp);
        }

        if (choice == 19)
        {
            int num_users = 0;
            int comp = 0;
            getInt("Number of users to generate", &num_users);
            getInt("Complexity of relationships:\nEnter a number from 1 to 9 where 1 means least number of relationships and 9 means most number of relationships:\nComplexity", &comp);
            generateGraphFile(num_users, comp);
        }
        if (choice == 20)
        {
            int num_brands = 0;
            int similarity = 0;
            int max_len;
            getInt("Number of brands to generate(Don't forget to change MAT_SIZE!)", &num_brands);
            printf("Amount of simiarity:Enter a number from 1 to 9 where 1 means least number of simiarities and 9 means most number of simiarities:\n");
            getInt("Similarty", &similarity);
            getInt("Maximum brand name length (enter an reasonable number, and make sure number of brand * max length < 200)", &max_len);
            generate_brand_file(num_brands, max_len, similarity);
        }
        if (choice == 21)
        {
            output_all_brands();
        }
        if (choice == 22)
        {
            output_all_users();
        }

        printf("------------------------------------------------\n");
    } // Enf while (choice!=9)
    //You can implement a function to delete the list of all users!
    //delete_graph(allUsers);
    printf("You can write a function to delete the graph here.\n");
    printf("Done!");
    return 0;
}