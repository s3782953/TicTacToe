#include <iostream>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <string>
#include <vector>
#include <random>

class Game
{
    enum class Player
    {
        none = '-',
        player1 = 'X',
        player2 = 'O'
    };

    struct Move
    {
        unsigned int x = 0;
        unsigned int y = 0;
    };

    Player board[3][3];

public:
    Game()
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                board[i][j] = Player::none;
            }
        }
    }

    void printBoard()
    {
        std::cout << "+-----------------+";
        for (unsigned int i = 0; i < 3; i++)
        {
            std::cout << "\n|";
            for (unsigned int j = 0; j < 3; j++)
            {
                std::cout << std::setw(3) << static_cast<char>(board[i][j]) << std::setw(3) << " |";
            }
        }
        std::cout << "\n+-----------------+\n";
    }

    void printHelp()
    {
        std::cout << "\nBoard positions are as follows:\n"
                  << "+--------------------+";
        for (unsigned int i = 0; i < 3; i++)
        {
            std::cout << '\n'
                      << '|';
            for (unsigned int j = 0; j < 3; j++)
            {
                std::cout << std::setw(3) << i << j << std::setw(3) << " |";
            }
        }
        std::cout << '\n'
                  << "+--------------------+\n";
    }

    bool isTie()
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            if (board[i][0] == Player::none || board[i][1] == Player::none || board[i][2] == Player::none)
                return false;
        }
        return true;
    }

    bool checkWin(Player player)
    {
        for (unsigned int i = 0; i < 3; i++)
        {
            // Check horizontals
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
                return true;

            // Check verticals
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
                return true;
        }

        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;

        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;

        return false;
    }

    Move getEasyAiMove()
    {
        std::vector<Move> freePositions;
        Move move;
        Move freePos;
        Move temp;

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    freePos.x = i;
                    freePos.y = j;
                    freePositions.push_back(freePos);
                }
            }
        }

        auto rng = std::default_random_engine{};
        std::shuffle(std::begin(freePositions), std::end(freePositions), rng);
        temp = freePositions.front();
        move.x = temp.x;
        move.y = temp.y;

        return move;
    }

    Move minimax()
    {
        int score = std::numeric_limits<int>::max();
        Move move;

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::player2;

                    int temp = maxSearch();

                    if (temp < score)
                    {
                        score = temp;
                        move.x = i;
                        move.y = j;
                    }
                    board[i][j] = Player::none;
                }
            }
        }

        return move;
    }

    int maxSearch()
    {
        if (checkWin(Player::player1))
        {
            return 10;
        }
        else if (checkWin(Player::player2))
        {
            return -10;
        }
        else if (isTie())
        {
            return 0;
        }

        int score = std::numeric_limits<int>::min();

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::player1;
                    score = std::max(score, minSearch());
                    board[i][j] = Player::none;
                }
            }
        }

        return score;
    }

    int minSearch()
    {
        if (checkWin(Player::player1))
        {
            return 10;
        }
        else if (checkWin(Player::player2))
        {
            return -10;
        }
        else if (isTie())
        {
            return 0;
        }

        int score = std::numeric_limits<int>::max();

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (board[i][j] == Player::none)
                {
                    board[i][j] = Player::player2;
                    score = std::min(score, maxSearch());
                    board[i][j] = Player::none;
                }
            }
        }

        return score;
    }

    void getMove(Player player)
    {
        bool fail = true;
        unsigned int x = -1, y = -1;

        do
        {
            if (player == Player::player1)
                std::cout << "X's Move: ";
            else if (player == Player::player2)
                std::cout << "O's Move: ";

            char c;
            std::cin >> c;
            x = c - '0';
            std::cin >> c;
            y = c - '0';

            fail = board[x][y] != Player::none;

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        } while (fail);
        if (player == Player::player1)
            board[x][y] = Player::player1;
        else if (player == Player::player2)
            board[x][y] = Player::player2;
    }

    void vsComputerHard()
    {
        unsigned int turn = 0;
        bool exit = false;

        printBoard();
        std::cout << "Enter your move with a 0 followed by position example: 05\n";

        do
        {
            // player1 move
            if (turn == 0)
            {
                getMove(Player::player1);

                if (checkWin(Player::player1))
                {
                    printBoard();
                    std::cout
                        << '\n'
                        << "******************\n"
                        << "*     You Win    *\n"
                        << "******************\n"
                        << '\n';
                    exit = true;
                }
            }
            else
            {
                std::cout << "\nComputer Move: ";

                Move aimove = minimax();
                std::cout << aimove.x << aimove.y << "\n";
                board[aimove.x][aimove.y] = Player::player2;

                if (checkWin(Player::player2))
                {
                    printBoard();
                    std::cout
                        << '\n'
                        << "******************\n"
                        << "*  Computer Wins *\n"
                        << "******************\n"
                        << '\n';
                    exit = true;
                }
            }

            if (isTie())
            {
                printBoard();
                std::cout
                    << '\n'
                    << "******************\n"
                    << "*       Tie      *\n"
                    << "******************\n"
                    << '\n';
                exit = true;
            }
            if (!exit)
                printBoard();
            turn ^= 1;

        } while (!exit);
    }

    void vsComputerEasy()
    {
        unsigned int turn = 0;
        bool exit = false;

        printBoard();
        std::cout << "Enter your move as a (row,col). Middle position Example: 11\n";

        do
        {
            // player1 move
            if (turn == 0)
            {
                getMove(Player::player1);

                if (checkWin(Player::player1))
                {
                    printBoard();
                    std::cout
                        << '\n'
                        << "******************\n"
                        << "*     You Win    *\n"
                        << "******************\n"
                        << '\n';
                    exit = true;
                }
            }
            else
            {
                std::cout << "\nComputer Move: ";

                Move aimove = getEasyAiMove();
                std::cout << aimove.x << aimove.y << "\n";
                board[aimove.x][aimove.y] = Player::player2;

                if (checkWin(Player::player2))
                {
                    printBoard();
                    std::cout
                        << '\n'
                        << "******************\n"
                        << "*  Computer Wins *\n"
                        << "******************\n"
                        << '\n';
                    exit = true;
                }
            }

            if (isTie())
            {
                printBoard();
                std::cout
                    << '\n'
                    << "******************\n"
                    << "*       Tie      *\n"
                    << "******************\n"
                    << '\n';
                exit = true;
            }
            if (!exit)
                printBoard();
            turn ^= 1;

        } while (!exit);
    }

    void vsPlayer()
    {
        unsigned int turn = 0;
        bool exit = false;

        printBoard();
        std::cout << "Enter your move as a (row,col). Middle position Example: 11\n";

        do
        {
            // player1 move
            if (turn == 0)
            {
                getMove(Player::player1);

                if (checkWin(Player::player1))
                {
                    printBoard();
                    std::cout
                        << '\n'
                        << "******************\n"
                        << "*  Player 1 Wins *\n"
                        << "******************\n"
                        << '\n';
                    exit = true;
                }
            }
            else
            {
                getMove(Player::player2);

                if (checkWin(Player::player2))
                {
                    printBoard();
                    std::cout
                        << '\n'
                        << "******************\n"
                        << "*  Player 2 Wins *\n"
                        << "******************\n"
                        << '\n';
                    exit = true;
                }
            }

            if (isTie())
            {
                printBoard();
                std::cout
                    << 'n'
                    << "******************\n"
                    << "*       Tie      *\n"
                    << "******************\n"
                    << '\n';
                exit = true;
            }
            if (!exit)
                printBoard();
            turn ^= 1;
        } while (!exit);
    }
};

