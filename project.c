#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("couldn't load app");
        exit(1);
    }
there:
    
    printf("WElCOME TO WATCHLIST\n");
    printf("To open your profile type 'p', to add new movie or series type 'n': ");
    int found=0;
    ch1 = getchar();
    switch (ch1)
    {
    case 'p':
    case 'P':
        yes:
        printf("Welcome to the profile Section\n");
        printf("Enter W to see watched and Enter T to see to Watch movie ");
        scanf(" %c", &ch2);
        getchar();
        
        if (ch2 == 'w' || ch2 == 'W')
        {   again:
            rewind(data);
            printf("This is watched movie section\n");
            printf("Wanna see all list or search according to your own preference for all enter A for search Enter S:  ");
            scanf(" %c", &ch4);
            getchar();
            if (ch4 == 'a' || ch4 == 'A')
            {   int count=0;
                while ((fread(&m, sizeof(movie), 1, data)) == 1)
                {
                    printf("Name=%sRating=%.2f\nGenre=%s\n", m.name, m.rating, m.genre);
                    count++;
                }
                if (count==0)
                {
                    printf("the list is empty try adding new movie from movie adding option\n");
                }
                 printf("to again go back to main menu enter M to exit enter anything except M:  ");
            scanf(" %c", &ch3);
            getchar();
            if (ch3 == 'm' || ch3 == 'M')
                goto there;
            else{printf("Thank you for using our app\n");
                return 0;}

            }
            else if (ch4 == 'S' || ch4 == 's')
            {
                printf("We have sorted movie in alphabetically order to find type first letter of movie: ");
                scanf(" %c", &al);
                getchar();
                while ((fread(&m, sizeof(movie), 1, data)) == 1)
                {
                    if (m.name[0] == al)
                        found=1;
                        printf("Name=%sRating=%.2f\nGenre=%s\n", m.name, m.rating, m.genre);
                }
                if(found==0)
                {
                    printf("No movie found with that letter\n");
                }
            }
            else{
                printf("Invalid choices");
                printf("choose again\n");
                goto again;}
                 printf("to again go back to main menu enter M to exit enter anything except M:  ");
            scanf(" %c", &ch3);
            getchar();
            if (ch3 == 'm' || ch3 == 'M')
                goto there;
        else{
                printf("Thank you for using our app\n");
                return 0;}
        }

        else if (ch2 == 'T' || ch2 == 't')

        {   mere:
            rewind(data2);
            printf("This is to_watched movie section\n");
            printf("Wanna see all list or search according to your own preference for all enter A for search Enter S:  ");
            scanf(" %c", &ch4);
            getchar();
            if (ch4 == 'a' || ch4 == 'A')
            {   int count=0;
                while ((fread(&m, sizeof(movie), 1, data2)) == 1)
                {
                    printf("Name=%sRating=%.2f\nGenre=%s\n", m.name, m.rating, m.genre);
                    count++;
                }
                if (count==0)
                {
                    printf("the list is empty try adding new movie from movie adding option\n");
                }
                 printf("to again go back to main menu enter M to exit enter anything except M:  ");
            scanf(" %c", &ch3);
            getchar();
            if (ch3 == 'm' || ch3 == 'M')
                goto there;
            else{
                printf("Thank you for using our app\n");
                    return 0;}
            }
            else if (ch4 == 'S' || ch4 == 's')
            {
                printf("We have sorted movie in alphabetically order to find type first letter of movie: ");
                scanf(" %c", &al);
                getchar();
                while ((fread(&m, sizeof(movie), 1, data2)) == 1)
                {
                    if (m.name[0] == al)
                        printf("Name=%sRating=%.2f\nGenre=%s\n", m.name, m.rating, m.genre);
                        found=1;
                }
                if(found==0)
                {
                    printf("No movie found with that letter\n");
                }
            }
            else{
                printf("Invalid choices\n");
                printf("choose again\n");
                goto mere;}
            printf("to again go back to main menu enter M to exit enter anything except M:  ");
            scanf(" %c", &ch3);
            getchar();
            if (ch3 == 'm' || ch3 == 'M')
                goto there;
            else{
                printf("Thankyou for using our app\n");
                return 0;}
        }
        else
        {
            printf("Invalid choice\n");
            printf("choose again\n");
            goto yes;
        }
        break;

    case 'n':
    case 'N':
    {   here:
        printf("This is where you can add new movie\n");
        printf("Enter W to add in watched and Enter T to add to To_Watch movie:  ");
        scanf(" %c", &ch2);
        getchar();
        if (ch2 == 'W' || ch2 == 'w')
        {
            rewind(data2);
            printf("Welcome to the place where you can add movie to watched section\n");
            do
            {
                printf("Add movie name you want to add: ");
                fgets(m.name, sizeof(m.name), stdin);
                printf("Enter genre of the movie: ");
                fgets(m.genre, sizeof(m.genre), stdin);
                printf("Enter the rating: ");
                scanf("%f", &m.rating);
                fwrite(&m, sizeof(movie), 1, data);
                printf("Want to add another movie Y/N:  ");
                scanf(" %c", &ch3);
                getchar();
            } while (ch3 == 'y' || ch3 == 'Y');
            printf("to again go back to main menu enter M to exit enter anything except M:  ");
            scanf(" %c", &ch3);
            getchar();
            if (ch3 == 'm' || ch3 == 'M')
                goto there;
            else{
                printf("Thank you for using our app\n");
                return 0;}
        }

        else if (ch2 == 't' || ch2 == 'T')
        {
            rewind(data2);
            printf("Welcome to the place where you can add movie to to_watched section\n");
            do
            {
                printf("Add movie name you want to add: ");
                fgets(m.name, sizeof(m.name), stdin);
                printf("Enter genre of the movie: ");
                fgets(m.genre, sizeof(m.genre), stdin);
                printf("Enter the rating: ");
                scanf("%f", &m.rating);
                fwrite(&m, sizeof(movie), 1, data2);
                printf("Want to add another movie Y/N:  ");
                scanf(" %c", &ch3);
                getchar();
            } while (ch3 == 'y' || ch3 == 'Y');
            printf("to again go back to main menu enter M to exit enter anything except M:  ");
            scanf(" %c", &ch3);
            getchar();
            if (ch3 == 'm' || ch3 == 'M')
                goto there;
            else{
                printf("Thank you for using our app\n");
                return 0;}
        }
        else
        {  
            printf("Invalid choices\n");
            printf("choose again");
            goto here;
        }

        break;
    }

    default:
        printf("Invalid choice");
        printf("Choose again");
        goto there;
    }
    
    fclose(data);
    fclose(data2);
    return 0;
}
