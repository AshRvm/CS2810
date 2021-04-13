#include <iostream>
#include <string>
using namespace std;

class EDD{
    private:
        string s1;
        string s2;
        int** matrix;                               //matrix storing the edit distances of the two strings
        int flag1 = 0;                              //represents whether strings are assigned or not
        int flag2 = 0;                              //represents whether compdist has been called after assign
    public:
        void assign(string a, string b){
            s1 = a;
            s2 = b;
            flag1 = 1;                              //assign completed
            flag2 = 0;                              //yet to call compdist
            matrix = new int*[a.size()+1];          //creating a matrix of size (n+1)*(m+1)
            for(int i=0;i<=a.size();i++){
                matrix[i] = new int[b.size()+1];
            }
        }

        /*
        ins : inserting a new char in the string to be changed
        del : deleting a char from the string to be changed
        rep : either the two chars are same (cost + 0) or are different (cost + 1) 

        ins is represented by moving rightwards 
        del is represented by moving downwards
        rep is represented by moving towards the bottom right
        */
        void compDist(){
            int ins,del,rep;
            if(flag1 == 0){
                throw("strings not found!");
                return;
            }
            for(int i=0;i<=s2.size();i++){
                matrix[0][i] = i;
            }
            for(int i=1;i<=s1.size();i++){
                matrix[i][0] = i;
                for(int j=1;j<=s2.size();j++){
                    ins = matrix[i][j-1] + 1;
                    del = matrix[i-1][j] + 1;
                    int min = (ins < del) ? ins : del;
                    if(s1[i-1] == s2[j-1]){         //same char, so cost + 0
                        rep = matrix[i-1][j-1];
                    }else{                          //diff char, so cost + 1
                        rep = matrix[i-1][j-1] + 1;
                    }
                    min = (min < rep) ? min : rep;
                    matrix[i][j] = min;             //min of rep, ins and del
                }
            }
            flag2 = 1;
        }
        void dist(){
            if(flag1 == 0){
                throw("strings not found!");
                return ;
            }
            if(flag2 == 0){
                compDist();
            }
            cout<<matrix[s1.size()][s2.size()]<<endl;
        }
        void table(){
            if(flag1 == 0){
                throw("strings not found!");
                return;
            }
            if(flag2 == 0){
                compDist();
            }
            for(int i=1;i<=s1.size();i++){
                for(int j=1;j<=s2.size();j++){
                    cout<<matrix[i][j]<<" ";
                }
                cout<<endl;
            }
        }
};

int main(){
    EDD A;
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        string query;
        cin>>query;
        try{
            if(query == "assign"){
                string a,b;
                cin>>a;
                cin>>b;
                A.assign(a,b);
            }else if(query == "compdist"){
                A.compDist();
            }else if(query == "dist"){
                A.dist();
            }else if(query == "table"){
                A.table();
            }
        }
        catch(const char* message){
            cerr<<message<<endl;
        }
    }
    return 0;
}