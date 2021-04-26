#include <iostream>
#include <vector>
using namespace std;

class MineSweep{
    private:
        vector<vector<int> > matrix;                                //representation of the minesweeper board
        vector<vector<bool> > isRevealed;                           //represents whether a block has been opened or not
        int size;                                                   //length of the minesweeper board
        int numMines;                                               //number of mines present
        int blocksRevealed;                                         //number of blocks revealed so far
    public:
        MineSweep(int N){
            size = N;
            blocksRevealed = 0;
            for(int i=0;i<N;i++){
                //initialising the board and the isRevealed vector
                vector<int> tempVector1;
                vector<bool> tempVector2;
                for(int j=0;j<N;j++){
                    tempVector1.push_back(0);
                    tempVector2.push_back(false);
                }
                matrix.push_back(tempVector1);
                isRevealed.push_back(tempVector2);
            }
        }
        //represents mines on the board by assigning values of '-1' to them 
        void assignMines(vector<int> locations){
            numMines = (int)locations.size();
            for(int i=0;i<numMines;i++){
                int row = locations[i]/size;
                int column = locations[i]%size;
                matrix[row][column] = -1;
            }
            //assigns the values of the other blocks
            assignNumbers();
        }
        //returns the number of mine present in the surroundings of the block
        int findValue(int r, int c){
            int count = 0;
            if(r != 0){                                             //checking if a row is present above
                if(matrix[r-1][c] == -1) count++;                   //immediate top element
                if(c != 0){                                         //top right element
                    if(matrix[r-1][c-1] == -1) count++;
                }   
                if(c != size-1){                                    //top left element
                    if(matrix[r-1][c+1] == -1) count++;
                }
            }
            if(r != size-1){                                        //checking if a row is present below
                if(matrix[r+1][c] == -1) count++;                   //immediate bottom element
                if(c != 0){                                         //bottom right element
                    if(matrix[r+1][c-1] == -1) count++;
                }
                if(c != size-1){                                    //bottom left element
                    if(matrix[r+1][c+1] == -1) count++;
                }
            }
            if(c != 0){                                             //immediate left element
                if(matrix[r][c-1] == -1) count++;
            }
            if(c != size-1){                                        //immediate right element
                if(matrix[r][c+1] == -1) count++;
            }
            return (count);
        }

        //assigns values to each non-mine block a value, representing the number of neighbouring mines
        void assignNumbers(){
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if(matrix[i][j] != -1){
                        matrix[i][j] = findValue(i,j);
                    }
                }
            }
        }

        //reveals the 8 neighbours of a 0-block given by the co-ordinates r,c
        //also calls the function recursively if a 0-block is a neighbour of this 0-block
        int neighboursOfZero(int r, int c){
            blocksRevealed++;
            int count = 0;
            if(r != 0){                                             //checks the row above
                if(isRevealed[r-1][c] == false){                    //checks the immediate above element
                    isRevealed[r-1][c] = true;
                    if(matrix[r-1][c] != 0) count ++;
                    else count += neighboursOfZero(r-1,c);
                }
                if(c != 0){                                         //checks the top left element
                    if(isRevealed[r-1][c-1] == false){
                        isRevealed[r-1][c-1] = true;
                        if(matrix[r-1][c-1] != 0) count ++;
                        else count += neighboursOfZero(r-1,c-1);
                    }
                }
                if(c != size-1){                                    //checks the top right element
                    if(isRevealed[r-1][c+1] == false){
                        isRevealed[r-1][c+1] = true;
                        if(matrix[r-1][c+1] != 0) count ++;
                        else count += neighboursOfZero(r-1,c+1);
                    }
                }
            }
            if(r != size-1){                                        //checks the row below
                if(isRevealed[r+1][c] == false){                    //checks the immediate bottom element
                    isRevealed[r+1][c] = true;
                    if(matrix[r+1][c] != 0) count ++;
                    else count += neighboursOfZero(r+1,c);
                }
                if(c != 0){                                         //checks the bottom left element
                    if(isRevealed[r+1][c-1] == false){
                        isRevealed[r+1][c-1] = true;
                        if(matrix[r+1][c-1] != 0) count ++;
                        else count += neighboursOfZero(r+1,c-1);
                    }
                }
                if(c != size-1){                                    //checks the bottom right element
                    if(isRevealed[r+1][c+1] == false){
                        isRevealed[r+1][c+1] = true;
                        if(matrix[r+1][c+1] != 0) count ++;
                        else count += neighboursOfZero(r+1,c+1);
                    }
                }
            }
            if(c != 0){                                             //checks the immediate left element 
                if(isRevealed[r][c-1] == false){
                    isRevealed[r][c-1] = true;
                    if(matrix[r][c-1] != 0) count ++;
                    else count += neighboursOfZero(r,c-1);
                }
            }
            if(c != size-1){                                        //checks the immediate right element
                if(isRevealed[r][c+1] == false){
                    isRevealed[r][c+1] = true;
                    if(matrix[r][c+1] != 0) count ++;
                    else count += neighboursOfZero(r,c+1);
                }
            }
            return (count);
        }

        /*
        Returns : -1 if the block to be revealed is a mine
                   0 if all the blocks have been revealed
                   number of blocks revealed so far
        */
        int reveal(int r, int c){                                   //if the block has not been revealed yet
            if(isRevealed[r][c] == false){
                if(matrix[r][c] == -1){
                    return(-1);
                }else if(matrix[r][c] != 0){
                    blocksRevealed++;
                    isRevealed[r][c] = true;
                    if(blocksRevealed == size*size - numMines) return(0);
                    else return(blocksRevealed);
                }else{
                    isRevealed[r][c] = true;
                    blocksRevealed += neighboursOfZero(r,c);
                    if(blocksRevealed == size*size - numMines) return(0);
                    else return(blocksRevealed);
                }
            }else{                                                  //if the block already has been revealed
                return(blocksRevealed);
            }
        }

        //prints the values of each block in the minesweeper table
        void printValues(){
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    cout<<matrix[i][j]<<" ";
                }
                cout<<endl;
            }
        }
};

int main(){
    int N,M;
    cin>>N>>M;
    MineSweep MS(N);
    vector<int> mineLocations;
    for(int i=0;i<M;i++){
        int temp;
        cin>>temp;
        mineLocations.push_back(temp);
    }
    MS.assignMines(mineLocations);
    int row,column;
    int result = 1;
    while((cin>>row>>column) && (result > 0)){
        result = MS.reveal(row, column);
        if(result > 0) cout<<result<<endl;
    }
    if(result == 0) cout<<"Won"<<endl;
    else if(result == -1) cout<<"Lost"<<endl;
}