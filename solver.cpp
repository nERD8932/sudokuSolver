#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

int solvegrid[9][9][9],sudo[9][9],possibnum[9][9][2];
int convert[2][9] = {0,1,2,3,4,5,6,7,8,0,0,0,3,3,3,6,6,6};

struct game
{
    int menu();
    int inputsudo();
    int readfile();
    int display();
    int loopsolve();

    int solve1();
    int clearsq(int a, int b, int c);
    int pointingpairs(int a, int b);
    //int nakedpair();  /**needs work**/
   // int nakedpair_s(int a,int b); /**needs work**/
    int lockedcandidates(int a, int b);

    int solve2();
    int nakedsingle(int a,int b);
    int fillsq(int a, int b);

    int checkcomp();
    int calcpossibnum();
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
    printf("      -SUDOKU SOLVER-\n\n\n 1. Input Sudoku and solve\n 2. Read Sudoku text file and solve\n 3. Exit\n\n");
    switch(getch())
    {
    case 49:
        obj.inputsudo();
        break;
    case 50:
        obj.readfile();
        break;
    case 51:
        break;
    default:
        obj.menu();
        break;
    }
}

int game::readfile()
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
    char num;
    fstream file;
    file.open("sudoku.txt",ios::in);
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            num = file.get();
            if(num=='.'){sudo[i][j] = 0;}
            else{sudo[i][j] = num - 48;}
        }
    }
    file.close();
    obj.display();
    printf("\n\n File successfully read,\n press Y to solve sudoku,\n or, press N to go back to the main menu.");
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
    printf("\n\n Input successfully taken,\n press Y to solve sudoku,\n or, press N to go back to the main menu.");
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
    obj.solve1();
    obj.solve2();
    obj.calcpossibnum();
    for(int i=0;i<7;i=i+3){for(int j=0;j<7;j=j+3){obj.fillsq(i,j);}}
    for(int i=0;i<7;i=i+3){for(int j=0;j<7;j=j+3){obj.nakedsingle(i,j);}}
    for(int i=0;i<7;i=i+3){for(int j=0;j<7;j=j+3){obj.pointingpairs(i,j);}}
    //for(int i=0;i<7;i=i+3){for(int j=0;j<7;j=j+3){obj.nakedpair_s(i,j);}}
    for(int i=0;i<4;i=i+3){for(int j=0;j<7;j=j+3){obj.lockedcandidates(i,j);}}
    //obj.nakedpair();
    obj.display();
    obj.checkcomp();
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
            occ=0;
            for(int k=0;k<9;k++)
            {
                if(solvegrid[k][i][j]!=0){occ++;}
            }
            if(occ==1)
            {
                for(int k=0;k<9;k++)
                {
                    if(solvegrid[k][i][j]!=0){sudo[i][j]=k+1;}
                }
            }
        }
    }
}


int game::pointingpairs(int a,int b)
{
    int occ,occ2;
    for(int k=0;k<9;k++)
    {
        occ=0;
        for(int i=a;i<a+3;i++)
        {
            for(int j=b;j<b+3;j++)
            {
                if(solvegrid[k][i][j]!=0){occ++;}
            }
        }
        if(occ>1&&occ<4)
        {
            for(int i=a;i<a+3;i++)
            {
                occ2=0;
                for(int j=b;j<b+3;j++)
                {
                    if(solvegrid[k][i][j]!=0){occ2++;}
                }
                if(occ2==occ)
                {
                    for(int l=0;l<9;l++){if(l<b||l>b+2){solvegrid[k][i][l]=0;}}
                }
            }
            for(int i=b;i<b+3;i++)
            {
                occ2=0;
                for(int j=a;j<a+3;j++)
                {
                    if(solvegrid[k][j][i]!=0){occ2++;}
                }
                if(occ2==occ)
                {
                    for(int l=0;l<9;l++){if(l<a||l>a+2){solvegrid[k][l][i]=0;}}
                }
            }
        }
    }
}

int game::fillsq(int a, int b)
{
    int occ;
    for(int k=0;k<9;k++)
    {
        occ=0;
        for(int i=a;i<a+3;i++)
        {
            for(int j=b;j<b+3;j++)
            {
                if(solvegrid[k][i][j]!=0){occ++;}
            }
        }
        if(occ==1)
        {
            for(int i=a;i<a+3;i++)
            {
                for(int j=b;j<b+3;j++)
                {
                    if(solvegrid[k][i][j]!=0){sudo[i][j]=k+1;}
                }
            }
        }
    }
}

