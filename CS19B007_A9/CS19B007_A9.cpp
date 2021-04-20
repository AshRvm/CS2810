#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Currency{
    private:
        int numColours;                             //number of colours used
        int numCurrencies;                          //number of countries
        vector<int> colour;                         //vector storing colour of a country
        vector<vector<int> > colourGraph;           //vector storing the colour graph
        vector<vector<float> > currencies;          //vector storing currency multipliers
        vector<vector<float> > multipliers;         //vector storing the multipiers given the restraint of colours
    public:
        Currency(int C){
            numColours = C;
            //initialising the colours graph
            for(int i=0;i<C;i++){
                vector<int> tempVector;
                colourGraph.push_back(tempVector);
            }
        }
        //function to add edges to the colour graph
        void addColourEdge(int a, int b){
            colourGraph[a].push_back(b);
            colourGraph[b].push_back(a);
        }
        //initialises the currencies and multipliers vectors 
        void getNumCurrencies(int N){
            numCurrencies = N;
            for(int i=0;i<N;i++){
                vector<float> tempVector;
                currencies.push_back(tempVector);
                multipliers.push_back(tempVector);
                for(int j=0;j<N;j++){
                    if(i==j) multipliers[i].push_back(1);
                    else multipliers[i].push_back(-1);
                }
            }
        }
        //assigns colour c to the (colour.size)th country
        void assignColour(int c){
            colour.push_back(c);
        }
        //assigns the values of the currency converter matrix
        void assignConversions(vector<vector<float> > &mat){
            currencies = mat;
        }
        //function stating whether direct exchange between two colour is legal or not
        bool isLegal(int c1, int c2){
            if(c1 == c2) return (true);
            for(int i=0;i<(int)colourGraph[c1].size();i++){
                if(colourGraph[c1][i] == c2){
                    return (true);
                }
            }
            return (false);
        }
        /*
        Creats a new matrix storing the maximum currency multiplier between two countries, either via direct exchange or indirect
        First set of for loops to initialise multipliers matrix with the legal direct exchanges
        Second set of for loops to check and modify the currency multiplier, if there exists a higher multiplier via indirect exchange
        Third set of for loops to check for increasing loops in a path, thus making the maximum multiplier infinity
        */
        void assignMultipliers(){
            for(int i=0;i<numCurrencies;i++){
                for(int j=0;j<numCurrencies;j++){
                    if(isLegal(colour[i],colour[j])){
                        multipliers[i][j] = currencies[i][j];
                    }
                }
            }
            for(int k=0;k<numCurrencies;k++){
                for(int j=0;j<numCurrencies;j++){
                    for(int i=0;i<numCurrencies;i++){
                        if((multipliers[i][k] != -1) && (multipliers[k][j] != -1)){
                            if(multipliers[i][k] * multipliers[k][j] > multipliers[i][j]){
                                multipliers[i][j] = multipliers[i][k] * multipliers[k][j];
                            }
                        }
                    }
                }
            }
            for(int k=0;k<numCurrencies;k++){
                if(multipliers[k][k] > 1){
                    for(int i=0;i<numCurrencies;i++){
                        for(int j=0;j<numCurrencies;j++){
                            if((multipliers[i][k] != -1) && (multipliers[k][j] != -1)){
                                multipliers[i][j] = -2;
                            }
                        }
                    }
                }
            }
        }
        //prints the maximum currency multiplier in an exchange from country s to country t, starting with X units
        void finalValue(int s, int t, int x){
            if(multipliers[s][t] == -1){
                cout<<-1<<endl;
            }else if(multipliers[s][t] == -2){
                cout<<"INF"<<endl;
            }else{
                //print out the floating point with precision 3
                cout<<fixed<<setprecision(3)<<(x*multipliers[s][t])<<endl;
            }
        }
        void printMultipliers(){
            for(int i=0;i<numCurrencies;i++){
                for(int j=0;j<numCurrencies;j++){
                    cout<<multipliers[i][j]<<" ";
                }
                cout<<endl;
            }
        }
        void printCurrencies(){
            for(int i=0;i<numCurrencies;i++){
                for(int j=0;j<numCurrencies;j++){
                    cout<<currencies[i][j]<<" ";
                }
                cout<<endl;
            }
        }
};

int main(){
    int C;
    cin>>C;
    Currency obj(C);
    int m;
    cin>>m;
    int u,v;
    for(int i=0;i<m;i++){
        cin>>u>>v;
        obj.addColourEdge(u,v);
    }
    int N;
    cin>>N;
    obj.getNumCurrencies(N);
    for(int i=0;i<N;i++){
        int c;
        cin>>c;
        obj.assignColour(c);
    }
    vector<vector<float> > mat;
    for(int i=0;i<N;i++){                           //initialising the matrix
        vector<float> tempVector;
        mat.push_back(tempVector);
    }
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            float temp;
            cin>>temp;
            mat[i].push_back(temp);
        }
    }
    obj.assignConversions(mat);                     //assigning the conversions matrix
    obj.assignMultipliers();                        //Modifying the multipliers via indirect exchanges
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        int s,t,X;
        cin>>s>>t>>X;
        obj.finalValue(s,t,X);
    }
}