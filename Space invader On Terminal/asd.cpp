#include <iostream>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include <time.h> //  for random number
using namespace std;

void loadData();
void storeData();
void printMap();
void gotoxy(int x, int y);
void Header();
int options();   // two areanas
void gameOver(); // Game end.

//--------------------------------------DISPLAYING ON SCREEN------------------------------------
void DisplayHealth();
void DisplayScore();
void DisplayLives();
void DisplaySpaceship(int); // int here detemines direction

//-------------------------------------------SPACESHIP------------------------------------------
void spaceshipHealh();
void spaceshipMoveLeft();
void spaceshipMoveRight();
void spaceshipLaser();
void shootLaser(int n);
void moveLasers(); // use the gravity algorithm

//---------------------------------------------ALIENS-------------------------------------------
void alien1Horizontal1();
void alien2Horizontal1();
void Rip_alien(int, int);
void alien1Lasers();
void alien2Lasers();
void aliensLasersMovement();
void UFOmovement(); // Random Appearance
void UFOlaser();
void UfoLaserMovement();
void eraseEnemy(int x, int y); // Erases UFO
int RandomRow();
int RandomCol(int n);

//-----------------------------------------DATA STRUCTURES-------------------------------------
char map[45][156];
char spaceship[7][11];
char alien1[5][11];
char alien2[4][10];
char alien2A[4][10]; // 2nd animation
char UFO[4][16];

bool ch = false, run = false, Running = true;
int sX = 34, sY = 73;
int alienX1 = 3, alienY1 = 3, a1way = 1;
int alienX2 = 9, alienY2 = 36;
int n = 0, count = 0, speed = 0, g = 0, t = 0;
int Score = 0, lives = 2, health = 100, hp_1 = 100, hp_2 = 100, hp_3 = 100, hp_4 = 100, hp_5 = 100;
bool Alive_1 = true, Alive_2 = true, Alive_3 = true, Alive_4 = true, Alive_5 = true;

main()
{
    srand(time(0));
    Header();
    int option = options();

    loadData();
    system("cls");
    printMap();

    DisplaySpaceship(0);
    DisplayHealth();
    DisplayLives();
    DisplayScore();

    if (option == 1)
    {
        while (!GetAsyncKeyState(VK_ESCAPE) && lives >= 0 && Running == true)
        {
            count += 10;
            speed++;
            n++;
            alien1Horizontal1();
            alien2Horizontal1();

            if (GetAsyncKeyState(VK_LEFT))
            {
                spaceshipMoveLeft();
                count += 50;
                // speed=0;
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
                spaceshipMoveRight();
                count += 50;
                // speed=0;
            }
            else if (GetAsyncKeyState(VK_SPACE) && speed >= 50)
            {
                shootLaser(n);
                count += 50;
                speed = 0;
            }
            else if (GetAsyncKeyState(VK_END))
            {
                storeData();
                break;
            }

            if (n > 50)
            {
                alien1Lasers();
                alien2Lasers();
                n = 0;
            }
            if (count >= 100)
            {
                count = 0;
                moveLasers();
                aliensLasersMovement();
            }
            spaceshipHealh();
            Running = Alive_1 || Alive_2 || Alive_3 || Alive_4 || Alive_5;
        }
    }
    else if (option == 2)
    {
        while (!GetAsyncKeyState(VK_ESCAPE) && lives >= 0 && Running == true)
        {
            count += 10;
            speed++;
            n++;
            t++;

            if (t > 100)
            {
                eraseEnemy(alienX1, alienY1);
                if (Alive_3 == true)
                {
                    eraseEnemy(alienX2, alienY2);
                }
            }
            UFOmovement();

            if (GetAsyncKeyState(VK_LEFT))
            {
                spaceshipMoveLeft();
                count += 50;
                // speed=0;
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
                spaceshipMoveRight();
                count += 50;
                // speed=0;
            }
            else if (GetAsyncKeyState(VK_SPACE) && speed >= 50)
            {
                shootLaser(n);
                count += 50;
                speed = 0;
            }

            if (n > 50)
            {
                UFOlaser();
                n = 0;
            }
            if (count >= 100)
            {
                count = 0;
                moveLasers();
                UfoLaserMovement();
            }
            spaceshipHealh();
            Running = Alive_1 || Alive_2 || Alive_3;
        }
    }

    system("cls");
    gameOver();
}

