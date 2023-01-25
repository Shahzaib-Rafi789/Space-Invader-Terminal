#include<iostream>
#include<conio.h>
#include<fstream>
#include<windows.h>
using namespace std;

void loadData();
void printMap();
void gotoxy(int x, int y);
void DisplaySpaceship(int);
void spaceshipMoveLeft();
void spaceshipMoveRight();
void alien1Movement(int);
void alien2Movement(int k);
void alien1Horizontal1();
void alien2Horizontal1();
void Rip_alien(int,int);
void bossMovement(int);
void spaceshipLaser();
void shootLaser(int n);
void moveLasers();
void alien1Lasers();
void alien1LasersMovement();

char map[45][156];
char spaceship[7][11];
char alien1[5][11];
char alien2[4][10];
char alien2A[4][10];//2nd animation
char boss[11][34];
char bossA[11][34];// 2nd boss animation

int sX=34,sY=73;
int alienX1=3,alienY1=3,a1way=1;
int alienX2=9,alienY2=36;
int n=0,count=0,speed=0,g=0;
int health=100,hp_1=100,hp_2=100,hp_3=100,hp_4=100,hp_5=100;
bool Alive_1=true,Alive_2=true,Alive_3=true,Alive_4=true,Alive_5=true;

main()
{
    loadData();
    system("cls");
    printMap();
    // spaceshipLaser();
    // DisplaySpaceship(0); 
    // for(int i=0;i<30;i++)
    // {
    //     Sleep(200);
    //     alien1Movement(i);
    //     alien2Movement(i+14);
    //     // bossMovement(i);
    // }
    while(!GetAsyncKeyState(VK_ESCAPE))
    {
        count+=10;
        speed++;
        n++;
        alien1Horizontal1();
        alien2Horizontal1();
        // if(count>10)
        // {
        //     alien1LasersMovement();
        //     if(count>50){
        //     alien1Lasers();
        //     count=0;
        //     }
        // }
        if(GetAsyncKeyState(VK_LEFT))
        {
            spaceshipMoveLeft();
            count+=50;
            // speed=0;
        }
        else if(GetAsyncKeyState(VK_RIGHT))
        {
            spaceshipMoveRight();
            count+=50;
            // speed=0;
        }
        // else if(count==2 && t<=5)
        // {
        //     Sleep(1);
        //     speed++;
        // }
        else if(GetAsyncKeyState(VK_SPACE) && speed>=50)
        {
            shootLaser(n);
            count+=50;
            speed=0;
        }
    //     // if(count==2)
    //     // {
    //     //     count=0;
    //     //     bossMovement(n);
    //     //     n++;
    //     // }
    //     // counspeed++;
        if(n>50){
            alien1Lasers();
            n=0;
        }
        if(count>=100){
            count=0;
            moveLasers();
            alien1LasersMovement();
        }
    }
}
void loadData()
{
    fstream file;
    int temp;
    file.open("D:\\Space invader\\Document\\map.txt",ios::in);
    for(int i=0;i<45;i++)
    {
        for(int j=0;j<156;j++)
        {
            file >> temp;
            map[i][j]=temp;
        }
    }
    file.close();

    file.open("D:\\Space invader\\Document\\Spaceship.txt",ios::in);
    for(int i=0;i<7;i++)
    {
        for(int j=0;j<11;j++)
        {
            file >> temp;
            spaceship[i][j]=temp;
        }
    }
    file.close();

    file.open("D:\\Space invader\\Document\\Alien1.txt",ios::in);
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<11;j++)
        {
            file >> temp;
            alien1[i][j]=temp;
        }
    }
    file.close();

    file.open("D:\\Space invader\\Document\\Alien2.txt",ios::in);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<10;j++)
        {
            file >> temp;
            alien2[i][j]=temp;
        }
    }
    file.close();

    file.open("D:\\Space invader\\Document\\Alien2A.txt",ios::in);
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<10;j++)
        {
            file >> temp;
            alien2A[i][j]=temp;
        }
    }
    file.close();

    file.open("D:\\Space invader\\Document\\Boss.txt",ios::in);
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<34;j++)
        {
            file >> temp;
            boss[i][j]=temp;
        }
    }
    file.close();

    file.open("D:\\Space invader\\Document\\BossA.txt",ios::in);
    for(int i=0;i<11;i++)
    {
        for(int j=0;j<34;j++)
        {
            file >> temp;
            bossA[i][j]=temp;
        }
    }
    file.close();
}
void printMap()
{
    for(int i=0;i<45;i++)
    {
        for(int j=0;j<156;j++)
        {
            cout<<map[i][j];
        }
        cout<<endl;
    }
}
void gotoxy(int x, int y)
{
COORD coordinates;
coordinates.X = x;
coordinates.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
void DisplaySpaceship(int check)
{
    for(int i=0;i<7;i++)
    {
        for(int j=0;j<11;j++)
        {
            gotoxy(sY+j,sX+i);
            cout<<spaceship[i][j];
        }
        if(check==1){
            gotoxy(sY-1,sX+i);
        }
        
        cout<<' ';
        cout<<endl;
    }
}
void spaceshipMoveLeft()
{
    if(sY>3)
    {
        sY--;
        DisplaySpaceship(0);
    }
}
void spaceshipMoveRight()
{
    if(sY<142)
    {
        sY++;
        DisplaySpaceship(1);
    }
}
void alien1Horizontal1()
{
    if(Alive_1 || Alive_2)
    {
        alienY1+=a1way;
        for(int i=0;i<5;i++)
        {
            if(Alive_1!=false)
            {
                gotoxy(alienY1-a1way,alienX1+i);
                if(a1way==-1){
                    gotoxy(alienY1+11,alienX1+i);
                }
                cout<<' ';
            }
        
        if(Alive_2!=false)
            {
                gotoxy(alienY1-a1way+70,alienX1+i);
                if(a1way==-1){
                    gotoxy(alienY1+81,alienX1+i);
                }
                cout<<' ';
            }

            for(int j=0;j<11;j++)
            {
                if(Alive_1!=false)
                {
                    gotoxy(alienY1+j,alienX1+i);
                    cout<<alien1[i][j];

                    if(alien1[i][j]!=' ' && map[alienX1+i][alienY1+j]==char(177)){
                        hp_1-=20;
                        map[alienX1+i][alienY1+j]=' ';
                    }

                    if(hp_1<=0){
                        Alive_1=false;
                        Rip_alien(alienX1,alienY1);
                    }
                }

                if(Alive_2!=false)
                {
                    gotoxy(alienY1+j+70,alienX1+i);
                    cout<<alien1[i][j];

                    if(alien1[i][j]!=' ' && map[alienX1+i][alienY1+j+70]==char(177)){
                        hp_2-=20;
                        map[alienX1+i][alienY1+j+70]=' ';
                    }

                    if(hp_2<=0){
                        Alive_2=false;
                        Rip_alien(alienX1,alienY1+70);
                    }
                }
            }
        }
        gotoxy(0,1);

        if(alienY1<4 || alienY1>70)
        {
            a1way=a1way*-1;
        }
    }
}
void alien2Horizontal1()
{
    if(Alive_3 || Alive_4 || Alive_5)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<10;j++)
            {
                if(Alive_3!=false)
                {
                    gotoxy(alienY2+j,alienX2+i);
                    cout<<alien2[i][j];

                    if(alien2[i][j]!=' ' && map[alienX2+i][alienY2+j]==char(177)){
                        hp_3-=34;
                        map[alienX2+i][alienY2+j]=' ';
                    }

                    if(hp_3<=0){
                        Alive_3=false;
                        Rip_alien(alienX2,alienY2);
                    }
                }

                if(Alive_4!=false)
                {
                    gotoxy(alienY2+j+38,alienX2+i);
                    cout<<alien2A[i][j];

                    if(alien2[i][j]!=' ' && map[alienX2+i][alienY2+j+38]==char(177)){
                        hp_4-=34;
                        map[alienX2+i][alienY2+j+38]=' ';
                    }

                    if(hp_4<=0){
                        Alive_4=false;
                        Rip_alien(alienX2,alienY2+38);
                    }
                }

                if(Alive_5!=false)
                {
                    gotoxy(alienY2+j+76,alienX2+i);
                    cout<<alien2[i][j];

                    if(alien2[i][j]!=' ' && map[alienX2+i][alienY2+j+76]==char(177)){
                        hp_5-=34;
                        map[alienX2+i][alienY2+j+76]=' ';
                    }

                    if(hp_5<=0){
                        Alive_5=false;
                        Rip_alien(alienX2,alienY2+76);
                    }
                }
            }
        }
    }
    gotoxy(0,1);
}
void Rip_alien(int x,int y)
{
    for(int i=0;i<5;i++)
    {
        for(int j=-1;j<12;j++)
        {
            gotoxy(y+j,x+i);
            cout<<' ';
            map[x+i][y+j]=' ';
        }
    }
}
void alien1Movement(int k)
{
    for(int i=0;i<5;i++)
    {
        gotoxy(k+2,i+2);
        cout<<' ';
        for(int j=0;j<11;j++)
        {
            gotoxy(j+k+3,i+2);
            cout<<alien1[i][j];
        }
    }
    gotoxy(0,1);
}
void alien2Movement(int k)
{
    for(int i=0;i<4;i++)
    {
        gotoxy(k+2,i+2);
        cout<<' ';
        for(int j=0;j<10;j++)
        {
            gotoxy(j+k+3,i+2);
            if(k%2==0)
            cout<<alien2[i][j];
            if(k%2!=0)
            cout<<alien2A[i][j];
        }
    }
    gotoxy(0,1);
}
void bossMovement(int k)
{
    if((k/5)%2==0)
    {
        for(int i=0;i<11;i++)
        {
            // gotoxy(k+2,i+2);
            // cout<<' ';
            for(int j=0;j<34;j++)
            {
                gotoxy(j+61,i+2);
                cout<<boss[i][j];
            }
        }
    }
    else if((k/5)%2!=0)
    {
        for(int i=0;i<11;i++)
        {
            // gotoxy(k+2,i+2);
            // cout<<' ';
            for(int j=0;j<34;j++)
            {
                gotoxy(j+61,i+2);
                cout<<bossA[i][j];
            }
        }
    }
    gotoxy(0,1);
}
void spaceshipLaser()
{
    gotoxy(sY,sX);
    for(int i=0;sX-i>2;i++)
    {
        Sleep(100);
        gotoxy(sY,sX-i);
        cout<<char(177);
        gotoxy(sY,sX-i+1);
        cout<<' ';
    }
}
void shootLaser(int n)
{
    gotoxy(sY+5,sX-2);
    cout<<char(177);
    map[sX-2][sY+5]=char(177);
}
void moveLasers()
{
    char c=177,previousItem;
    int move;
    for(int i=5;i<37;i++)
    {
        for(int j=4;j<150;j++)
        {
            if(map[i][j]==c)
            {
                move=2;
                previousItem=map[i-move][j];
                map[i-move][j]=map[i][j];
                map[i][j]=previousItem;
                gotoxy(j,i);
                cout<<map[i][j];
                gotoxy(j,i-move);
                cout<<map[i-move][j];
            }
        }
    }

    for(int j=4;j<150;j++){
        if(map[4][j]==c){
            gotoxy(j,4);
            cout<<' ';
            map[4][j]=' ';
        }
    }
}
void alien1Lasers()
{
    gotoxy(alienY1+5,alienX1+7);
    cout<<char(157);
    map[alienX1+7][alienY1+5]=char(157);
}
void alien1LasersMovement()
{
    char d=157,previousItem;
    for(int i=37;i>5;i--)
    {
        for(int j=4;j<150;j++)
        {
            if(map[i][j]==d)
            {
                previousItem=map[i+2][j];
                map[i+2][j]=map[i][j];
                map[i][j]=previousItem;
                gotoxy(j,i);
                cout<<map[i][j];
                gotoxy(j,i+2);
                cout<<map[i+2][j];
            }
        }
    }

    for(int j=4;j<150;j++){
        if(map[38][j]==d)
        {
            gotoxy(j,38);
            cout<<' ';
            map[38][j]=' ';
        }
    }
}