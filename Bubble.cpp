#include <string>
#include <iostream>
#include <ctime>
#include <sstream>
#include "cgame.h"
int main()
{

    cgame game;
    game.makeConsole();
    CHAR_INFO *buffscreen = new CHAR_INFO[s_width * s_height];

    int b = 1;
    int size = s_width - 7;
    int arr[size];
    int n = 0;
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        arr[i] = 2 + rand() % 30;
    }
    int i = 0;
    int j = 0;
    while (1)
    {

        game.fill(buffscreen);

        if (arr[j] < arr[j + 1])
        {
            std::swap(arr[j + 1], arr[j]);
            n++;
        }
        j++;
        if (j > size - 1)
        {
            j = 0;
            i += 1;

            if (i > size - 1)
            {
                i = 0;
                break;
            }
        }
        for (int k = 0; k < size; k++)
            game.Line(k + 3, s_height - 3, k + 3, arr[k], redF, buffscreen);
        game.DrawStringFromInt(48, 1, blueF | whiteB, n, buffscreen);
        game.display(buffscreen);
        Sleep(10);
    }
    game.DrawString(10, 4, blueF | whiteB, L"Sorted", buffscreen);
    for (int k = 0; k < size; k++)
        game.Line(k + 3, s_height - 3, k + 3, arr[k], redF, buffscreen);
    game.display(buffscreen);
}