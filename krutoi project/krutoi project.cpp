#include <iostream>
#include <iomanip>
using namespace std;
const int m = 15;
void fill_board(int board[m][m], int n, int mine);//заполнение поле
void print_board(int board[m][m], int used[m][m], int n);//выводит поле в консоль
void art();//выводит надписть
void recursion(int board[m][m], int used[m][m], int cur_row, int cur_col, int& opened);//открывает соседние нулевые и ненулевые ячейки
int row[] = { -1,-1,-1 ,0,0,1,1,1 };//массив для проверки соседних яччеек
int col[] = { -1,0,1,-1,1,-1,0,1 };//массив для проверки соседних ячеек
int board[m][m];//массив поле
int used[m][m];//массив для хранения открытых ячеек
int main()
{
    char re;
    int opened, n, mines;
    setlocale(0, "ru");
menu://главное меню игры
    system("cls");
    art();
    for (int i = 0; i <= 91; ++i)
    {
        cout << "<>";
        if (i == 45)
        {
            cout << "\n";
            cout << "ИГРАТЬ(p)\nО ИГРЕ(a)\nВЫЙТИ(e)\n";
        }
    }
    cout << "\nВаше действие: ";
    cin >> re;

    if (re == 'p' or re == 'e' or re == 'a')
    {
        if (re == 'p')
        {
            goto new_game;
        }
        if (re == 'a')
        {
            system("cls");
            art();
            for (int i = 0; i <= 91; ++i)
            {
                cout << "<>";
                if (i == 45)
                {
                    cout << "\nО ИГРЕ\n";
                    cout << "Цель игры: открыть все безопасные клетки и не попасть на мину\n";
                    cout << "x - неоткрытые клетки (в которых может быть мина или безоппасное место)\n";
                    cout << "9 - мина, если её открыть, игра закончится\n";
                    cout << "0 - пустое место\n";
                    cout << "1-6 - цифра показывает на количество мин вокруг неё\n";
                }
            }
            cout << "\n";
            system("PAUSE");
            goto menu;
        }
        else
        {
            goto exit;
        }
    }
    else
    {
        cout << "\n\nНеподходящее действие, попробуйте ещё раз. \n\n";
        system("PAUSE");
        goto menu;
    }
new_game://запускает новую игру
    system("cls");
    art();
    for (int i = 0; i <= 91; ++i)
    {
        cout << "<>";
        if (i == 45)
        {
            cout << "\nВЫБИРИТЕ СЛОЖНОСТЬ\n";
            cout << "EASY(e) - поле 9х9, 6 мин\n";
            cout << "MEDIUM(m) - поле 9х9, 10 мин\n";
            cout << "HARD(h) - поле 11х11, 16 мин\n";
            cout << "CUSTOM(c) - на выбор игрока\n";
        }
    }
    cout << "\n";
    cin >> re;
    switch (re)
    {
    case'e': n = 11; mines = 6; break;
    case'm':n = 11; mines = 10; break;
    case'h':n = 13; mines = 16; break;
    case'c':system("cls");
        art();
        for (int i = 0; i <= 91; ++i)
        {
            cout << "<>";
            if (i == 45)
            {
                cout << "\nВЫБЕРИТЕ КОЛИЧЕСТВО СТРОК И МИН\n";
                cout << "НЕ БОЛЬШЕ 13 СТРОК И НЕ МЕНЬШЕ 2\n";
                cout << "НЕ БОЛЬШЕ 30 МИН И НЕ МЕНЬШЕ ОДНОЙ\n";
            }
        }
        cout << "\nКоличество строк: ";
        cin >> n;
        cout << "Количество мин: ";
        cin >> mines;
        if (n > 13 or mines > 30 or n < 2 or mines < 1)
        {
            cout << "\n\nНеподходящее действие, попробуйте ещё раз. \n\n";
            system("PAUSE"); goto new_game;
        }
        else
        {
            n += 2;
        }
        break;
    default:cout << "\n\nНеподходящее действие, попробуйте ещё раз. \n\n";
        system("PAUSE"); goto new_game;
        break;
    }
    system("cls");
    cout << "НОВАЯ ИГРА!\n";
    int cur_row, cur_col;
    bool valid;
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            board[i][j] = 0;
        }
    }
    for (int i = 0; i <= n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {

            used[i][j] = 0;

        }
    }
    fill_board(board, n, mines);
    opened = 0;
