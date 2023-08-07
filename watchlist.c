#include <stdio.h>
#include <stdlib.h>

// Function to clear the console screen
// if using linux you can comment out this clear function and uncomment the other clear function
void clear()
{
    system("cls");
}
// If you are using linux uncomment this clear function and comment out the other clear function
/*
void clear()
{
    system("clear");
}*/

// Structure to represent a movie
typedef struct
{
    char name[20];
    float rating;
    char genre[20];
} movie;
// Function to check if a file is empty
int isFileEmpty(FILE *file)
{
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        return 1;
    }
    return 0;
}

// Function to print all movies from a file
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

// Function to search and print movies by the first letter of their name
void searchMoviesByFirstLetter(FILE *file, char letter)
{   
    clear();
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
            printf("Wanna search another movie with another letter? (Y/N): ");
            scanf(" %c", &ch);
            getchar();
            if (ch == 'y' || ch == 'Y')
            {
                clear();
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
void clearFiles()
{
    // Clear the "watched" file
    fclose(watchedFile);
    watchedFile = fopen("watched.bin", "wb"); // Open in write mode to truncate and clear the file
    if (watchedFile == NULL)
    {
        printf("Already Cleared or Error clearing the watched file.\n");
        exit(1);
    }

    // Clear the "to watch" file
    fclose(toWatchFile);
    toWatchFile = fopen("to_watched.bin", "wb"); // Open in write mode to truncate and clear the file
    if (toWatchFile == NULL)
    {
        printf("Already Cleared Error clearing the to watch file.\n");
        exit(1);
    }
}

// Function to close open files
void closeFiles()
{
    fclose(watchedFile);
    fclose(toWatchFile);
}

// Function to add movies to the "watched" list
void addToWatched(FILE *file)
{
    clear();
    movie m;
    char ch, ch1;

    rewind(file);
    do
    {
        printf("Add movie name you want to add: ");
        fgets(m.name, sizeof(m.name), stdin);
        printf("Enter genre of the movie: ");
        fgets(m.genre, sizeof(m.genre), stdin);
        int validRating = 0;
        while (!validRating)
        {
            printf("Enter the rating: ");
            char ratingStr[20];
            fgets(ratingStr, sizeof(ratingStr), stdin);

            if (sscanf(ratingStr, "%f", &m.rating) == 1)
            {
                validRating = 1;
            }
            else
            {
                printf("Invalid rating. Please enter a numeric value.\n");
            }
        }
        fwrite(&m, sizeof(movie), 1, file);
        printf("Want to add another movie Y/N:\n");
        scanf(" %c", &ch);
        getchar();
        clear();

    } while (ch == 'y' || ch == 'Y');
    clear();
    printf("Quit = Q\nMain Menu= Any key:\n");
    ch1=getchar();
    if (ch1 == 'q' || ch1 == 'Q')
    {
        closeFiles();
        exit(0);
    }
}

// Function to add movies to the "to watch" list
void addToToWatched(FILE *file)
{   clear();
    movie m;
    char ch, ch1;

    rewind(file);
    do
    {
        printf("Add movie name you want to add: ");
        fgets(m.name, sizeof(m.name), stdin);
        printf("Enter genre of the movie: ");
        fgets(m.genre, sizeof(m.genre), stdin);
        int validRating = 0;
        while (!validRating)
        {
            printf("Enter the rating: ");
            char ratingStr[20];
            fgets(ratingStr, sizeof(ratingStr), stdin);

            if (sscanf(ratingStr, "%f", &m.rating) == 1)
            {
                validRating = 1;
            }
            else
            {
                printf("Invalid rating. Please enter a numeric value.\n");
            }
        }
        fwrite(&m, sizeof(movie), 1, file);
        printf("Want to add another movie Y/N:\n");
        scanf(" %c", &ch);
        getchar();
        clear();
    } while (ch == 'y' || ch == 'Y');
    clear();
    printf("Quit = Q \nMain Menu= Enter Any key:\n");
    ch1=getchar();
    if (ch1 == 'q' || ch1 == 'Q')
    {
        closeFiles();
        exit(0);
    }
}

// Function to open the user's profile
void openProfile(FILE *watchedFile, FILE *toWatchFile)
{
    char ch2;

    while (1) // Infinite loop to keep the user in the main menu until they choose to exit.
    {
        clear();
        printf("WELCOME TO WATCHLIST\n");
        printf("What do you want to do?\n\n");
        printf("Profile = P\nAdd New Movie=N\nQuit = Q\nReset Application=R\n\n");
        char ch1 = getchar();
        getchar();

        switch (ch1)
        {
        case 'r':
        case 'R':
            clear();
            clearFiles();
            printf("loading.......\n");
            printf("Application Reset Successful.\n");
            printf("Press any key to continue.\n");
            getchar();
            openProfile(watchedFile, toWatchFile);
            break;
        case 'p':
        case 'P':
            if (isFileEmpty(watchedFile) && isFileEmpty(toWatchFile))
                {
                    printf("List is empty. Try putting some movies first from the adding section and go to the main menu section.\n");
                    getchar(); 
                    break;
                }
            while (1) // Infinite loop to keep the user in the profile section until they choose to go back.
            {
                clear();
                printf("Welcome to the Profile Section\n\n");
                printf("Which list you want to see ?\n");
                printf("Already Watched Movie= W\nTo_Watch Movie=T\n\n");
                scanf(" %c", &ch2);
                getchar();

                if (ch2 == 'w' || ch2 == 'W')
                {
                    while (1) // Infinite loop to keep the user in the watched movies section until they choose to go back.
                    {
                        clear();
                        printf("This is watched movie section\n");
                        printf("What do you want to do?\n");
                        printf("See All Watched List=A\nSearch Movie By First Letter=S\n\n");
                        scanf(" %c", &ch2);
                        getchar();

                        if (ch2 == 'a' || ch2 == 'A')
                        {
                            clear();
                            printAllMovies(watchedFile);
                            printf("Thankyou\n");
                            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
                            char ch3;
                            printf("Go to Profile= P\nQuit = Q\nMain Menu= M\n\n");
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
                            else
                            {

                                clear();
                                printf("Invalid choice\n");
                                char retry;
                                printf("Do you want to try again? (Y/N):\n");
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
                        else if (ch2 == 's' || ch2 == 'S')
                        {
                            char al;
                            clear();
                            printf("This is The search bar , Enter First Letter of The Movie\n ");
                            scanf(" %c", &al);
                            getchar();
                            searchMoviesByFirstLetter(watchedFile, al);
                            printf("Thankyou\n");
                            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
                            char ch3;
                            printf("Go to Profile= P\nQuit = Q\nMain Menu= M\n\n");
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
                            else if (ch3 == 'M' || ch3 == 'm')
                            {
                                openProfile(watchedFile, toWatchFile);
                            }
                            else
                            {
                                clear();
                                printf("Invalid choice\n");
                                char retry;
                                printf("Do you want to try again? (Y/N):\n");
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

                        else
                        {
                            clear();
                            printf("Invalid choice\n");
                            char retry;
                            printf("Do you want to try again? (Y/N):\n");
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
                        printf("What do you want to do?\n");
                        printf("See All Watch List=A\nSearch Movie By First Letter=S\n\n");

                        scanf(" %c", &ch2);
                        getchar();

                        if (ch2 == 'a' || ch2 == 'A')
                        {
                            clear();
                            printAllMovies(toWatchFile);
                            printf("Thankyou\n");
                            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
                            char ch3;
                            printf("Go to Profile= P\nQuit = Q\nMain Menu= M\n\n");
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
                            else
                            {
                                printf("Invalid choice\n");
                                char retry;
                                printf("Do you want to try again? (Y/N):\n");
                                scanf(" %c", &retry);
                                getchar();
                                if (retry == 'y' || retry == 'Y')
                                {
                                    continue; // Retry the watched movies section.
                                }
                                else
                                {
                                    return;
                                    // Exit the program.
                                }
                            }
                        }
                        else if (ch2 == 's' || ch2 == 'S')
                        {
                            char al;
                            clear();
                            printf("This is The search bar , Enter First Letter of The Movie\n");
                            scanf(" %c", &al);
                            getchar();
                            searchMoviesByFirstLetter(toWatchFile, al);
                            printf("Thankyou\n");
                            printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
                            char ch3;
                            printf("Go to Profile= P\nQuit = Q\nMain Menu= M\n\n ");
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
                            else
                            {
                                printf("Invalid choice\n");
                                char retry;
                                printf("Do you want to try again? (Y/N):\n");
                                scanf(" %c", &retry);
                                getchar();
                                if (retry == 'y' || retry == 'Y')
                                {
                                    continue; // Retry the watched movies section.
                                }
                                else
                                {
                                    return;
                                    // Exit the program.
                                }
                            }
                        }
                        else
                        {
                            clear();
                            printf("Invalid choice\n");
                            char retry;
                            printf("Do you want to try again? (Y/N):\n");
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
                    printf("Do you want to try again? (Y/N):\n");
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
            printf("Welcome to The Add new movie Section\nThis is where you can add a new movie\n");
            printf("what do you want to do?\n");
            printf("Add to Watched List = W\nAdd to To_Watch List = T\n\n");
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
                printf("Do you want to try again? (Y/N):\n");
                scanf(" %c", &retry);
                getchar();
                if (retry == 'y' || retry == 'Y')
                {
                    continue; // Retry the movie adding section.
                }
            }
            break;

        case 'q':
        case 'Q':
            return;

        default:
            clear();
            printf("Invalid choice\n");
            char retry;
            printf("Do you want to try again? (Y/N):\n");
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
    // Open files for "watched" and "to watch" lists
    watchedFile = fopen("watched.bin", "a+b");
    toWatchFile = fopen("to_watched.bin", "a+b");

    if (watchedFile == NULL || toWatchFile == NULL)
    {
        printf("Couldn't load the app.\n");
        exit(1);
    }

    // Start the application by opening the user's profile
    openProfile(watchedFile, toWatchFile);

    // Close the opened files before exiting the program
    fclose(watchedFile);
    fclose(toWatchFile);

    return 0;
}
