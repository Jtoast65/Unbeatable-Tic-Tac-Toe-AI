#include <iostream>
#include "GameState.h"
#include "GameTree.h"
#include "LinkedList.h"
#include "Queue.h"

using namespace std;

void ai_play_block(int dim, int MaxNodes){
    
}

void play(){
    cout << "\nChoose the Game Mode:\n" << "\n(1) for Player vs Player\n" << "(2) for Player vs AI\n" << endl;
    int input1;
    cin >> input1;
    if(input1 == 1){
        cout << "\nYou chose to play Player vs Player!\n" << endl;
        cout << "\nChoose dimensions of the board:   ";
        int dim;
        cin>>dim;
        cout << endl;
        GameState board(dim);
        cout << "\n" << board << endl;
        int row;
        int col;
        while(true){
            cout << "Input Row: ";
            cin >> row;
            cout << "Input Column: ";
            cin >> col;
            board.play(row, col);
            cout << "\n" << board << endl;
            if(board.hasWon(!board.currentTurn)){
                if(board.currentTurn){
                    cout << "\nX has won!!!\n" << endl;
                }else{
                    cout << "\nO has won!!!\n" << endl;
                }
                break;
            }
        }
        
    }else if(input1 == 2){
        cout << "\nYou chose to play Player vs AI!" << endl;
        cout << "\nChoose the Dificulty:\n" << "\n(1) easy\n" << "(2) medium\n" << "(3) hard\n" << endl;
        int input2;
        cin >> input2;
        if(input2 == 1){
            cout << "\nYou chose to play Easy!\n" << endl;
            int MaxNodes = 100'000;
            cout << "\nChoose dimensions of the board: ";
            int dim;
            cin>>dim;
            cout << endl;

            GameState board(dim);

            board.play(dim/2, dim/2);
            cout << "\n" << board << endl;

            int row;
            int col;
            while(true){
                cout << "Input Row: ";
                cin >> row;
                cout << "Input Column: ";
                cin >> col;
                
                if(board.grid[row][col] != -1){
                    throw std::logic_error("Aidan -invalid move dummy");
                }else{
                    board.play(row, col);
                }

                cout << "\n" << board << endl;

                GameTree* tree = new GameTree(board, MaxNodes);
                Vec nextmv = tree->nextMove();

                cout << "\n AI Move:" << endl;
                board.play(nextmv.x, nextmv.y);
                cout << "\n" << board << endl;

                delete tree;

                if(board.hasWon(!board.currentTurn)){
                    if(board.currentTurn){
                        cout << "\nX has won!!!\n" << endl;
                        break;
                    }else{
                        cout << "\nO has won!!!\n" << endl;
                        break;
                    }
                }
                if(board.turnCount == dim*dim){
                    cout << "It's a Tie!!!" << endl;
                    break;
                }
            }

        }else if(input2 == 2){
            cout << "\nYou chose to play Medium!\n" << endl;
            int MaxNodes = 500'000;
            cout << "\nChoose dimensions of the board: ";
            int dim;
            cin>>dim;
            cout << endl;

            GameState board(dim);

            board.play(dim/2, dim/2);
            cout << "\n" << board << endl;

            int row;
            int col;
            while(true){
                cout << "Input Row: ";
                cin >> row;
                cout << "Input Column: ";
                cin >> col;

                if(board.grid[row][col] != -1){
                    throw std::logic_error("Aidan -invalid move dummy");
                }else{
                    board.play(row, col);
                }
                cout << "\n" << board << endl;

                GameTree* tree = new GameTree(board, MaxNodes);
                Vec nextmv = tree->nextMove();

                cout << "\n AI Move:" << endl;
                board.play(nextmv.x, nextmv.y);
                cout << "\n" << board << endl;

                delete tree;

                if(board.hasWon(!board.currentTurn)){
                    if(board.currentTurn){
                        cout << "\nX has won!!!\n" << endl;
                        break;
                    }else{
                        cout << "\nO has won!!!\n" << endl;
                        break;
                    }
                }
                if(board.turnCount == dim*dim){
                    cout << "It's a Tie!!!" << endl;
                    break;
                }
            }

        }else if(input2 == 3){
            cout << "\nYou chose to play Hard!\n" << endl;
            int MaxNodes = 1'000'000;
            cout << "\nChoose dimensions of the board: ";
            int dim;
            cin>>dim;
            cout << endl;

            GameState board(dim);

            board.play(dim/2, dim/2);
            cout << "\n" << board << endl;

            int row;
            int col;
            while(true){
                cout << "Input Row: ";
                cin >> row;
                cout << "Input Column: ";
                cin >> col;

                if(board.grid[row][col] != -1){
                    throw std::logic_error("Aidan -invalid move dummy");
                }else{
                    board.play(row, col);
                }
                cout << "\n" << board << endl;

                GameTree* tree = new GameTree(board, MaxNodes);
                Vec nextmv = tree->nextMove();

                cout << "\n AI Move:" << endl;
                board.play(nextmv.x, nextmv.y);
                cout << "\n" << board << endl;

                delete tree;

                if(board.hasWon(!board.currentTurn)){
                    if(board.currentTurn){
                        cout << "\nX has won!!!\n" << endl;
                        break;
                    }else{
                        cout << "\nO has won!!!\n" << endl;
                        break;
                    }
                }
                if(board.turnCount == dim*dim){
                    cout << "It's a Tie!!!" << endl;
                    break;
                }
            }

        }else{
            cout << "\nInvalid Input\n" << endl;
        }
    }else{
        cout << "\nInvalid Input\n" << endl;
    }
}

int main(){

    play();

    return 0;
}