#ifndef GAMETREE_H
#define GAMETREE_H

#include "GameState.h"
#include "Queue.h"
#include <iostream>
#include <stdexcept>

struct Node{
    int win;
    GameState board;
    Node** Nodes;

    Node(GameState gs){
        win = 0;
        board = gs;
        int sz = gs.size;
        Nodes = new Node*[sz*sz];
        for(int i=0; i<sz*sz; i++){
            Nodes[i] = nullptr;
        }
    }
};

struct GameTree{

    private:

        int closeToWin(GameState board){
            int sz = board.size;
            int k = 0;
            for(int i=0; i<sz; i++){
                for(int j=0; j<sz; j++){
                    if(board.grid[i][j] == -1){
                        GameState temp = board;
                        temp.play(i,j);
                        if(temp.hasWon(board.currentTurn)){
                            return k;
                        }
                    }
                    k++;
                }
            }

            return -1;
        }

        int deleteTree(Node* start){
            if(start == nullptr){
                return 0;
            }

            int sz = start->board.size;
            int cnt = 1;
            for(int i=0; i<sz*sz; i++){
                cnt += deleteTree(start->Nodes[i]);
            }

            delete start;
            start = nullptr;

            return cnt;
        }

        int max(int a, int b){
            if(a >= b){
                return a;
            }else{
                return b;
            }
        }

        int min(int a, int b){
            if(a >= b){
                return b;
            }else{
                return a;
            }
        }

        int minmax(Node* start, bool maxPlayer){
            int sz = start->board.size;
            bool term_node = true;
            for(int i=0; i<sz*sz; i++){
                if(start->Nodes[i] != nullptr){
                    term_node = false;
                    break;
                }
            }
            if(term_node){
                return start->win;
            }

            if(maxPlayer){
                int bestVal = INT_MIN;
                for(int i=0; i<sz*sz; i++){
                    if(start->Nodes[i] != nullptr){
                        int val = minmax(start->Nodes[i], false);
                        bestVal = max(bestVal, val);
                    }
                }
                return bestVal;
            }else{
                int bestVal = INT_MAX;
                for(int i=0; i<sz*sz; i++){
                    if(start->Nodes[i] != nullptr){
                        int val = minmax(start->Nodes[i], true);
                        bestVal = min(bestVal, val);
                    }
                }
                return bestVal;
            }
        }


    public:

        Node* root;
        int num_nodes;
        int max_nodes;

        GameTree(GameState board, int max_n){
            root = new Node(board);
            max_nodes = max_n;
            num_nodes = 0;
            int sz = board.size;

            Queue<Node*> nodeQ;
            nodeQ.push(root);

            Node* crnt;
            while(!nodeQ.isEmpty()){
                crnt = nodeQ.pop();

                if(num_nodes > max_nodes && max_nodes > 0){
                    break;
                }

                if(crnt->board.turnCount == sz*sz){
                    crnt->win = 0;
                    continue;
                }

                int win_mv = -1;
                if(crnt->board.turnCount >= 2*(sz-1)){
                    win_mv = closeToWin(crnt->board);
                }

                if(win_mv == -1){
                    int k = 0;
                    for(int i=0; i<sz; i++){
                        for(int j=0; j<sz; j++){
                            if(crnt->board.grid[i][j] == -1){
                                Node* temp = new Node(crnt->board);
                                temp->board.play(i,j);
                                crnt->Nodes[k] = temp;
                                num_nodes++;
                                nodeQ.push(temp);
                            }
                            k++;
                        }
                    }
                }else{
                    Node* temp = new Node(crnt->board);
                    temp->board.play(win_mv/sz,win_mv%sz);
                    temp->win = (temp->board.hasWon(0)) ? 1 : -1;
                    crnt->Nodes[win_mv] = temp;
                    num_nodes++;
                }
            }
        }

        int numGens(){
            Node* crnt = root;
            int sz = root->board.size;
            while(true){
                bool state = false;
                for(int i=0; i < sz*sz; i++){
                    if(crnt->Nodes[i] != nullptr){
                        crnt = crnt->Nodes[i];
                        state = true;
                        break;
                    }
                }
                if(!state){
                    break;
                }
            }

            return crnt->board.turnCount;
        }

        Vec nextMove(){
            int sz = root->board.size;
            int minmaxVals[sz*sz];

            for(int i=0; i<sz*sz; i++){
                minmaxVals[i] = INT_MIN;
            }

            for(int i=0; i<sz*sz; i++){
                if(root->Nodes[i] != nullptr){
                    minmaxVals[i] = minmax(root->Nodes[i], false);
                }
            }

            int max_idx;
            int maxVal = INT_MIN;
            for(int i=0; i<sz*sz; i++){
                if(minmaxVals[i] > maxVal){
                    maxVal = minmaxVals[i];
                    max_idx = i;
                }
            }
            return Vec(max_idx/sz , max_idx%sz);
        }

        ~GameTree() {
            deleteTree(root);
        }
};

#endif