void loadData()
{
    fstream file;
    int temp;

    if (ch == 0)
    {
        file.open("D:\\Space invader\\Document\\map.txt", ios::in);
    }
    else
    {
        file.open("D:\\Space invader\\Document\\LastSaved.txt", ios::in);
        file >> sX;
        file >> sY;
        file >> alienX1;
        file >> alienY1;
        file >> alienX2;
        file >> alienY2;
        file >> hp_1;
        file >> Alive_1;
        file >> hp_2;
        file >> Alive_2;
        file >> hp_3;
        file >> Alive_3;
        file >> hp_4;
        file >> Alive_4;
        file >> hp_5;
        file >> Alive_5;
        file >> health;
        file >> Score;
        file >> lives;
    }

    for (int i = 0; i < 45; i++)
    {
        for (int j = 0; j < 156; j++)
        {
            file >> temp;
            map[i][j] = temp;
        }
    }
    file.close();

    file.open("D:\\Space invader\\Document\\Spaceship.txt", ios::in);
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            file >> temp;
            spaceship[i][j] = temp;
        }
    }
    file.close();

    file.open("D:\\Space invader\\Document\\Alien1.txt", ios::in);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            file >> temp;
            alien1[i][j] = temp;
        }
    }
    file.close();

    file.open("D:\\Space invader\\Document\\Alien2.txt", ios::in);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            file >> temp;
            alien2[i][j] = temp;
        }
    }
    file.close();

    file.open("D:\\Space invader\\Document\\Alien2A.txt", ios::in);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            file >> temp;
            alien2A[i][j] = temp;
        }
    }
    file.close();

    file.open("D:\\Space invader\\Document\\UFO.txt", ios::in);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            file >> temp;
            UFO[i][j] = temp;
        }
    }
    file.close();
}

void storeData()
{
    fstream file;

    file.open("D:\\Space invader\\Document\\LastSaved.txt", ios::out);
    file << sX << ' ' << sY << ' ' << alienX1 << ' ' << alienY1 << ' ' << alienX2 << ' ' << alienY2 << ' ' << hp_1 << ' ' << Alive_1 << ' ' << hp_2 << ' ' << Alive_2 << ' ' << hp_3 << ' ' << Alive_3 << ' ' << hp_4 << ' ' << Alive_4 << ' ' << hp_5 << ' ' << Alive_5 << ' ' << health << ' ' << Score << ' ' << lives;

    for (int i = 0; i < 45; i++)
    {
        file << endl;
        for (int j = 0; j < 156; j++)
        {
            file << int(map[i][j]);
            if (j != 155)
            {
                file << ' ';
            }
        }
    }
    file.close();
}

void Header()
{
    char d = 15;

    system("cls");
    cout << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << endl;
    cout << ' ' << ' ' << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << endl;
    cout << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << " SPACE INVADER " << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << endl;
    cout << ' ' << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << endl;
    cout << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << d << endl;
}

int options()
{
    cout << "\n\t1. Arena1.";
    cout << "\n\t2. Arena2.";

    cout << "\n\n\tSelect your option : ";
    char opt = getch();

    while ((int(opt) - 48) < 1 || (int(opt) - 48) > 2)
    {
        cout << "Invalid! Input Again : ";
        opt = getch();
    }

    if (int(opt) - 48 == 1)
    {
        Header();
        cout << "\n\tLoad Last Saved Game : ";
        char optt = getch();

        if (int(optt) - 48 == 1)
        {
            ch = 1;
        }
    }

    return (int(opt) - 48);
}

void printMap()
{
    for (int i = 0; i < 45; i++)
    {
        for (int j = 0; j < 156; j++)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
}

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void gameOver()
{
    if (Running == true)
    {
        gotoxy(70, 20);
        cout << "GAME OVER";
    }
    else
    {
        gotoxy(70, 20);
        cout << "YOU DID IT!";
    }
    getch();
    getch();
    getch();
    getch();
    getch();
    getch();
}

void DisplaySpaceship(int check)
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            gotoxy(sY + j, sX + i);
            cout << spaceship[i][j];
        }
        if (check == 1)
        {
            gotoxy(sY - 1, sX + i);
        }

        cout << ' ';
        cout << endl;
    }
}

void DisplayHealth()
{
    if (run == 0)
    {
        gotoxy(165, 10);
        cout << "------------------------";
        gotoxy(170, 12);
        cout << "Health : ";
        gotoxy(165, 14);
        cout << "------------------------";

        gotoxy(165, 20);
        cout << "------------------------";
        gotoxy(170, 22);
        cout << "Score : ";
        gotoxy(165, 24);
        cout << "------------------------";

        gotoxy(165, 30);
        cout << "------------------------";
        gotoxy(170, 32);
        cout << "Lives : ";
        gotoxy(165, 34);
        cout << "------------------------";
        run = 1;
    }

    gotoxy(178, 12);
    cout << health << "  ";
}