void returnToMenu()
{
    char input;
    std::cout << "\nPress x to exit or any other key to return to menu:\n";
    std::cin >> input;
    if (input == 'x' || input == 'X')
        exit(EXIT_SUCCESS);
    else
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void menu()
{
    Game tictactoe;
    char selection;
    char subSelection;
    std::cout << "\n Menu";
    std::cout << "\n========";
    std::cout << "\n 1 - VS Human";
    std::cout << "\n 2 - VS Computer";
    std::cout << "\n 3 - Help";
    std::cout << "\n X - Exit";
    std::cout << "\n Enter selection: ";
    // read the input
    std::cin >> selection;
    switch (selection)
    {
    case '1':
    {
        std::cout << "\n VS Human\n";
        tictactoe.vsPlayer();
        returnToMenu();
        menu();
    }
    break;
    case '2':
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "\n VS Computer Menu";
        std::cout << "\n========";
        std::cout << "\n 1 - Easy Mode";
        std::cout << "\n 2 - Hard Mode";
        std::cout << "\n 3 - Help";
        std::cout << "\n 4 - Return to Menu";
        std::cout << "\n X - Exit";
        std::cout << "\n Enter selection: ";
        // read the input
        std::cin >> subSelection;
        switch (subSelection)
        {
        case '1':
        {
            std::cout << "\n VS Computer\n";
            tictactoe.vsComputerEasy();
            returnToMenu();
            menu();
        }
        break;
        case '2':
        {
            std::cout << "\n VS Computer\n";
            tictactoe.vsComputerHard();
            returnToMenu();
            menu();
        }
        break;
        case '3':
        {
            tictactoe.printHelp();
            returnToMenu();
            menu();
        }
        case '4':
        {
            menu();
        }
        case 'X':
        case 'x':
        {
            exit(EXIT_SUCCESS);
        }
        break;
        default:
            std::cout << "\n Invalid selection";
        }
    }
    break;
    case '3':
    {
        tictactoe.printHelp();
        returnToMenu();
        menu();
    }
    case 'X':
    case 'x':
    {
        exit(EXIT_SUCCESS);
    }
    break;
    default:
        std::cout << "\n Invalid selection";
    }
    std::cout << "\n";
}

int main()
{
    menu();
    std::cin.ignore();
}