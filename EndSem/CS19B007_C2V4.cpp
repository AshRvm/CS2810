#include <iostream>
using namespace std;

//class that has operations on two graphs
class GraphOps{
    private:
        int size;                                       //number of vertices
        int** G1;                                       //the first graph in adjacency matrix form
        int** G2;                                       //the second graph in adjacency matrix form
        int numEdgesG1;                                 //number of edges in first matrix 
        int numEdgesG2;                                 //number of edges in second matrix
    public:
        GraphOps(int n){
            size = n;
            numEdgesG1 = 0;
            numEdgesG2 = 0;
            G1 = new int*[n];
            G2 = new int*[n];
            for(int i=0;i<n;i++){
                G1[i] = new int[n];
                G2[i] = new int[n];
                for(int j=0;j<n;j++){
                    G1[i][j] = 0;
                    G2[i][j] = 0;
                }
            }
        }
        //assigns values in graph 1 adjacency matrix
        void getEdgesG1(int x, int y){
            G1[x][y] = 1;
            G1[y][x] = 1;
            numEdgesG1++;
        }
        //assigns values in graph 2 adjacency matrix
        void getEdgesG2(int x, int y){
            G2[x][y] = 1;
            G2[y][x] = 1;
            numEdgesG2++;
        }

        //checks if the edge is present in atleast one graph
        void ADD(){
            int result = 0;
            for(int i=0;i<size;i++){
                for(int j=i+1;j<size;j++){
                    if((G1[i][j] == 1) || (G2[i][j] == 1)) result++;
                }
            }
            cout<<result<<endl;
        }

        //checks if the edge is present in G1 and not in G2
        void SUB(){
            int result = 0;
            for(int i=0;i<size;i++){
                for(int j=i+1;j<size;j++){
                    if((G1[i][j] == 1) && (G2[i][j] == 0)) result++;
                }
            }
            cout<<result<<endl;
        }

        //checks if the edge is present in G1 or not in G2
        void DIV(){
            int result = 0;
            for(int i=0;i<size;i++){
                for(int j=i+1;j<size;j++){
                    if((G1[i][j] == 1) || (G2[i][j] == 0)) result++;
                }
            }
            cout<<result<<endl;
        }

        //checks if the edges can satisfy the conditions to form the edges of the graph.. 
        //..obtained from the tensor product of G1 and G2
        void TensorProduct(){
            float result = 0;
            for(int a=0;a<size;a++){
                for(int b=0;b<size;b++){
                    for(int c=0;c<size;c++){
                        for(int d=0;d<size;d++){
                            if((G1[a][c] == 1) && (G2[b][d] == 1)) result += 0.5;
                        }
                    }
                }
            }
            cout<<result<<endl;
        }
};

int main(){
    int n;
    cin>>n;
    GraphOps obj(n);
    int E1,E2;
    cin>>E1;
    for(int i=0;i<E1;i++){
        int x,y;
        cin>>x>>y;
        obj.getEdgesG1(x,y);
    }
    cin>>E2;
    for(int i=0;i<E2;i++){
        int x,y;
        cin>>x>>y;
        obj.getEdgesG2(x,y);
    }
    obj.ADD();
    obj.SUB();
    obj.DIV();
    obj.TensorProduct();
    return 0;
}