void DisplayScore()
{
    gotoxy(178, 22);
    cout << Score;
}

void DisplayLives()
{
    gotoxy(178, 32);

    if (lives == 2)
    {
        cout << "\3 \3 \3";
    }
    else if (lives == 1)
    {
        cout << "\3 \3   ";
    }
    else if (lives == 0)
    {
        cout << "\3      ";
    }
}

void spaceshipMoveLeft()
{
    if (sY > 3)
    {
        sY--;
        DisplaySpaceship(0);
    }
}

void spaceshipMoveRight()
{
    if (sY < 142)
    {
        sY++;
        DisplaySpaceship(1);
    }
}

void spaceshipHealh()
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (spaceship[i][j] != ' ' && map[sX + i][sY + j] == char(157))
            {
                health -= 20;
                DisplayHealth();
                gotoxy(sY + j, sX + i);
                cout << spaceship[i][j];
                map[sX + i][sY + j] = ' ';
            }
        }
    }
    if (health <= 0)
    {
        lives--;

        if (lives >= 0)
        {
            gotoxy(20, 30);
            cout << "Press any key to Continue : ";
            getch();
            getch();
            gotoxy(20, 30);
            cout << "                                      ";
        }

        health = 100;
        DisplayHealth();
        DisplayLives();
    }
}

void alien1Horizontal1()
{
    if (Alive_1 || Alive_2)
    {
        alienY1 += a1way;
        for (int i = 0; i < 5; i++)
        {
            if (Alive_1 != false)
            {
                gotoxy(alienY1 - a1way, alienX1 + i);
                if (a1way == -1)
                {
                    gotoxy(alienY1 + 11, alienX1 + i);
                }
                cout << ' ';
            }

            if (Alive_2 != false)
            {
                gotoxy(alienY1 - a1way + 70, alienX1 + i);
                if (a1way == -1)
                {
                    gotoxy(alienY1 + 81, alienX1 + i);
                }
                cout << ' ';
            }

            for (int j = 0; j < 11; j++)
            {
                if (Alive_1 != false)
                {
                    gotoxy(alienY1 + j, alienX1 + i);
                    cout << alien1[i][j];

                    if (alien1[i][j] != ' ' && map[alienX1 + i][alienY1 + j] == char(177))
                    {
                        hp_1 -= 20;
                        map[alienX1 + i][alienY1 + j] = ' ';
                    }

                    if (hp_1 <= 0)
                    {
                        Alive_1 = false;
                        Score += 200;
                        DisplayScore();
                        Rip_alien(alienX1, alienY1);
                    }
                }

                if (Alive_2 != false)
                {
                    gotoxy(alienY1 + j + 70, alienX1 + i);
                    cout << alien1[i][j];

                    if (alien1[i][j] != ' ' && map[alienX1 + i][alienY1 + j + 70] == char(177))
                    {
                        hp_2 -= 20;
                        map[alienX1 + i][alienY1 + j + 70] = ' ';
                    }

                    if (hp_2 <= 0)
                    {
                        Alive_2 = false;
                        Score += 200;
                        DisplayScore();
                        Rip_alien(alienX1, alienY1 + 70);
                    }
                }
            }
        }
        gotoxy(0, 1);

        if (alienY1 < 4 || alienY1 > 70)
        {
            a1way = a1way * -1;
        }
    }
}

