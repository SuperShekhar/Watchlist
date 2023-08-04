#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear()
{
    printf("\033[2J\033[H");
}

typedef struct
{
    char name[20];
    float rating;
    char genre[20];
} movie;

void printAllMovies(FILE *file)
{
    movie m;
    int count = 0;

    rewind(file);
    while (fread(&m, sizeof(movie), 1, file) == 1)
    {
        printf("Name=%sRating=%.2f\nGenre=%s\n", m.name, m.rating, m.genre);
        count++;
    }

    if (count == 0)
    {
        printf("The list is empty. Try adding new movies from the movie adding option.\n");
    }
}

void searchMoviesByFirstLetter(FILE *file, char letter)
{
    movie m;
    int count = 0;
    int found = 0;

    rewind(file);
    while (fread(&m, sizeof(movie), 1, file) == 1)
    {
        if (m.name[0] == letter)
        {
            printf("Name=%sRating=%.2f\nGenre=%s\n", m.name, m.rating, m.genre);
            found = 1;
        }
        count++;
    }

    if (count == 0)
    {
        printf("The list is empty. Try adding new movies from the movie adding option.\n");
    }
    else
    {
        if (found == 0)
        {
            printf("No movie found with that letter.\n");
            char ch;
            printf("Wanna search another movie with other letter? (Y/N): ");
            scanf(" %c", &ch);
            getchar();
            if (ch == 'y' || ch == 'Y')
            {
                char al;
                printf("Enter the new first letter of the movie: ");
                scanf(" %c", &al);
                getchar();
                searchMoviesByFirstLetter(file, al);
            }
        }
    }
}

FILE *watchedFile, *toWatchFile;
void closeFiles()
{
    fclose(watchedFile);
    fclose(toWatchFile);
}
void addToWatched(FILE *file)
{
    movie m;
    char ch, ch1;

    rewind(file);
    do
    {
        printf("Add movie name you want to add: ");
        fgets(m.name, sizeof(m.name), stdin);
        printf("Enter genre of the movie: ");
        fgets(m.genre, sizeof(m.genre), stdin);
        printf("Enter the rating: ");
        scanf("%f", &m.rating);
        fwrite(&m, sizeof(movie), 1, file);
        printf("Want to add another movie Y/N: ");
        scanf(" %c", &ch);
        getchar();
        if (ch != 'y' || ch != 'Y')
        {
            printf("If you wanna quit type Q if not enter any key to go back to the main menu: ");
            scanf(" %c", &ch1);
            getchar();
            if (ch1 == 'q' || ch1 == 'Q')
            {
                closeFiles();
                exit(0);
            }
        }
    } while (ch == 'y' || ch == 'Y');
}

void addToToWatched(FILE *file)
{
    movie m;
    char ch, ch1;

    rewind(file);
    do
    {
        printf("Add movie name you want to add: ");
        fgets(m.name, sizeof(m.name), stdin);
        printf("Enter genre of the movie: ");
        fgets(m.genre, sizeof(m.genre), stdin);
        printf("Enter the rating: ");
        scanf("%f", &m.rating);
        fwrite(&m, sizeof(movie), 1, file);
        printf("Want to add another movie Y/N: ");
        scanf(" %c", &ch);
        getchar();
        if (ch != 'y' || ch != 'Y')
        {
            printf("If you wanna quit enter Q if not enter any key to go back to the main menu: ");
            scanf(" %c", &ch1);
            getchar();
            if (ch1 == 'q' || ch1 == 'Q')
            {
                closeFiles();
                exit(0);
            }
        }
    } while (ch == 'y' || ch == 'Y');
}