int game::nakedsingle(int a, int b)
{
    int occ,x1,x2;
    for(int k=0;k<9;k++)
    {
        occ=0;
        for(int i=a;i<a+3;i++)
        {
            for(int j=b;j<b+3;j++)
            {
                if(possibnum[i][j][0]==1&&possibnum[i][j][1]==k){occ++;x1=i;x2=j;}
            }
        }
    }
    if(occ==1){solvegrid[possibnum[x1][x2][1]][x1][x2]=possibnum[x1][x2][1]+1;}
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
    printf("\n\n\n");
   /* printf(" +-----------------------------+\n");
    for(int i=0;i<9;i++)
    {
        printf(" | ");
        for(int j=0;j<9;j++)
        {
            if(j%3==0&&j!=0){printf("| %i  ",possibnum[i][j][0]);}
            else{if((j+1)%3!=0){printf("%i  ",possibnum[i][j][0]);}else{printf("%i ",possibnum[i][j][0]);}}
        }
        printf("|");
        if((i+1)%3==0&&i!=8){printf("\n\n |-----------------------------|\n\n");}
        else{printf("\n\n");}
    }
    printf(" +-----------------------------+");

    int show=5;
    printf("\n\n\n");
    printf(" +-----------------------------+\n");
    for(int i=0;i<9;i++)
    {
        printf(" | ");
        for(int j=0;j<9;j++)
        {
            if(j%3==0&&j!=0){printf("| %i  ",solvegrid[show-1][i][j]);}
            else{if((j+1)%3!=0){printf("%i  ",solvegrid[show-1][i][j]);}else{printf("%i ",solvegrid[show-1][i][j]);}}
        }
        printf("|");
        if((i+1)%3==0&&i!=8){printf("\n\n |-----------------------------|\n\n");}
        else{printf("\n\n");}
    }
    printf(" +-----------------------------+");
    */
    return 0;
}

/*
int game::nakedpair_s(int a,int b)
{
    int x1,x2,x3,x4;
    for(int i=a;i<a+3;i++)
    {
        for(int j=b;j<b+3;j++)
        {
            x1=-1;x2=-1;x3=-1;x4=-1;
            if(possibnum[i][j][0]==2&&i!=a+2&&j!=b+2)
            {
                for(int k=0;k<9;k++){if(solvegrid[k][i][j]!=0){if(x1==-1){x1=k;}else{x2=k;}}}
            }

            if(j==b+2)
            {
                for(int k=i+1;k<a+3;k++)
                {
                    for(int l=b;l<b+3;l++)
                    {
                        if(possibnum[k][l][0]==2)
                        {
                            for(int n=0;n<9;n++){if(solvegrid[n][k][l]!=0){if(x3==-1){x3=n;}else{x4=n;}}}
                        }
                        if(x1==x3&&x2==x4)
                        {
                            for(int n=a;n<a+3;n++)
                            {
                                for(int m=b;m<b+3;m++)
                                {
                                    if(n==i&&m==j){}
                                    else if(n==k&&m==l){}
                                    else{solvegrid[x1][n][m]=0;solvegrid[x2][n][m]=0;}
                                }
                            }

                        }
                        else{x3=-1;x4=-1;}
                    }
                }
            }
            else
            {
                for(int k=i+1;k<a+3;k++)
                {
                    for(int l=b;l<b+3;l++)
                    {
                        if(possibnum[k][l][0]==2)
                        {
                            for(int n=0;n<9;n++){if(solvegrid[n][k][l]!=0){if(x3==-1){x3=n;}else{x4=n;}}}
                        }
                        if(x1==x3&&x2==x4)
                        {
                            for(int n=a;n<a+3;n++)
                            {
                                for(int m=b;m<b+3;m++)
                                {
                                    if(n==i&&m==j){}
                                    else if(n==k&&m==l){}
                                    else{solvegrid[x1][n][m]=0;solvegrid[x2][n][m]=0;}
                                }
                            }

                        }
                        else{x3=-1;x4=-1;}
                    }
                }
            }
        }
    }
}

int game::nakedpair()
{
    int x1,x2,x3,x4;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            x1=-1;x2=-1;x3=-1;x4=-1;
            if(possibnum[i][j][0]==2&&j<8)
            {
                for(int k=0;k<9;k++){if(solvegrid[k][i][j]!=0){if(x1==-1){x1=k;}else{x2=k;}}}
            }
            for(int k=j+1;k<9;k++)
            {
                if(possibnum[i][k][0]==2)
                {
                    for(int l=0;l<9;l++){if(solvegrid[l][i][k]!=0){if(x3==-1){x3=l;}else{x4=l;}}}
                }
                if(x1==x3&&x2==x4)
                {
                    for(int l=0;l<9;l++)
                    {
                        if(l!=j&&l!=k){solvegrid[x1][i][l]=0;solvegrid[x2][i][l]=0;}
                    }

                }
                else{x3=-1;x4=-1;}
            }
        }
    }
}
*/
int game::checkcomp()
{
    bool flag;
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

int game::calcpossibnum()
{
    int occ;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            occ=0;
            for(int k=0;k<9;k++)
            {
                if(solvegrid[k][i][j]!=0){occ++;}
            }
            possibnum[i][j][0] = occ;
            if(occ==1)
            {
                for(int k=0;k<9;k++)
                {
                    if(solvegrid[k][i][j]!=0){possibnum[i][j][1]=k;}
                }
            }
        }
    }
}