again://новый ход
    system("cls");
    print_board(board, used, n);
    cur_row = 0, cur_col = 0;
    valid = false;
    while (!valid)
    {
        cout << "Введите свое действие: \n";
        cout << "Введите строку -> ";
        cin >> cur_row;
        cout << "Введите колонку -> ";
        cin >> cur_col;
        if (cur_row > n - 2 || cur_row < 1 || cur_col>n - 2 || cur_col < 1 || used[cur_row][cur_col] == 1)//проверяет в рамках ли ход
        {
            cout << "\n\nНеподходящее действие, попробуйте ещё раз. \n\n";
            system("PAUSE");
            goto again;
        }
        else
        {
            valid = true;
        }
    }
    if (board[cur_row][cur_col] == 9)//проигрыш
    {
        system("cls");
        cout << "      ВЫ ПРОИГРАЛИ! \n";
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                used[i][j] = 1;
            }
        }
        print_board(board, used, n);
        cout << "ПОВТОРИТЬ? \n";
        cout << "ДА(y)\n";
        cout << "НЕТ(n)\n";
        cin >> re;
        if (re == 'y' or re == 'n')
        {
            if (re == 'n')
            {
                goto menu;
            }
            else
            {
                goto new_game;
            }
        }
        else
        {
            goto menu;
        }
    }
    else if (board[cur_row][cur_col] == 0)//переодресация на открытие ячеек
    {
        recursion(board, used, cur_row, cur_col, opened);
    }
    else
    {
        used[cur_row][cur_col] = 1;
        opened++;
    }
    if (opened == (n - 2) * (n - 2) - mines)//победа
    {
        system("cls");
        cout << "      ВЫ ПОБЕДИЛИ!\n";
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                used[i][j] = 1;
            }
        }
        print_board(board, used, n);
        cout << "ПРОВТОРИТЬ? \n";
        cout << "ДА(y)\n";
        cout << "НЕТ(n)\n";
        cin >> re;
        if (re == 'y' or re == 'n')
        {
            if (re == 'n')
            {
                goto menu;
            }
            else
            {
                goto new_game;
            }
        }
        else
        {
            goto menu;
        }
    }
    goto again;
exit: return 0;
}
void fill_board(int board[m][m], int n, int mine)
{
    for (int i = 0; i < n; ++i)//создает края
    {
        board[0][i] = -1;
        board[i][0] = -1;
        board[n - 1][i] = -1;
        board[i][n - 1] = -1;
    }

    srand(time(0));
    int mines = 0;
    while (mines < mine)//создает мины
    {
        int x = rand() % (n - 2) + 1;
        int y = rand() % (n - 2) + 1;//случайное расположение мины
        if (board[x][y] != 9)
        {
            board[x][y] = 9;
            for (int i = 0; i < 8; ++i)
            {
                if (board[x + row[i]][y + col[i]] != -1 && board[x + row[i]][y + col[i]] != 9)
                {
                    board[x + row[i]][y + col[i]]++;//ставит цифры около мин
                }
            }
            mines++;
        }
    }
}
void print_board(int board[m][m], int used[m][m], int n)
{
    cout << "   ";
    for (int i = 1; i <= n - 2; i++)//выводит номера столбцов
    {
        cout << setw(2) << i;
    }
    cout << "\n";
    for (int i = 1; i <= n - 2; ++i)
    {
        cout << setw(2) << i << "|";//выводит номера строк
        for (int j = 1; j <= n - 2; ++j)
        {
            if (used[i][j] == 1)
            {
                cout << setw(2) << board[i][j]; //выводит открытые ячейки           
            }
            else
            {
                cout << setw(2) << "x";//выводит закрытые ячейки
            }
        }
        cout << "\n";
    }
}

