#include<iostream>
using namespace std;

struct moves
{
    int row,col,score;
};

struct TicTacToe
{
    char human, computer, board[3][3];
    TicTacToe()
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                board[i][j]=' ';
            }
        }
    }
    bool Winner()
    {
        int winConditions[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
        for(int i=0;i<8;i++)
        {
            bool win=true;
            int firstRow= board[i][0]/3, firstCol=board[i][0]%3;
            for(int j=0;j<3;j++)
            {
                int row=winConditions[i][j]/3, col=winConditions[i][j]%3;
                if(board[firstRow][firstCol] == ' ' || board[firstRow][firstCol] != board[row][col])
                {
                    win=false;
                }
            }
            if(win)
            {
                return true;
            }           
        }
        return false;
    }
    bool tieCheck()
    {
        if(Winner())
        {
            return false;
        }
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(board[i][j] == ' ')
                {
                    return false;
                }
            }
        }
        return true;
    }

    void humanMove()
    {
        while(true)
        {
            int position;
            cout<<"Enter the postion between (1-9) where you want to put your symbol: ";
            cin>>position;
            int row= (position-1)/3,col=(position-1)%3;
            if(position >=1 && position<=9 && board[row][col] == ' ')
            {
                board[row][col]= human;
                break;
            }
        }
    }

    void computerMove()
    {
        moves bestMove=minimax();
        board[bestMove.row][bestMove.col]=computer;  
    }

    moves minimax(bool maximizing_player= true)
    {
        moves bestMove;
        if(Winner())
        {
            if(maximizing_player)
            {
                bestMove.score=-1;
            }
            else
            {
               bestMove.score=1;
            }
            return bestMove;
        }
        else if(tieCheck())
        {
            bestMove.score=0;
            return bestMove;
        }
        bestMove.score= maximizing_player? -2 : 2;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(board[i][j] == ' ')
                {
                    board[i][j]= maximizing_player ? computer : human;
                    moves board_state= minimax(!maximizing_player);
                    if(maximizing_player)
                    {
                        if(board_state.score > bestMove.score)
                        {
                            bestMove.score=board_state.score;
                            bestMove.row=i;
                            bestMove.col=j;
                        }
                    }
                    else
                    {
                        if(board_state.score < bestMove.score)
                        {
                            bestMove.score=board_state.score;
                            bestMove.row=i;
                            bestMove.col=j;
                        }
                    }
                    board[i][j]= ' ';
                }       
            }         
        }
        return bestMove;
    }

    void play()
    {
        while(true)
        {
            cout<<"Choose a symbol between 'X' or 'O', X is going first and O going second: ";
            cin>>human;
            human=toupper(human);
            if(human == 'X' || human == 'O')
            {
                break;
            }
        }
        computer= human == 'X'? 'O': 'X';
        if(human == 'O')
        {
            computerMove();
        }
        print();
        while(true)
        {
            humanMove();
            print();
            if(Winner())
            {
                cout<<"Player wins!!!\n";
                return;
            }
            else if(tieCheck())
            {
                cout<<"Tie!!!\n";
                return;
            }
            cout<<"Computer is making a move: \n";
            computerMove();
            print();
            if(Winner())
            {
                cout<<"AI Wins!!!\n";
                return;
            }
            else if(tieCheck())
            {
                cout<<"Tie!!\n";
            }
        }
    }


    void print()
    {
        for(int i=0;i<3;i++)
        {
            if(i)
            {
                cout<<"--------------\n";
            }
            for(int j=0;j<3;j++)
            {
                if(j)
                {
                    cout<<"|";
                }
                cout<<" ";
                if(board[i][j] == ' ')
                {
                    cout<<3*i + j +1;
                }
                else
                {
                    cout<<board[i][j];
                }
                cout<<" ";
            }
            cout<<"\n";
        }
    }
};

int main()
{
    TicTacToe game;
    game.play();
    return 0;
}

