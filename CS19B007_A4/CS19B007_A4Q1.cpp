#include <iostream>
#include <string>
using namespace std;

template <class T> 
class Vector{
    private:
        size_t capacity;
        size_t currentSize;
        T* vec;
    public:
        //constructor 1
        Vector(){
            capacity = 1;
            currentSize = 0;
            vec = new T[1];
        }
        //constructor 2
        Vector(size_t c){
            capacity = c;
            currentSize = 0;
            vec = new T[c];
        }
        //constructor 3
        Vector(size_t c, T x){
            capacity = c;
            currentSize = c;
            vec = new T[c];
            for(int i=0;i<c;i++){
                vec[i] = x;
            }
        }
        size_t getCapacity(){                                               //returns the current capacity of the vector 
            return (capacity);
        }
        size_t Size(){                                                      //returns the number of elements in the vector
            return (currentSize);
        }
        void push(T x){                                                     //adds a new element to the top of the vector, and..
            if(currentSize == capacity){                                    //doubles the capacity, if the size = capacity 
                T* temp = new T[capacity*2];
                for(int i=0;i<capacity;i++){                                //storing the old values in a new array
                    temp[i] = vec[i];
                }
                delete vec;                                                 //deletes the old vec array
                vec = temp;
                capacity *= 2;
            }
            vec[currentSize] = x;
            currentSize++;
        }
        void pop(){
            currentSize--;                                                  //equivalent to deleting the last element
        }
        T front(){                                                          //returns the first element in the vector
            if(currentSize == 0) return(-1);
            else return(vec[0]);
        }
        T back(){                                                           //returns the last element in the vector
            if(currentSize == 0) return(-1);
            else return(vec[currentSize-1]);
        }
        T operator [](size_t i){                                            //returns the element in the ith position in the vector
            if(i >= currentSize) return(-1);
            else return(vec[i]);
        }
        void sort(){
            quickSort(0,currentSize-1);                                     //sorts the vector using quick sort
        }
        void quickSort(int left, int right){
            if(left<right){
                int divider = partition(left, right);                       //uses the first element in the vector as a pivot to divide..
                quickSort(left,divider-1);                                  //the vec array into two partitions and further sort and divide.. 
                quickSort(divider+1,right);                                 //until all partitions, when individually sorted, sorts the whole array
            }
        }
        void printVector(){                                                 //prints the elements of the vector
            for(int i=0;i<currentSize;i++){
                cout<<vec[i]<<" ";
            }
            cout<<endl;
        }
    protected:
        int partition(int left, int right){                                 //returns the location, the pivot will have in the finally sorted array
            int pivot = vec[left];
            int j=right;
            for(int i=right;i>left;i--){                                    //traverses from the rightmost element and inserts all elements greater..
                if(vec[i] > pivot){                                         //than the pivot to the right side, by swapping it's position with an..
                    int temp = vec[i];                                      //element smaller than the pivot
                    vec[i] = vec[j];
                    vec[j] = temp;
                    j--;
                }
            }
            vec[left] = vec[j];                                             //finally swaps the pivot with the element smaller than pivot, in..
            vec[j] = pivot;                                                 //the immediate left of the larger partition(partiion of elements with..
            return(j);                                                      //values larger than the pivot)
        }
};

int StringToInt(string s){                                                  //converts a string of numbers into the integer value of the number..
    int result = 0;                                                         //by subtracting 48 from the ASCII values of the respective digits
    for(int i=0;i<s.size();i++){
        result = result*10 + (int)s[i] - 48;
    }
    return result;
}

int main(){
    string response;
    getline(cin,response);
    int count=0;
    int c,x;
    string word = "";
    for(int i=0;i<response.size();i++){                                     //checks for the number of inputs given after "vector" by counting..
        if(response[i] != ' '){                                             //the number of appearences of ' ' int the string
            word = word + response[i];
        }else if((response[i] == ' ') || (i = response.size())){
            count ++;
            if(count == 2){                                                 //gets the value of c, since "vector" increases count to 1..
                c = StringToInt(word);                                      //and the string is not empty yet    
            }
            word = "";
        }
    }
    if((word != "") && (count == 2)){                                       //assigns the value to x, since c is assigned it's value before..
        x = StringToInt(word);                                              //count becomes 2
        count++;
    }else if((word != "") && (count == 1)){                                 //assigns the value to c, sinve c is yet to be assigned, which is..
        c = StringToInt(word);                                              //indicated by count=1
        count++;
    }

    //count represents the number of words in the first line of input
    Vector<int> vector;                                                     //normally constructs the vector
    if(count == 2){
        vector = Vector<int> (c);                                           //construct the vector with one argumnent
    }else if(count == 3){
        vector = Vector<int> (c,x);                                         //construct the vector with two arguments
    }
    int Q;
    cin>>Q;
    for(int i=0;i<Q;i++){
        string query;
        cin>>query;
        if(query == "push"){
            int x;
            cin>>x;
            vector.push(x);
        }else if(query == "element"){
            int i;
            cin>>i;
            cout<<vector[i]<<endl;
        }else if(query == "pop"){
            vector.pop();
        }else if(query == "front"){
            cout<<vector.front()<<endl;
        }else if(query == "back"){
            cout<<vector.back()<<endl;
        }else if(query == "capacity"){
            cout<<vector.getCapacity()<<endl;
        }else if(query == "size"){
            cout<<vector.Size()<<endl;
        }else{
            vector.sort();
            vector.printVector();
        }
    }
}