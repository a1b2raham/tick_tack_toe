#include <stdio.h>
#include <stdbool.h>

int open[9][2];
struct dict
{
    int x;
    int y;
    int score;
};

void print_board(int game[][3])
{
    printf("   0 1 2\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", i);
        printf("|");
        for (int j = 0; j < 3; j++)
        {
            if (game[i][j] == 0)
            {
                printf(" ");
            }
            else if (game[i][j] == 1)
            {
                printf("X");
            }
            else if (game[i][j] == -1)
            {
                printf("O");
            }
            printf("|");
        }
        printf("\n");
    }
}

int chk_win(int game[][3])
{
    for (int i = 0; i < 3; i++)
    {
        if (game[i][0] == game[i][1] && game[i][1] == game[i][2] && game[i][0] != 0)
        {
            return game[i][0];
        }
        if (game[0][i] == game[1][i] && game[1][i] == game[2][i] && game[0][i] != 0)
        {
            return game[0][i];
        }
    }
    if (game[0][0] == game[1][1] && game[1][1] == game[2][2] && game[0][0] != 0)
    {
        return game[0][0];
    }
    if (game[0][2] == game[1][1] && game[1][1] == game[2][0] && game[0][2] != 0)
    {
        return game[0][2];
    }

    return 0;
}

void open_space(int game[][3], int open[][2])
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (game[i][j] == 0)
            {
                open[count][0] = i;
                open[count][1] = j;
                count++;
            }
        }
    }
    for (int i = count; i < 9; i++)
    {
        open[i][0] = -1;
        open[i][1] = -1;
    }
}

int minmax(int game[][3], bool maxp, int depth, struct dict result[])
{
    int chk = chk_win(game);
    if (chk == 1)
    {
        return 10 - depth;
    }
    else if (chk == -1)
    {
        return -10 + depth;
    }
    int open[9][2];
    open_space(game, open);
    if (open[0][0] == -1)
    {
        return 0;
    }

    if (maxp)
    {
        int max = -1000;
        for (int i = 0; i < 9; i++)
        {
            if (open[i][0] == -1)
            {
                break;
            }
            game[open[i][0]][open[i][1]] = 1;
            int a = minmax(game, false, depth + 1, result);

            if (a > max)
            {
                max = a;
            }
            if (depth == 0)
            {
                result[i].x = open[i][0];
                result[i].y = open[i][1];
                result[i].score = a;
            }
            game[open[i][0]][open[i][1]] = 0;
        }
        return max;
    }
    else
    {
        int min = 1000;
        for (int i = 0; i < 9; i++)
        {
            if (open[i][0] == -1)
                break;

            game[open[i][0]][open[i][1]] = -1;
            int a = minmax(game, true, depth + 1, result);
            if (a < min)
                min = a;

            game[open[i][0]][open[i][1]] = 0;
        }
        return min;
    }
}
int main()
{
    struct dict result[20];

    int game[][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    printf("Welcome to Tic Tac Toe\n");
    print_board(game);
    open_space(game, open);

    while (true)
    {

        int x, y;
        int p = 0;
        printf("Enter the row and column number: ");
        scanf("%d %d", &x, &y);
        while (open[p][0] != -1)
        {
            if (open[p][0] == x && open[p][1] == y)
            {
                break;
            }
            p++;
        }
        if (open[p][0] == -1)
        {
            printf("Invalid move\n");
            continue;
        }
        game[x][y] = -1;
        open_space(game, open);

        if (chk_win(game) == -1)
        {
            printf("\nYou win\n");
            break;
        }
        else if (open[0][0] == -1)
        {
            printf("\nIt's a Tie!\n");
            break;
        }
        minmax(game, true, 0, result);
        int small = -1000;
        for (int k = 0; open[k][0] != -1; k++)
        {
            if (result[k].score > small)
            {
                small = result[k].score;
                x = result[k].x;
                y = result[k].y;
            }
        }
        game[x][y] = 1;
        open_space(game, open);
        print_board(game);
        if (chk_win(game) == 1)
        {
            printf("\nYou lost\n");
            break;
        }
    }

    return 0;
}