void recursion(int board[m][m], int used[m][m], int cur_row, int cur_col, int& opened)//открывает соседние ячейки
{
    used[cur_row][cur_col] = 1;
    opened++;
    for (int i = 0; i < 8; ++i)
    {
        if (used[cur_row + row[i]][cur_col + col[i]] != 1)
        {
            if (board[cur_row + row[i]][cur_col + col[i]] > 0 and board[cur_row + row[i]][cur_col + col[i]] < 9)
            {
                used[cur_row + row[i]][cur_col + col[i]] = 1;
                opened++;
            }
            else
            {
                if (board[cur_row + row[i]][cur_col + col[i]] == 0)
                {
                    recursion(board, used, cur_row + row[i], cur_col + col[i], opened);
                }
            }
        }

    }
}
void art()
{
    string input;
    input = "minesweeper";
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i] == 'a')
            cout << "  ___   ";
        if (input[i] == 'E' || input[i] == 'e')
            cout << " _____  ";
        if (input[i] == 'I' || input[i] == 'i')
            cout << " _____  ";
        if (input[i] == 'M' || input[i] == 'm')
            cout << " __  __  ";
        if (input[i] == 'N' || input[i] == 'n')
            cout << " _   _  ";
        if (input[i] == 'P' || input[i] == 'p')
            cout << " _____  ";
        if (input[i] == 'R' || input[i] == 'r')
            cout << " _____  ";
        if (input[i] == 'S' || input[i] == 's')
            cout << " _____  ";
        if (input[i] == 'W' || input[i] == 'w')
            cout << " _    _  ";
        if (input[i] == 'U' || input[i] == 'u')
            cout << " _   _  ";

    }
    cout << endl;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i] == 'a')
            cout << " / _ \\  ";
        if (input[i] == 'E' || input[i] == 'e')
            cout << "|  ___| ";
        if (input[i] == 'I' || input[i] == 'i')
            cout << "|_   _| ";
        if (input[i] == 'M' || input[i] == 'm')
            cout << "|  \\/  | ";
        if (input[i] == 'N' || input[i] == 'n')
            cout << "| \\ | | ";
        if (input[i] == 'P' || input[i] == 'p')
            cout << "| ___ \\ ";
        if (input[i] == 'R' || input[i] == 'r')
            cout << "| ___ \\ ";
        if (input[i] == 'S' || input[i] == 's')
            cout << "/  ___| ";
        if (input[i] == 'W' || input[i] == 'w')
            cout << "| |  | | ";
        if (input[i] == 'U' || input[i] == 'u')
            cout << "| | | | ";
    }
    cout << endl;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i] == 'a')
            cout << "/ /_\\ \\ ";
        if (input[i] == 'E' || input[i] == 'e')
            cout << "| |__   ";
        if (input[i] == 'I' || input[i] == 'i')
            cout << "  | |   ";
        if (input[i] == 'M' || input[i] == 'm')
            cout << "| .  . | ";
        if (input[i] == 'N' || input[i] == 'n')
            cout << "|  \\| | ";
        if (input[i] == 'P' || input[i] == 'p')
            cout << "| |_/ / ";
        if (input[i] == 'R' || input[i] == 'r')
            cout << "| |_/ / ";
        if (input[i] == 'S' || input[i] == 's')
            cout << "\\ `--.  ";
        if (input[i] == 'W' || input[i] == 'w')
            cout << "| |  | | ";
        if (input[i] == 'U' || input[i] == 'u')
            cout << "| | | | ";
    }
    cout << endl;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i] == 'a')
            cout << "|  _  | ";
        if (input[i] == 'E' || input[i] == 'e')
            cout << "|  __|  ";
        if (input[i] == 'I' || input[i] == 'i')
            cout << "  | |   ";
        if (input[i] == 'M' || input[i] == 'm')
            cout << "| |\\/| | ";
        if (input[i] == 'N' || input[i] == 'n')
            cout << "| . ` | ";
        if (input[i] == 'P' || input[i] == 'p')
            cout << "|  __/  ";
        if (input[i] == 'R' || input[i] == 'r')
            cout << "|    /  ";
        if (input[i] == 'S' || input[i] == 's')
            cout << " `--. \\ ";
        if (input[i] == 'W' || input[i] == 'w')
            cout << "| |/\\| | ";
        if (input[i] == 'U' || input[i] == 'u')
            cout << "| | | | ";
    }
    cout << endl;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i] == 'a')
            cout << "| | | | ";
        if (input[i] == 'E' || input[i] == 'e')
            cout << "| |___  ";
        if (input[i] == 'I' || input[i] == 'i')
            cout << " _| |_  ";
        if (input[i] == 'M' || input[i] == 'm')
            cout << "| |  | | ";
        if (input[i] == 'N' || input[i] == 'n')
            cout << "| |\\  | ";
        if (input[i] == 'P' || input[i] == 'p')
            cout << "| |     ";
        if (input[i] == 'R' || input[i] == 'r')
            cout << "| |\\ \\  ";
        if (input[i] == 'W' || input[i] == 'w')
            cout << "\\  /\\  / ";
        if (input[i] == 'S' || input[i] == 's')
            cout << "/\\__/ / ";
        if (input[i] == 'U' || input[i] == 'u')
            cout << "| |_| | ";
    }
    cout << endl;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == 'A' || input[i] == 'a')
            cout << "\\_| |_/ ";
        if (input[i] == 'E' || input[i] == 'e')
            cout << "\\____/  ";
        if (input[i] == 'I' || input[i] == 'i')
            cout << " \\___/  ";
        if (input[i] == 'M' || input[i] == 'm')
            cout << "\\_|  |_/ ";
        if (input[i] == 'N' || input[i] == 'n')
            cout << "\\_| \\_/ ";
        if (input[i] == 'P' || input[i] == 'p')
            cout << "\\_|     ";
        if (input[i] == 'R' || input[i] == 'r')
            cout << "\\_| \\_| ";
        if (input[i] == 'S' || input[i] == 's')
            cout << "\\____/  ";
        if (input[i] == 'W' || input[i] == 'w')
            cout << " \\/  \\/  ";
        if (input[i] == 'U' || input[i] == 'u')
            cout << " \\___/  ";
    }
    cout << endl;
}