void alien2Horizontal1()
{
    if (Alive_3 || Alive_4 || Alive_5)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (Alive_3 != false)
                {
                    gotoxy(alienY2 + j, alienX2 + i);
                    cout << alien2[i][j];

                    if (alien2[i][j] != ' ' && map[alienX2 + i][alienY2 + j] == char(177))
                    {
                        hp_3 -= 34;
                        map[alienX2 + i][alienY2 + j] = ' ';
                    }

                    if (hp_3 <= 0)
                    {
                        Alive_3 = false;
                        Score += 100;
                        DisplayScore();
                        Rip_alien(alienX2, alienY2);
                    }
                }

                if (Alive_4 != false)
                {
                    gotoxy(alienY2 + j + 38, alienX2 + i);
                    cout << alien2A[i][j];

                    if (alien2[i][j] != ' ' && map[alienX2 + i][alienY2 + j + 38] == char(177))
                    {
                        hp_4 -= 34;
                        map[alienX2 + i][alienY2 + j + 38] = ' ';
                    }

                    if (hp_4 <= 0)
                    {
                        Alive_4 = false;
                        Score += 100;
                        DisplayScore();
                        Rip_alien(alienX2, alienY2 + 38);
                    }
                }

                if (Alive_5 != false)
                {
                    gotoxy(alienY2 + j + 76, alienX2 + i);
                    cout << alien2[i][j];

                    if (alien2[i][j] != ' ' && map[alienX2 + i][alienY2 + j + 76] == char(177))
                    {
                        hp_5 -= 34;
                        map[alienX2 + i][alienY2 + j + 76] = ' ';
                    }

                    if (hp_5 <= 0)
                    {
                        Alive_5 = false;
                        Score += 100;
                        DisplayScore();
                        Rip_alien(alienX2, alienY2 + 76);
                    }
                }
            }
        }
    }
    gotoxy(0, 1);
}

void Rip_alien(int x, int y)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = -1; j < 12; j++)
        {
            gotoxy(y + j, x + i);
            cout << ' ';
            map[x + i][y + j] = ' ';
        }
    }
}

void spaceshipLaser()
{
    gotoxy(sY, sX);
    for (int i = 0; sX - i > 2; i++)
    {
        Sleep(100);
        gotoxy(sY, sX - i);
        cout << char(177);
        gotoxy(sY, sX - i + 1);
        cout << ' ';
    }
}

void shootLaser(int n)
{
    gotoxy(sY + 5, sX - 2);
    cout << char(177);
    map[sX - 2][sY + 5] = char(177);
}

void moveLasers()
{
    char c = 177, previousItem;
    int move;
    for (int i = 5; i < 37; i++)
    {
        for (int j = 4; j < 150; j++)
        {
            if (map[i][j] == c)
            {
                move = 2;
                previousItem = map[i - move][j];
                map[i - move][j] = map[i][j];
                map[i][j] = previousItem;
                gotoxy(j, i);
                cout << map[i][j];
                gotoxy(j, i - move);
                cout << map[i - move][j];
            }
        }
    }

    for (int j = 4; j < 150; j++)
    {
        if (map[4][j] == c)
        {
            gotoxy(j, 4);
            cout << ' ';
            map[4][j] = ' ';
        }
    }
}

void alien1Lasers()
{
    if (hp_1 > 0)
    {
        gotoxy(alienY1 + 5, alienX1 + 7);
        cout << char(157);
        map[alienX1 + 7][alienY1 + 5] = char(157);
    }

    if (hp_2 > 0)
    {
        gotoxy(alienY1 + 5 + 70, alienX1 + 7);
        cout << char(157);
        map[alienX1 + 7][alienY1 + 5 + 70] = char(157);
    }
}

void alien2Lasers()
{
    if (hp_3 > 0)
    {
        gotoxy(alienY2 + 5, alienX2 + 5);
        cout << char(157);
        map[alienX2 + 5][alienY2 + 5] = char(157);
    }

    if (hp_4 > 0)
    {
        gotoxy(alienY2 + 5 + 38, alienX2 + 5);
        cout << char(157);
        map[alienX2 + 5][alienY2 + 5 + 38] = char(157);
    }

    if (hp_5 > 0)
    {
        gotoxy(alienY2 + 5 + 76, alienX2 + 5);
        cout << char(157);
        map[alienX2 + 5][alienY2 + 5 + 76] = char(157);
    }
}

void aliensLasersMovement()
{
    char d = 157, previousItem;
    for (int i = 37; i > 5; i--)
    {
        for (int j = 4; j < 150; j++)
        {
            if (map[i][j] == d)
            {
                previousItem = map[i + 2][j];
                map[i + 2][j] = map[i][j];
                map[i][j] = previousItem;
                gotoxy(j, i);
                cout << map[i][j];
                gotoxy(j, i + 2);
                cout << map[i + 2][j];
            }
            // else if(i<34 && (map[i][j]==char(173) || map[i][j]==char(215) || map[i][j]==char(214) || map[i][j]==char(206) || map[i][j]==char(204)|| map[i][j]==char(185) || map[i][j]==char(219))){
            //     cout<<' ';
            //     map[i][j]=' ';
            // }
        }
    }

    for (int j = 4; j < 150; j++)
    {
        if (map[38][j] == d)
        {
            gotoxy(j, 38);
            cout << ' ';
            map[38][j] = ' ';
        }
    }
}

