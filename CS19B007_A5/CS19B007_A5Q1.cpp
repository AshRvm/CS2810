#include <iostream>
#include <string>
using namespace std;

class BloomBrain{
    private:
        int numRooms;
        int lastUnoccupiedRoom;
        int numMembers;
        bool* isEmpty;
        
        //-----------------------------------------------Maximum subarray----------------------------------------------------------
        /*
        Finds the maximum subarray of a given array, using modified divide and conquer algorithm.
        start - starting index of the block
        end   - ending index of the block
        MS    - maximum sum of the block
        BS    - block sum
        PS    - Prefix sum (sum of maximum subarray which starts from start)
        SS    - Suffix sum (sum of maximum subarray which ends at end)
        */
        void maxSubArray(int* array, int& MS, int& BS, int& PS, int& SS, int& start, int& end){
            if(start == end){                                               //base case with only 1 element in the block
                MS = array[start];
                BS = array[start];
                PS = array[start];
                SS = array[start];
            }else{
                int MS1, MS2, BS1, BS2, PS1, PS2, SS1, SS2, start1, start2, end1, end2;
                start1 = start;
                end2 = end;
                if((start+end)%2 == 0) start2 = (start+end)/2;              //if size is odd, assigns middle element as start of 2nd block
                else start2 = (start+end)/2 + 1;                            //else divide equally 
                end1 = start2 - 1;
                maxSubArray(array, MS1, BS1, PS1, SS1, start1, end1);
                maxSubArray(array, MS2, BS2, PS2, SS2, start2, end2);
                BS = BS1 + BS2;                                             //block sum will be the sum of block sums of the two blocks
                PS = (PS1 > PS2+BS1)? PS1 : PS2+BS1;                        //prefix sum = max(prefix sum1 , prefix sum2 + block sum1)
                SS = (SS2 > SS1+BS2)? SS2 : SS1+BS2;                        //suffix sum = max(suffix sum2 , suffix sum1 + block sum2)
                MS = PS2 + SS1;                                             //maximum sum = max(maximum sum1, maximum sum2, overlapping sum)..
                if(MS < MS1) MS = MS1;                                      //..where overlapping sum = prefix sum2 + suffix sum1
                if(MS < MS2) MS = MS2;
            }
        }

        //----------------------------------------------Number of inversions-------------------------------------------------------
        /*
        Finds the number of inversions in the array, to be made to sort it
        inversionCount - function that sets the recursive calls 
        divide         - divides the array into two blocks and adds the count values returned by each block..
                         ..along with the count value returned by the merge function
        merge          - merges the two blocks and computes the increment in count values on doing so, by using..
                         ..an incremental process  
        */
        long long inversionCount(int* array, int size){
            int* temp = new int[size];                                      //temp array used to represent divided arrays
            return divide(array, temp, 0, size-1);
        }
        long long divide(int* array, int* temp, int start, int end){
            int mid = (start+end)/2;                                        //divider of the array
            long long count = 0;
            if(start<end){
                count += divide(array, temp, start, mid);                   //block1 consisting of array[start..mid]
                count += divide(array, temp, mid+1, end);                   //block2 consisting of array[mid+1..end]
                count += merge(array, temp, start, mid+1, end);             //merging the two divided blocks
            }
            return count;
        }
        long long merge(int* array, int* temp, int start1, int start2, int end){
            long long count = 0;
            int i=start1, j=start2, k=start1;                               //start1 is starting index of block1 and..
            while((i < start2) && (j <= end)){                              //..start2 is starting index of block2
                if(array[i] <= array[j]){
                    temp[k] = array[i];
                    k++;
                    i++;
                }else{
                    temp[k] = array[j];
                    k++;
                    j++;
                    count += start2 - i;                                    //since all remaining elements in block1..
                }                                                           //..will be greater than block2[j]
            }
            while(i < start2){                                              //inserting remaining elements into main block
                temp[k] = array[i];
                k++;
                i++;
            }
            while(j <= end){                                                //inserting remaining elements into main block
                temp[k] = array[j];
                k++;
                j++;
            }
            for(int i=start1;i<=end;i++){                                   //replacing initial array with merged blocks
                array[i] = temp[i];
            }
            return count;
        }
    public:
        int* seraphicValues;
        
        //Constructor - assuming initially all rooms are filled(as mentioned in the question)
        BloomBrain(int n){
            numRooms = n;
            seraphicValues = new int[n];
            for(int i=0;i<n;i++) seraphicValues[i] = 0;
            lastUnoccupiedRoom = -1;
            numMembers = n;
            isEmpty = new bool[n];
            for(int i=0;i<n;i++) isEmpty[i] = false;
        }
        void printSeraphicValues(){
            for(int i=0;i<numRooms;i++){
                cout<<seraphicValues[i]<<" ";
            }
            cout<<endl;
        }
        long long update(){
            long long count=0;
            int size = 0;
            int* tempArray = new int[numRooms];
            for(int i=0;i<numRooms;i++){
                if((isEmpty[i] == false) || (seraphicValues[i] != 0)){          //creats an array of the ..
                    tempArray[size] = seraphicValues[i];                        //..occupied rooms
                    size++;
                }
            }
            count = inversionCount(tempArray, size);
            return (count);
        }
        void join(int seraphicValue){
            numMembers++;
            seraphicValues[lastUnoccupiedRoom] = seraphicValue;                 //places the new member in the.. 
            isEmpty[lastUnoccupiedRoom] = false;                                //..last unoccupied room
            int i=lastUnoccupiedRoom;
            while(i >= 0){                                                      //finding new last..
                if(isEmpty[i] == true){                                         //..unoccupied room
                    lastUnoccupiedRoom = i;
                    break;
                }
                i--;
            }
        }
        void leave(int room){                                                   //updates the last unoccupied..
            numMembers--;                                                       //..room and marks the room as..
            seraphicValues[room] = 0;                                           //..empty
            isEmpty[room] = true;
            if(lastUnoccupiedRoom < room) lastUnoccupiedRoom = room;
        }
        int occupied(){                                                         //return the number of members
            return (numMembers);
        }
        int play(){                                                             //returns the maximum sum of ..
            int MS, BS, PS, SS, start=0, end = numRooms-1;                      //..seraphic values from sub-..
            maxSubArray(seraphicValues, MS, BS, PS, SS, start, end);            //..arrays of the original array
            return (MS);
        }
};

int main(){
    int N,Q;
    cin>>N>>Q;
    BloomBrain A(N);
    string query;
    for(int i=0;i<Q;i++){
        cin>>query;
        if(query == "update"){
            for(int j=0;j<N;j++){
                cin>>A.seraphicValues[j];
            }
            cout<<A.update()<<endl;
        }else if(query == "join"){
            int s;
            cin>>s;
            A.join(s);
        }else if(query == "leave"){
            int idx;
            cin>>idx;
            A.leave(idx);
        }else if(query == "occupied"){
            cout<<A.occupied()<<endl;
        }else if(query == "play"){
            cout<<A.play()<<endl;
        }
    }
    return 0;
}
