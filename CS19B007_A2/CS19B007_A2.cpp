#include <iostream>
#include <string>
using namespace std;

class Matrix{
    protected:
        int n;                                                     //number of rows
        int m;                                                     //number of columns
        int** matrix;
    public:
        void createMatrix(int numRows, int numColumns){
            n = numRows;
            m = numColumns;
            matrix = new int*[n];
            for(int i=0;i<n;i++){
                matrix[i] = new int[m];
            }
        }

        int binarySearch(int x, int k){
            if(matrix[k][0] > x){                                 //checks if element less than or equal to x exists in the row
                return (-1);
            }
            int index = 0;                                        //largest index of element of largest element of row less than or equal to x
            int start = 0;
            int end = m-1;
            while(start <= end){
                int j = (start+end)/2;                            //middle index
                if(x >= matrix[k][j]){                            //checks 2nd half of row
                    index = j;
                    start = j+1;
                }else{                                            //checks 1st half of row
                    end = j-1;
                }
            }
            return (index);
        }

        int* matrixSearch(int x){
            int* indices = new int[2];
            for(int i=0;i<n;i++){
                if((x > matrix[i][m-1]) || (x < matrix[i][0])){   //checks whether x can exist within the row by checking the max and min values
                    continue;
                }else{
                    int start = 0;
                    int end = m-1;
                    while(start < end){
                        int j = (start+end)/2;
                        if(x <= matrix[i][j]){
                            end = j;
                        }else{
                            start = j+1;
                        }
                    }
                    if(matrix[i][end] == x){
                        indices[0] = i;
                        indices[1] = end;
                        return (indices);
                    }
                }
            }
            indices[0] = -1;
            indices[1] = -1;
            return (indices);
        }
        void getMatrix(int** tempMatrix){
            matrix = tempMatrix;
        }
};

class MatrixMedian : public Matrix{
    public:
        long long upperBound(int x,int k){                       //returns index of smallest element larger than x, by using the index of ...
            long long temp = this->binarySearch(x,k);            // ... largest element less than or equal to x
            if(temp == m-1){                                     //no element, strictly greater than x
                return(-1);
            }else{
                return(temp+1);
            }
        }

        /*
        Finds the median of row-wise sorted matrix, using binary search on the set of integers, ranging from the minimum element of the matrix 
        to the maximum element (can be found in O(n)), using the property, the number of elements, smaller than and greater than the median, 
        must atmost be (m*n + 1)/2 each.
        The number of elements less than a number, in a row can be found in O(logm) using upperBound method and for the whole matrix can be found in O(n*logm).
        The median in the range of numbers can be found in atmost log(2^32) == 32 operations. 
        )
        */
        int findMedian(){
            long long min = matrix[0][0];                      //represents the smallest element of the matrix
            long long max = matrix[0][m-1];                    //represents the largest element of the matrix
            for(int i=1;i<n;i++){
                if(matrix[i][0] < min){
                    min = matrix[i][0];
                }
            }
            for(int i=1;i<n;i++){
                if(matrix[i][m-1] > max){
                    max = matrix[i][m-1];
                }
            }
            int numLT = (m*n + 1)/2;                            //number of elements in matrix that should be less than the median
            int count = 0;                                      //number of elements less the the number being checked
            long long mid = (min+max)/2;
            while(max > min){                                   //terminates when max == min-1
                mid = (min+max)/2;
                if(max+min<0){                                     //mid = floor[(max + min)/2]
                    mid--;
                }
                count = 0;
                for(int i=0;i<n;i++){
                    if(this->upperBound(mid,i) == -1){          //all elements in the row are less than or equal to the number being checked
                        count += m;
                    }else{
                        count += this->upperBound(mid,i);
                    }
                }
                if(count < numLT){                              //checking lower half, since count exceeds the required count(numLT)
                    min = mid+1;
                }else{                                          //checking upper half, since count is less than or equal to required count
                    max = mid;
                }
            }
            if(count >= numLT){                                 //returns min as the next itteration would have made mid = min
                return (min);
            }else{                                              //returns max as the next itteration would have made mid = max
                return (max);
            }                      
        }
};

int main(){
    int n,m;
    cin>>n>>m;
    int** tempMatrix = new int*[n];
    for(int i=0;i<n;i++){
        tempMatrix[i] = new int[m];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>tempMatrix[i][j];
        }
    }
    MatrixMedian matrix;
    matrix.createMatrix(n,m);
    matrix.getMatrix(tempMatrix);
    
    int Q;
    cin>>Q;
    for(int i=0;i<Q;i++){
        string query;
        cin>>query;
        if(query == "BS"){
            int x,k;
            cin>>x>>k;
            cout<<matrix.binarySearch(x,k)<<endl;
        }else if(query == "MS"){
            int x;
            int* indices = new int[2];
            cin>>x;
            indices = matrix.matrixSearch(x);
            cout<<indices[0]<<" "<<indices[1]<<endl;
        }else{
            cout<<matrix.findMedian()<<endl;
        }
    }
    return 0;
}