void openProfile(FILE *watchedFile, FILE *toWatchFile)
{
    char ch1, ch2;

    while (1) // Infinite loop to keep the user in the main menu until they choose to exit.
    {
        clear();
        printf("WELCOME TO WATCHLIST\n");
        printf("To open your profile type 'p', to add a new movie or series type 'n':,to quit type 'q': ");
        ch1 = getchar();
        getchar();

        switch (ch1)
        {
        case 'p':
        case 'P':
            while (1) // Infinite loop to keep the user in the profile section until they choose to go back.
            {
                clear();
                printf("Welcome to the profile Section\n");
                printf("Enter W to see watched movies and Enter T to see to Watch movies: ");
                scanf(" %c", &ch2);
                getchar();

                if (ch2 == 'w' || ch2 == 'W')
                {
                    while (1) // Infinite loop to keep the user in the watched movies section until they choose to go back.
                    {
                        clear();
                        printf("This is watched movie section\n");
                        printf("Wanna see all list or search according to your own preference? For all, enter A; for search, enter S:  ");
                        scanf(" %c", &ch2);
                        getchar();

                        if (ch2 == 'a' || ch2 == 'A')
                        {
                            printAllMovies(watchedFile);
                            char ch3;
                            printf("To go back to the profile section enter P ; to quit, enter Q; and for main menu enter M: ");
                            scanf(" %c", &ch3);
                            getchar();
                            if (ch3 == 'p' || ch3 == 'P')
                            {
                                break; // Exit the watched movies section and go back to the profile section.
                            }
                            else if (ch3 == 'Q' || ch3 == 'q')
                            {
                                return; // Exit the program.
                            }
                            else if (ch3 == 'M' || ch3 == 'm')
                            {
                                openProfile(watchedFile, toWatchFile);
                            }
                        }
                        else if (ch2 == 's' || ch2 == 'S')
                        {
                            char al;
                            clear();
                            printf("We have sorted movies in alphabetical order. To find, type the first letter of the movie: ");
                            scanf(" %c", &al);
                            getchar();
                            searchMoviesByFirstLetter(watchedFile, al);
                            char ch3;
                            printf("To go back to the profile enter P; to quit enter Q ; and for main menu enter M:");
                            scanf(" %c", &ch3);
                            getchar();
                            if (ch3 == 'P' || ch3 == 'p')
                            {
                                break; // Exit the watched movies section and go back to the profile section.
                            }
                            else if (ch3 == 'Q' || ch3 == 'q')
                            {
                                return; // Exit the program.
                            }
                            else if (ch3 == 'M' || ch3 == 'M')
                            {
                                openProfile(watchedFile, toWatchFile);
                            }
                        }
                        else
                        {
                            clear();
                            printf("Invalid choice\n");
                            char retry;
                            printf("Do you want to try again? (Y/N): ");
                            scanf(" %c", &retry);
                            getchar();
                            if (retry == 'y' || retry == 'Y')
                            {
                                continue; // Retry the watched movies section.
                            }
                            else
                            {
                                return; // Exit the program.
                            }
                        }
                    }
                }
                else if (ch2 == 'T' || ch2 == 't')
                {
                    while (1) // Infinite loop to keep the user in the to_watch movies section until they choose to go back.
                    {
                        clear();
                        printf("This is to_watched movie section\n");
                        printf("Wanna see all list or search according to your own preference? For all, enter A; for search, enter S:  ");
                        scanf(" %c", &ch2);
                        getchar();

                        if (ch2 == 'a' || ch2 == 'A')
                        {
                            printAllMovies(toWatchFile);
                            char ch3;
                            printf("To go back to the profile section enter P; to quit enter Q; and for main menu enter M: ");
                            scanf(" %c", &ch3);
                            getchar();
                            if (ch3 == 'P' || ch3 == 'p')
                            {
                                break; // Exit the to_watch movies section and go back to the profile section.
                            }
                            else if (ch3 == 'Q' || ch3 == 'q')
                            {
                                return; // Exit the program.
                            }
                            else if (ch3 == 'M' || ch3 == 'm')
                            {
                                openProfile(watchedFile, toWatchFile);
                            }
                        }
                        else if (ch2 == 's' || ch2 == 'S')
                        {
                            char al;
                            clear();
                            printf("We have sorted movies in alphabetical order. To find, type the first letter of the movie: ");
                            scanf(" %c", &al);
                            getchar();
                            searchMoviesByFirstLetter(toWatchFile, al);
                            char ch3;
                            printf("To go back to the profile section enter P; to quit  enter Q ; and for main menu enter M: ");
                            scanf(" %c", &ch3);
                            getchar();
                            if (ch3 == 'P' || ch3 == 'p')
                            {
                                break; // Exit the to_watch movies section and go back to the profile section.
                            }
                            else if (ch3 == 'Q' || ch3 == 'q')
                            {
                                return; // Exit the program.
                            }
                            else if (ch3 == 'M' || ch3 == 'm')
                            {
                                openProfile(watchedFile, toWatchFile);
                            }
                        }
                        else
                        {
                            clear();
                            printf("Invalid choice\n");
                            char retry;
                            printf("Do you want to try again? (Y/N): ");
                            scanf(" %c", &retry);
                            getchar();
                            if (retry == 'y' || retry == 'Y')
                            {
                                continue; // Retry the to_watch movies section.
                            }
                            else
                            {
                                return; // Exit the program.
                            }
                        }
                    }
                }
                else
                {
                    clear();
                    printf("Invalid choice\n");
                    char retry;
                    printf("Do you want to try again? (Y/N): ");
                    scanf(" %c", &retry);
                    getchar();
                    if (retry == 'y' || retry == 'Y')
                    {
                        continue; // Retry the profile section.
                    }
                    else
                    {
                        return; // Exit the program.
                    }
                }
            }
            break;

        case 'n':
        case 'N':
            clear();
            printf("This is where you can add a new movie\n");
            printf("Enter W to add in watched and Enter T to add to To_Watch movie:  ");
            scanf(" %c", &ch2);
            getchar();

            if (ch2 == 'W' || ch2 == 'w')
            {
                addToWatched(watchedFile);
            }
            else if (ch2 == 't' || ch2 == 'T')
            {
                addToToWatched(toWatchFile);
            }
            else
            {
                clear();
                printf("Invalid choice\n");
                char retry;
                printf("Do you want to try again? (Y/N): ");
                scanf(" %c", &retry);
                getchar();
                if (retry == 'y' || retry == 'Y')
                {
                    continue; // Retry the movie adding section.
                }
            }
            break;
            
           case'q':
           case'Q':
              return;

        default:
            clear();
            printf("Invalid choice\n");
            char retry;
            printf("Do you want to try again? (Y/N): ");
            scanf(" %c", &retry);
            getchar();
            if (retry == 'y' || retry == 'Y')
            {
                continue; // Retry the main menu section.
            }
            else
            {
                return; // Exit the program.
            }
        }
    }
}

int main()
{

    watchedFile = fopen("watched.bin", "a+b");
    toWatchFile = fopen("to_watched.bin", "a+b");

    if (watchedFile == NULL || toWatchFile == NULL)
    {
        printf("Couldn't load the app.\n");
        exit(1);
    }

    openProfile(watchedFile, toWatchFile);

    fclose(watchedFile);
    fclose(toWatchFile);

    return 0;
}