void sUFOmovement()
{
    if (Alive_1 == true)
    {
        if (t > 100)
        {
            alienX1 = RandomRow();
            alienY1 = RandomCol(130);
            t = 0;
        }

        if (t > 50)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 16; j++)
                {
                    if (UFO[i][j] != ' ' && map[alienX1 + i][alienY1 + j] == char(177))
                        hp_1 -= 34;

                    gotoxy(alienY1 + j, alienX1 + i);
                    cout << UFO[i][j];
                    map[alienX1 + i][alienY1 + j] = UFO[i][j];
                }
            }
        }

        if (hp_1 <= 0)
        {
            Alive_1 = false;
            Score += 300;
            DisplayScore();
        }
    }

    else
    {
        if (Alive_2 == true)
        {
            if (t > 100)
            {
                alienX1 = RandomRow();
                alienY1 = RandomCol(56);
            }

            if (t > 50)
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 16; j++)
                    {
                        if (UFO[i][j] != ' ' && map[alienX1 + i][alienY1 + j] == char(177))
                            hp_1 -= 34;

                        gotoxy(alienY1 + j, alienX1 + i);
                        cout << UFO[i][j];
                        map[alienX1 + i][alienY1 + j] = UFO[i][j];
                    }
                }
            }

            if (hp_2 <= 0)
            {
                Alive_2 = false;
                Score += 300;
                DisplayScore();
            }
        }

        if (Alive_3 == true)
        {
            if (t > 100)
            {
                alienX2 = RandomRow();
                alienY2 = 75 + RandomCol(56);
            }

            if (t > 50)
            {
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 16; j++)
                    {
                        if (UFO[i][j] != ' ' && map[alienX2 + i][alienY2 + j] == char(177))
                            hp_3 -= 34;

                        gotoxy(alienY2 + j, alienX2 + i);
                        cout << UFO[i][j];
                        map[alienX2 + i][alienY2 + j] = UFO[i][j];
                    }
                }
            }

            if (hp_3 <= 0)
            {
                Alive_3 = false;
                Score += 300;
                DisplayScore();
            }
        }
        if (t > 100)
        {
            t = 0;
        }
    }
}

void UFOlaser()
{
    if (Alive_1 == true)
    {
        gotoxy(alienY1 + 4, alienX1 + 5);
        cout << char(157);
        gotoxy(alienY1 + 12, alienX1 + 5);
        cout << char(157);
        map[alienX1 + 5][alienY1 + 4] = char(157);
        map[alienX1 + 5][alienY1 + 12] = char(157);
    }

    else
    {
        if (Alive_2 == true)
        {
            gotoxy(alienY1 + 4, alienX1 + 5);
            cout << char(157);
            gotoxy(alienY1 + 12, alienX1 + 5);
            cout << char(157);
            map[alienX1 + 5][alienY1 + 4] = char(157);
            map[alienX1 + 5][alienY1 + 12] = char(157);
        }

        if (Alive_3 == true)
        {
            gotoxy(alienY2 + 4, alienX2 + 5);
            cout << char(157);
            gotoxy(alienY2 + 12, alienX2 + 5);
            cout << char(157);
            map[alienX2 + 5][alienY2 + 4] = char(157);
            map[alienX2 + 5][alienY2 + 12] = char(157);
        }
    }
}

void UfoLaserMovement()
{
    char d = 157, previousItem;
    for (int i = 37; i > 5; i--)
    {
        for (int j = 4; j < 150; j++)
        {
            if (map[i][j] == d)
            {
                previousItem = map[i + 2][j];
                map[i + 2][j] = map[i][j];
                map[i][j] = previousItem;
                gotoxy(j, i);
                cout << map[i][j];
                gotoxy(j, i + 2);
                cout << map[i + 2][j];
            }
        }
    }

    for (int j = 4; j < 150; j++)
    {
        if (map[37][j] == d)
        {
            gotoxy(j, 37);
            cout << ' ';
            map[37][j] = ' ';
        }
        else if (map[38][j] == d)
        {
            gotoxy(j, 38);
            cout << ' ';
            map[38][j] = ' ';
        }
    }
}

void eraseEnemy(int x, int y)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            gotoxy(y + j, x + i);
            cout << ' ';
            map[x + i][y + j] = ' ';
        }
    }
}

int RandomRow()
{
    // srand(time(0));
    int result = 3 + (rand() % 20);
    return result;
}

int RandomCol(int n)
{
    // srand(time(0));
    int result = 3 + (rand() % n);
    return result;
}
