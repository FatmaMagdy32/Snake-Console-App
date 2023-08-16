#include <bits/stdc++.h>
#include <ctime>
#include<conio.h>
#include<windows.h>
using namespace std;

class Map
{
    public:
    int width,height,fruitx,fruity;

};

class snake
{
public:
    int headx, heady, tail;
    char dir;
    int tailx[50]; int taily[50];
};

class player
{
    public:
    int score;
    bool lose = false;
};

Map map1;
snake s;
player p;

class Game
{
public:
    static void setup()
    {
       map1.width = 40;
       map1.height =20;
       generate_fruit();
       ///-----------------
       s.headx= map1.width /2;
       s.heady = map1.height /2;
       s.tail =0;
       ///-------------------
       p.score=0;
       p.lose=false;
    }
    static void generate_fruit()
    {
       srand(time(NULL));
       map1.fruitx = (rand() %(map1.width-2)) +1 ; //1 to 38
       map1.fruity = (rand() %(map1.height-2))  +1;
    }
    static void draw()
    {
        system("cls");
        for(int i =0 ; i< map1.height; i++)
        {
            for(int j=0; j<map1.width; j++)
            {
                if(i==0 || i==map1.height-1)
                    cout << "*";
                else if(j==0 || j==map1.width-1)
                    cout << "*";
                else if (i == s.heady && j== s.headx)
                    cout << "O";
                else if (i == map1.fruity &&j== map1.fruitx)
                    cout << "$";
                else
                   {
                       bool printed = false;
                       for(int z=0; z<s.tail; z++)
                       {
                           if(s.tailx[z] == j && s.taily[z] == i)
                           {
                               cout << "o";
                               printed = true;
                               break;
                           }

                       }
                       if(!printed)
                        cout << " ";

                   }
            }
            cout << endl;
        }
        cout << "Player Score " << p.score << endl;
    }
    static void input()
    {
        if(_kbhit())
        {
            char c = _getch();
            switch(c)
            {
            case 'w' :
                s.dir = 't';
                break;
            case 's' :
                s.dir = 'd';
                break;
            case 'd' :
                s.dir = 'r';
                break;
            case 'a' :
                s.dir = 'l';
                break;
            case 'x' :
               exit(0);
            }
        }
    }
    static void Move()
    {   shift(s.tailx,50);
        shift(s.taily,50);
        s.tailx[0] = s.headx;
        s.taily[0] = s.heady;
        switch(s.dir)
        {
        case 't':   s.heady--; break;
        case 'd': s.heady++; break;
        case 'r': s.headx++; break;
        case 'l': s.headx--; break;
        }
        if(s.heady >= map1.height || s.heady <=0 || s.headx>=map1.width || s.headx <=0)
        {
            p.lose=true;
        }
        if(s.headx== map1.fruitx && s.heady == map1.fruity)
        {
            generate_fruit();
            p.score++;
            s.tail++;
        }
    }

    static void shift(int arr[], int n)
    {
        for(int i =n-2; i>=0; i--)
        {
            arr[i+1]=arr[i];
        }
    }



};



int main()
{
    Game::setup();
    while(!p.lose)
    {
        Game::draw();
        Game::input();
        Game::Move();
        Sleep(200);
    }
    cout << "\nYou lose";
    return 0;
}