int game::lockedcandidates(int a, int b)
{
    int occ,occ2,x1,x2;
    for(int k=0;k<9;k++)
    {
        for(int i=a;i<a+3;i++)
        {
            occ = 0;
            for(int j=b;j<b+3;j++)
            {
                if(solvegrid[k][i][j]!=0){++occ;if(occ==1){x1=j;}else{x2=j;}}
            }
            if(occ==2&&i<8)
            {
                for(int m=0;m<9;m++){if(solvegrid[k][i][m]!=0){occ++;}}
                if(occ==4)
                {
                    for(int m=convert[1][i]+3;m<9;m++)
                    {
                        occ2=0;
                        for(int n=0;n<9;n++){if(solvegrid[k][m][n]!=0){occ2++;}}
                        if(occ2==2&&solvegrid[k][m][x1]!=0&&solvegrid[k][m][x2]!=0)
                        {
                            for(int n=0;n<9;n++)
                            {
                                if(n!=x1&&n!=x2){solvegrid[k][i][n]=0;solvegrid[k][m][n]=0;}
                                if(n!=i&&n!=m){solvegrid[k][n][x1]=0;solvegrid[k][n][x2]=0;}
                            }
                            for(int c=a;c<a+3;c++)
                            {
                                for(int v=b;v<b+3;v++)
                                {
                                    if(c!=i&&v!=x1&&v!=x2){solvegrid[k][c][v]=0;}
                                }
                            }
                            for(int c=convert[1][m];c<convert[1][m]+3;c++)
                            {
                                for(int v=convert[1][x1];v<convert[1][x1]+3;v++)
                                {
                                    if(c!=m&&v!=x1&&v!=x2){solvegrid[k][c][v]=0;}
                                }
                            }
                        }
                    }
                }
            }

            occ = 0;
            for(int j=b;j<b+3;j++)
            {
                if(solvegrid[k][j][i]!=0){++occ;if(occ==1){x1=j;}else{x2=j;}}
            }
            if(occ==2&&i<8)
            {
                for(int m=0;m<9;m++){if(solvegrid[k][m][i]!=0){occ++;}}
                if(occ==4)
                {
                    for(int m=convert[1][i]+3;m<9;m++)
                    {
                        occ2=0;
                        for(int n=0;n<9;n++){if(solvegrid[k][n][m]!=0){occ2++;}}
                        if(occ2==2&&solvegrid[k][x1][m]!=0&&solvegrid[k][x2][m]!=0)
                        {
                            for(int n=0;n<9;n++)
                            {
                                if(n!=x1&&n!=x2){solvegrid[k][n][i]=0;solvegrid[k][n][m]=0;}
                                if(n!=i&&n!=m){solvegrid[k][x1][n]=0;solvegrid[k][x2][n]=0;}
                            }
                            for(int c=a;c<a+3;c++)
                            {
                                for(int v=b;v<b+3;v++)
                                {
                                    if(c!=i&&v!=x1&&v!=x2){solvegrid[k][v][c]=0;}
                                }
                            }
                            for(int c=convert[1][m];c<convert[1][m]+3;c++)
                            {
                                for(int v=convert[1][x1];v<convert[1][x1]+3;v++)
                                {
                                    if(c!=m&&v!=x1&&v!=x2){solvegrid[k][v][c]=0;}
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

