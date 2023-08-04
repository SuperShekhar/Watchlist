#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to clear the terminal
void clear_terminal()
{
    printf("\033[2J\033[H");
}

// Function to set text color
void set_text_color(int color_code)
{
    printf("\033[0;%dm", color_code);
}

// Function to reset text color to default
void reset_text_color()
{
    printf("\033[0m");
}

typedef struct
{
    char name[20];
    float rating;
    char genre[20];
} movie;

int main()
{
    FILE *data, *data2;
    movie m;
    char user[20], ch1, ch2, ch3, ch4, al;
    data = fopen("watched.bin", "a+b");
    data2 = fopen("to_watched.bin", "a+b");
    if (data == NULL || data2 == NULL)
    {
        set_text_color(31); // Set text color to red
        printf("Couldn't load app\n");
        reset_text_color(); // Reset text color to default
        exit(1);
    }

there:
    clear_terminal(); // Clear the terminal

    set_text_color(33); // Set text color to yellow
    printf("WELCOME TO WATCHLIST\n");
    printf("To open your profile type 'p', to add new movie or series type 'n': ");
    reset_text_color(); // Reset text color to default

    int found = 0;
    ch1 = getchar();
    switch (ch1)
    {
    case 'p':
    case 'P':
    yes:
        clear_terminal(); // Clear the terminal

        set_text_color(36); // Set text color to cyan
        printf("Welcome to the profile Section\n");
        printf("Enter W to see watched and Enter T to see to Watch movie: ");
        reset_text_color(); // Reset text color to default

        scanf(" %c", &ch2);
        getchar();

        if (ch2 == 'w' || ch2 == 'W')
        {
        again:
            clear_terminal(); // Clear the terminal

            set_text_color(36); // Set text color to cyan
            printf("This is watched movie section\n");
            printf("Wanna see all list or search according to your own preference for all enter A for search Enter S: ");
            reset_text_color(); // Reset text color to default

            scanf(" %c", &ch4);
            getchar();
            if (ch4 == 'a' || ch4 == 'A')
            {
                int count = 0;
                while ((fread(&m, sizeof(movie), 1, data)) == 1)
                {
                    printf("Name=%sRating=%.2f\nGenre=%s\n", m.name, m.rating, m.genre);
                    count++;
                }
                if (count == 0)
                {
                    printf("the list is empty try adding a new movie from movie adding option\n");
                }
                printf("to again go back to the main menu enter M to exit enter anything except M: ");
                scanf(" %c", &ch3);
                getchar();
                if (ch3 == 'm' || ch3 == 'M')
                    goto there;
                else
                {
                    printf("Thank you for using our app\n");
                    return 0;
                }
            }
            else if (ch4 == 'S' || ch4 == 's')
            {
                clear_terminal(); // Clear the terminal

                set_text_color(36); // Set text color to cyan
                printf("We have sorted movie in alphabetical order to find type the first letter of the movie: ");
                reset_text_color(); // Reset text color to default

                scanf(" %c", &al);
                getchar();
                while ((fread(&m, sizeof(movie), 1, data)) == 1)
                {
                    if (m.name[0] == al)
                    {
                        found = 1;
                        printf("Name=%sRating=%.2f\nGenre=%s\n", m.name, m.rating, m.genre);
                    }
                }
                if (found == 0)
                {
                    printf("No movie found with that letter\n");
                }
            }
            else
            {
                clear_terminal(); // Clear the terminal

                set_text_color(31); // Set text color to red
                printf("Invalid choice\n");
                printf("Choose again\n");
                reset_text_color(); // Reset text color to default
                goto again;
            }
            printf("to again go back to the main menu enter M to exit enter anything except M: ");
            scanf(" %c", &ch3);
            getchar();
            if (ch3 == 'm' || ch3 == 'M')
                goto there;
            else
            {
                printf("Thank you for using our app\n");
                return 0;
            }
        }

        else if (ch2 == 'T' || ch2 == 't')
        {
        mere:
            clear_terminal(); // Clear the terminal

            set_text_color(36); // Set text color to cyan
            printf("This is to_watched movie section\n");
            printf("Wanna see all list or search according to your own preference for all enter A for search Enter S: ");
            reset_text_color(); // Reset text color to default

            scanf(" %c", &ch4);
            getchar();
            if (ch4 == 'a' || ch4 == 'A')
            {
                int count = 0;
                while ((fread(&m, sizeof(movie), 1, data2)) == 1)
                {
                    printf("Name=%sRating=%.2f\nGenre=%s\n", m.name, m.rating, m.genre);
                    count++;
                }
                if (count == 0)
                {
                    printf("the list is empty try adding a new movie from the movie adding option\n");
                }
                printf("to again go back to the main menu enter M to exit enter anything except M: ");
                scanf(" %c", &ch3);
                getchar();
                if (ch3 == 'm' || ch3 == 'M')
                    goto there;
                else
                {
                    printf("Thank you for using our app\n");
                    return 0;
                }
            }
            else if (ch4 == 'S' || ch4 == 's')
            {
                clear_terminal(); // Clear the terminal

                set_text_color(36); // Set text color to cyan
                printf("We have sorted movie in alphabetical order to find type the first letter of the movie: ");
                reset_text_color(); // Reset text color to default

                scanf(" %c", &al);
                getchar();
                while ((fread(&m, sizeof(movie), 1, data2)) == 1)
                {
                    if (m.name[0] == al)
                    {
                        printf("Name=%sRating=%.2f\nGenre=%s\n", m.name, m.rating, m.genre);
                        found = 1;
                    }
                }
                if (found == 0)
                {
                    printf("No movie found with that letter\n");
                }
            }
            else
            {
                clear_terminal(); // Clear the terminal

                set_text_color(31); // Set text color to red
                printf("Invalid choice\n");
                printf("Choose again\n");
                reset_text_color(); // Reset text color to default
                goto mere;
            }
            printf("to again go back to the main menu enter M to exit enter anything except M: ");
            scanf(" %c", &ch3);
            getchar();
            if (ch3 == 'm' || ch3 == 'M')
                goto there;
            else
            {
                printf("Thank you for using our app\n");
                return 0;
            }
        }
        else
        {
            clear_terminal(); // Clear the terminal

            set_text_color(31); // Set text color to red
            printf("Invalid choice\n");
            printf("Choose again\n");
            reset_text_color(); // Reset text color to default
            goto yes;
        }
        break;

    case 'n':
    case 'N':
    {
    here:
        clear_terminal(); // Clear the terminal

        set_text_color(36); // Set text color to cyan
        printf("This is where you can add a new movie\n");
        printf("Enter W to add in watched and Enter T to add to To_Watch movie: ");
        reset_text_color(); // Reset text color to default

        scanf(" %c", &ch2);
        getchar();
        if (ch2 == 'W' || ch2 == 'w')
        {
            rewind(data2);
            clear_terminal(); // Clear the terminal

            set_text_color(36); // Set text color to cyan
            printf("Welcome to the place where you can add a movie to the watched section\n");
            reset_text_color(); // Reset text color to default

            do
            {
                printf("Add movie name you want to add: ");
                fgets(m.name, sizeof(m.name), stdin);
                printf("Enter genre of the movie: ");
                fgets(m.genre, sizeof(m.genre), stdin);
                printf("Enter the rating: ");
                scanf("%f", &m.rating);
                fwrite(&m, sizeof(movie), 1, data);
                printf("Want to add another movie Y/N: ");
                scanf(" %c", &ch3);
                getchar();
            } while (ch3 == 'y' || ch3 == 'Y');
            printf("to again go back to the main menu enter M to exit enter anything except M: ");
            scanf(" %c", &ch3);
            getchar();
            if (ch3 == 'm' || ch3 == 'M')
                goto there;
            else
            {
                printf("Thank you for using our app\n");
                return 0;
            }
        }

        else if (ch2 == 't' || ch2 == 'T')
        {
            rewind(data2);
            clear_terminal(); // Clear the terminal

            set_text_color(36); // Set text color to cyan
            printf("Welcome to the place where you can add a movie to the to_watched section\n");
            reset_text_color(); // Reset text color to default

            do
            {
                printf("Add movie name you want to add: ");
                fgets(m.name, sizeof(m.name), stdin);
                printf("Enter genre of the movie: ");
                fgets(m.genre, sizeof(m.genre), stdin);
                printf("Enter the rating: ");
                scanf("%f", &m.rating);
                fwrite(&m, sizeof(movie), 1, data2);
                printf("Want to add another movie Y/N: ");
                scanf(" %c", &ch3);
                getchar();
            } while (ch3 == 'y' || ch3 == 'Y');
            printf("to again go back to the main menu enter M to exit enter anything except M: ");
            scanf(" %c", &ch3);
            getchar();
            if (ch3 == 'm' || ch3 == 'M')
                goto there;
            else
            {
                printf("Thank you for using our app\n");
                return 0;
            }
        }
        else
        {
            clear_terminal(); // Clear the terminal

            set_text_color(31); // Set text color to red
            printf("Invalid choice\n");
            printf("Choose again\n");
            reset_text_color(); // Reset text color to default
            goto here;
        }
        break;
    }

    default:
        clear_terminal(); // Clear the terminal

        set_text_color(31); // Set text color to red
        printf("Invalid choice\n");
        printf("Choose again\n");
        reset_text_color(); // Reset text color to default
        goto there;
    }

    fclose(data);
    fclose(data2);
    return 0;
}
