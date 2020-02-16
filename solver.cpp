#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

using namespace std;

int solvegrid[9][9][9],sudo[9][9];
int convert[2][9] = {0,1,2,3,4,5,6,7,8,0,0,0,3,3,3,6,6,6};

struct game
{
    int display();
    int menu();
    int inputsudo();
    int loopsolve();
    int solve1(); /** NARROW DOWN POSSIBLE NUMBERS **/
    int solve2();/** IF ONLY ONE NUMBER IS POSSIBLE IN AN ELEMENT, ADD IT TO THE SOLUTION **/
    int checkns(int a, int b);/**NAKED SINGLE TEST**/
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
    printf("      -SUDOKU SOLVER-\n\n\n 1. Input Sudoku and solve\n 2. Exit\n\n");
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
                if(j==0&&i!=0){i=i-1;j=7;sudo[i][j+1]=0;}
                else if(j!=0){j=j-2;sudo[i][j+1]=0;}
            }
            else if(input<48||input>57&&input!=8){printf("\n\n Incorrect input, returning to menu...(press any key to continue)");getch();obj.menu();}
            else{sudo[i][j] = input - 48;}
            obj.display();
        }
    }
    printf("\n\n Input successfully taken,\n press Y to solve sudoku, or, press N to go back to the main menu.");
    switch(getch())
    {
        case 121: //Y
            obj.loopsolve();
            break;
        case 89: //Y
            obj.loopsolve();
            break;
        case 110: //N
            obj.menu();
            break;
        case 78: //N
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
    for(int i=0;i<7;i=i+3){for(int j=0;j<7;j=j+3){obj.checkns(i,j);}}
    obj.display();
    flag = false;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(sudo[i][j]==0){flag = true;}
        }
    }
    if(flag==true){obj.loopsolve();}
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

int game::checkns(int a,int b)
{
    int occ=0,occ2=0;
    for(int k=0; k<9;k++)
    {
        occ=0;
        for(int i=a;i<a+3;i++)
        {
            for(int j=b;j<b+3;j++)
            {
                if(solvegrid[k][i][j]==k+1){occ++;}
            }
        }
        if(occ<=3&&occ!=0)
        {
            for(int i=a;i<a+3;i++)
            {
                occ2=0;
                for(int j=b;j<b+3;j++)
                {
                    if(solvegrid[k][i][j]==k+1){occ2++;}
                }
                if(occ2==occ)
                {
                    for(int l=0;l<9;l++)
                    {
                        if(l<b||l>b+2)
                        {
                            solvegrid[k][i][l] = 0;
                        }
                    }
                    break;
                }
            }

            for(int i=b;i<b+3;i++)
            {
                occ2=0;
                for(int j=a;j<a+3;j++)
                {
                    if(solvegrid[k][j][i]==k+1){occ2++;}
                }
                if(occ2==occ)
                {
                    for(int l=0;l<9;l++)
                    {
                        if(l<a||l>a+2)
                        {
                            solvegrid[k][l][i] = 0;
                        }
                    }
                    break;
                }
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
            occ=0;
            for(int k=0;k<9;k++)
            {
                if(solvegrid[j][k][i]==j+1){occ++;}
            }
            if(occ==1)
            {
                for(int k=0;k<9;k++)
                {
                    if(solvegrid[j][k][i]==j+1){sudo[k][i] = j+1;}
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
   /* printf("\n\n\n");
    for(int i=0;i<9;i++)
    {
        printf(" ");
        for(int j=0;j<9;j++)
        {
            printf("%i  ",solvegrid[2][i][j]);
        }
        printf("\n\n");
    }
    return 0;*/
}

