#include "Inventory.h"
#include "Item.h"
#include "location.h"
#include "person.h"
#include "npc.h"
#include "player.h"
#include <iostream>
#include <string>

using namespace std;
 
// sorting Algorithm
void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main(){
    int n=15;
    int arr[n] = {7,8,424,6,3,1,5,1,98,10};
    sort(arr,15);
    for(int i = 0; i < n; i++)
    {
      cout << arr[i] << endl;
    }



    
return 0;
}
