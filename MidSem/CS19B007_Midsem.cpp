#include <iostream>
using namespace std;

class Book{
    public:
        int bookId;
        int cost;
        int sellingPrice;
        int weight;
        int rating;
        void getBook(int a, int b, int c, int d, int e){
            bookId = a;
            cost = b;
            sellingPrice = c;
            weight = d;
            rating = e;
        }
        int usefulness(){                                           //calculates the usefulness quantity of a book
            return (sellingPrice-cost)*rating;
        }
        int operator <(Book& B){                                    //compares the usefulness of two books
            if(usefulness() < B.usefulness()) return (1);
            else return (0);
        }
};

class BookShelf: public Book{
    private:
        Book* shelf;                                                //stores the book objects
        Book* tempShelf;
        int size;
        int top;                                                    //used to create the shelf
        void swapBooks(int& i, int& j){                             //swaps the books at the..
            Book tempBook = shelf[i];                               //..positions i and j
            shelf[i] = shelf[j];
            shelf[j] = tempBook;
        }

//------------------------------------------------Quick Sort-----------------------------------
        /*
        partition : finds the position, the pivot would have in the sorted array
        quick sort: sorts the shelf of books by using pivot as the first book of the sub-shelf
        sort      : calls for the recursive quick sort 
        */
        int partition(int left, int right){
            Book pivot = shelf[left];
            int j=right;
            for(int i=right;i>left;i--){                                    
                if(pivot < shelf[i]){                                      
                    swapBooks(i,j);
                    j--;
                //swap if they have the same usefulness, but non-pivot book is lighter(more priority)
                }else if(!(shelf[i] < pivot) && (shelf[i].weight < pivot.weight)){
                    swapBooks(i,j);
                    j--;
                }
            }
            swapBooks(left,j);                                            
            return(j);
        }
        void sort(){
            quickSort(0,size-1); 
        }
        void quickSort(int left, int right){
            if(left<right){
                int divider = partition(left, right); 
                quickSort(left,divider-1); 
                quickSort(divider+1,right); 
            }
        }

    public:
        //initialises the shelf with given size
        void getSize(int n){
            size = n;
            top = 0;
            shelf = new Book[n];
            tempShelf = new Book[n];
        }
        //adds a book to the top of the shelf
        void addBook(Book book){
            shelf[top] = book;
            tempShelf[top] = book;
            top ++;
        }
        //sorts the shelf based on weight and usefulness of books
        void arrangeOptimally(){
            sort();
            for(int i=0;i<size;i++){
                cout<<shelf[i].bookId<<" ";
            }
            cout<<endl;
        }
        /*
        Finds the pair of books, whose sum of usefulness is the closest, amongst all other pairs
        of books, to the usefulness of the median book of the shelf, using double pointer method.
        */
        void sumClosestToMedian(){
            sort();
            int medianIndex = (size)/2;
            cout<<shelf[medianIndex].usefulness()<<endl;
            
            //the sum of usefulness, which is closest to that of the median book
            int sumUsefulness = 0;

            //the sum of book ids of the pair that satisfies the condition
            int sumId = 0;

            int median = shelf[medianIndex].usefulness();
            int l=0, r=size-1;                                  //l is the left pointer and r is right pointer
            int diff = 10000000;
            int tempDiff;                                       //abs difference of (diff - usefulness of pair)
            int left=0, right=0;                                //left-left closest book, right-right closest book
            while(l<r){
                //finding abs diff of previous minimum and the usefulness of current pair
                tempDiff = shelf[l].usefulness() + shelf[r].usefulness() - median;
                if(tempDiff < 0) tempDiff = -tempDiff;

                if(tempDiff < diff){                            //current pair is closer than pervious closest pair 
                    left = l;
                    right = r;
                    diff = tempDiff;
                }
                if(shelf[l].usefulness() + shelf[r].usefulness() < median) l++; 
                else r--; 
            }
            sumUsefulness = shelf[left].usefulness() + shelf[right].usefulness();
            sumId = shelf[left].bookId + shelf[right].bookId;
            cout<<sumUsefulness<<endl;
            cout<<sumId<<endl;
        }
};

int main(){
    int n;
    cin>>n;
    int bookId, cost, sellingPrice, weight, rating;
    BookShelf B;
    B.getSize(n);
    for(int i=0;i<n;i++){
        Book A;
        cin>>bookId>>cost>>sellingPrice>>weight>>rating;
        A.getBook(bookId,cost,sellingPrice,weight,rating);
        B.addBook(A);
    }
    char temp;
    cin>>temp;
    if(temp == 'A'){
        B.arrangeOptimally();
    }else if(temp == 's'){
        B.sumClosestToMedian();
    }
    return 0;
}