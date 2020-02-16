#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

using namespace std;

int solvegrid[9][9][9],sudo[9][9];//= {9,5,8,2,0,0,7,0,0,0,0,0,9,0,4,6,0,0,0,7,0,8,0,0,0,1,0,0,4,7,0,1,9,0,6,8,0,0,5,0,8,0,0,0,0,0,6,0,0,5,0,0,0,0,5,0,0,0,9,8,0,0,3,0,8,1,0,0,0,9,0,0,0,0,0,6,2,0,0,0,0};
int convert[2][9] = {0,1,2,3,4,5,6,7,8,0,0,0,3,3,3,6,6,6};

struct game
{
    int display();
    int menu();
    int inputsudo();
    int loopsolve();
    int solve1(); /** NARROW DOWN POSSIBLE NUMBERS **/
    int solve2();/** IF ONLY ONE NUMBER IS POSSIBLE IN AN ELEMENT, ADD IT TO THE SOLUTION **/
    int clearsq(int a, int b, int c);
};

game obj;


int main()
{
    obj.menu();
}

int game::menu()
{
    system("cls");
    system("title -SUDOKU SOLVER-");
    printf("      -SUDOKU SOLVER-\n\n\n 1. Input Sudoku and solve\n 2. Exit");
    switch(getch())
    {
    case 49:
        obj.inputsudo();
        break;
    case 50:
        break;
    default:
        obj.menu();
        break;
    }
}

int game::inputsudo()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            sudo[i][j] = 0;
            for(int k=0;k<9;k++)
            {
                solvegrid[i][j][k] = i+1;
            }
        }
    }
    int input;
    obj.display();
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            printf("\n\n Enter 0 for blank spaces, press backspace to re-enter previous cell");
            input = getch();
            if(input==8)
            {
                if(j==0&&i!=0){i=i-1;j=7;}
                else if(j!=0){j=j-2;}
            }
            else if(input<48||input>57&&input!=8){printf("\n\n Incorrect input, returning to menu...(press any key to continue)");getch();obj.menu();}
            else{sudo[i][j] = input - 48;}
            obj.display();
        }
    }
    printf("\n\n Input successfully taken, press Y to solve sudoku, or, press N to go back to the main menu.");
    switch(getch())
    {
        case 121: //y
            obj.loopsolve();
            break;
        case 89:
            obj.loopsolve();
            break;
        case 110:
            obj.menu();
            break;
        case 78:
            obj.menu();
            break;
        default:
            obj.menu();
            break;
    }
}

int game::loopsolve()
{
    bool flag;
    obj.solve1();
    obj.solve2();
    obj.display();
    flag = false;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(sudo[i][j]==0){flag = true;}
        }
    }
    if(flag = true){obj.loopsolve();}
    else{printf("\n\nSolved! (press any button to return to main menu)");getch();obj.menu();}
}

int game::solve1()
{
    int para1=0,para2=0;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(sudo[i][j]!=0)
            {
                for(int k=0;k<9;k++)
                {
                    solvegrid[k][i][j]=0;
                    if(convert[0][k]==i){para1 = convert[1][k];}
                    if(convert[0][k]==j){para2 = convert[1][k];}
                    solvegrid[sudo[i][j]-1][k][j] = 0;
                    solvegrid[sudo[i][j]-1][i][k] = 0;
                }
                obj.clearsq(para1,para2,sudo[i][j]-1);
            }
        }
    }
}

int game::solve2()
{
    int occ;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            occ=0;
            for(int k=0;k<9;k++)
            {
                if(solvegrid[j][i][k]==j+1){occ++;}
            }
            if(occ==1)
            {
                for(int k=0;k<9;k++)
                {
                    if(solvegrid[j][i][k]==j+1){sudo[i][k] = j+1;}
                }
            }
        }
    }
}

int game::clearsq(int a, int b, int c)
{
    for(int i=a;i<a+3;i++)
    {
        for(int j=b;j<b+3;j++)
        {
            solvegrid[c][i][j] = 0;
        }
    }
}

int game::display()
{
    system("CLS");
    printf(" +-----------------------------+\n");
    for(int i=0;i<9;i++)
    {
        printf(" | ");
        for(int j=0;j<9;j++)
        {
            if(j%3==0&&j!=0){printf("| %i  ",sudo[i][j]);}
            else{if((j+1)%3!=0){printf("%i  ",sudo[i][j]);}else{printf("%i ",sudo[i][j]);}}
        }
        printf("|");
        if((i+1)%3==0&&i!=8){printf("\n\n |-----------------------------|\n\n");}
        else{printf("\n\n");}
    }
    printf(" +-----------------------------+");
    /*printf("\n\n\n");
    for(int i=0;i<9;i++)
    {
        printf(" ");
        for(int j=0;j<9;j++)
        {
            printf("%i  ",solvegrid[6][i][j]);
        }
        printf("\n\n");
    }*/
    return 0;
}

