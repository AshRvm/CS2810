#include <iostream>
#include <string>
using namespace std;

class Matrix{
    private:
        int n;                                                  //size of matrices 
        int** matrix;                                           //structure storing the matrix
    public:
        //Custom Constructor initiating the matrix
        Matrix(int size){
            n = size;
            matrix = new int*[n];
            for(int i=0;i<n;i++){
                matrix[i] = new int[n];
            }
        }
        //Prints the matrix 
        void printMatrix(){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    cout<<matrix[i][j]<<" ";
                }
                cout<<endl;
            }
        }
        //Gets the elements of the matrix 
        void getMatrix(int** tempMatrix){
            matrix = tempMatrix;
        }

//-----------------------------------------------------Required Methods--------------------------------------------------
        //Returns array of special sums of each row
        int* SPSUM(){
            int* sums = new int[n];
            for(int i=0;i<n;i++){
                sums[i] = 0;
            }
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    if((i+j)%2 == 0){
                        sums[i] += this->matrix[i][j];
                    }else{
                        sums[i] += this->matrix[j][i];
                    }
                }
            }
            return (sums);
        }

        //Computes product of all row operation results
        long long MOD(){
            long long product = 1;
            for(int i=0;i<n;i++){
                if((i%3) == 0){
                    //finding maximum element of the row
                    int max = matrix[i][0];
                    for(int j=1;j<n;j++){
                        if(matrix[i][j] > max){
                            max = matrix[i][j];
                        }
                    }
                    product *= max;
                }else if((i%3) == 1){
                    //finding minimum element of the row
                    int min = matrix[i][0];
                    for(int j=1;j<n;j++){
                        if(matrix[i][j] < min){
                            min = matrix[i][j];
                        }
                    }
                    product *= min;
                }else{
                    //finding sum of elements of the row
                    int sum = 0;
                    for(int j=0;j<n;j++){
                        sum += matrix[i][j];
                    }
                    product *= sum/n;
                }
            }
            return (product);
        }

        //Creats a new matrix(mat3) which is the right-shifted form of matrix1(this) + matrix2(mat2)
        Matrix MRS(Matrix& mat2, int k){
            Matrix mat3(n);
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    int sum = this->matrix[i][j] + mat2.matrix[i][j];
                    if(j + k >= n){
                        mat3.matrix[(i+((j+k)/n))%n][(j+k)%n] = sum;
                    }else{
                        mat3.matrix[i][(j+k)%n] = sum;
                    }
                }
            }
            return (mat3);
        }

        //Creates a new matrix(mat3) which is the sum of a matrix and transpose of the other
        Matrix MADD(Matrix& mat2, int x){
            Matrix mat3(n);
            if(x == 1){
                for(int i=0;i<n;i++){
                    for(int j=0;j<n;j++){
                        mat3.matrix[i][j] = this->matrix[j][i] + mat2.matrix[i][j];         // mat2 + transpose(mat1)
                    }
                }
            }else{
                for(int i=0;i<n;i++){
                    for(int j=0;j<n;j++){
                        mat3.matrix[i][j] = this->matrix[i][j] + mat2.matrix[j][i];         //mat1 + transpose(mat2)
                    }
                }
            }
            return (mat3);
        }
};
//----------------------------------------------------End of Class and it's implementation-------------------------------

int main(){
    int Q,n;
    cin>>Q>>n;
    string query;

    //creating temporary matrices to take input
    int** tempMatrix1 = new int*[n];
    int** tempMatrix2 = new int*[n];
    for(int i=0;i<n;i++){
        tempMatrix1[i] = new int[n];
    }
    for(int i=0;i<n;i++){
        tempMatrix2[i] = new int[n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>tempMatrix1[i][j];
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>tempMatrix2[i][j];
        }
    }

    Matrix mat1(n), mat2(n);
    mat1.getMatrix(tempMatrix1);        //creates matrix object with values of tempMatrix1
    mat2.getMatrix(tempMatrix2);        //creates matrix object with values of tempMatrix2
    for(int i=0;i<Q;i++){
        cin>>query;
        
        if(query == "SPSUM"){
            int* sums = new int[n];
            sums = mat1.SPSUM();
            for(int i=0;i<n-1;i++){
                cout<<sums[i]<<",";
            }
            cout<<sums[n-1]<<endl;

        }else if(query == "MOD"){
            cout<<mat1.MOD()<<endl;

        }else if(query == "MRS"){
            int k;
            cin>>k;
            Matrix tempMat(n);
            tempMat = mat1.MRS(mat2,k);
            tempMat.printMatrix();

        }else if(query == "MADD"){
            int x;
            cin>>x;
            Matrix tempMat(n);
            tempMat = mat1.MADD(mat2,x);
            tempMat.printMatrix();
        }
    }
    return 0;
}