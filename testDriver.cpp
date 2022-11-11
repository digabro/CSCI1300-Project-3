#include <iostream>
#include "Inventory.h"
// #include "Item.h"
// #include "location.h"
// #include "person.h"
// #include "npc.h"
// #include "player.h"
#include <cassert>

using namespace std;
 
// sorting Algorithm
void sort(int arr[], int arr_size)
{
    for (int i = 0; i < arr_size - 1; i++){
        for (int j = 0; j < arr_size - i - 1; j++){
            if (arr[j] > arr[j + 1]){
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main(){
    int arr_size = 15;
    int arr[] = {7,8,424,6,3,1,5,1,98,10};
    sort(arr,15);
    for(int i = 0; i < arr_size; i++)
    {
        cout << arr[i] << endl;
    }

    // Inventory
    Inventory testInventory = Inventory(250, 1, 2, 0, 4);
    assert(testInventory.getBuffBucks() == 250);
    assert(testInventory.getPedialyte() == 1);
    assert(testInventory.getEnergyDrink() == 2);
    assert(testInventory.getMuscleMilk() == 0);
    assert(testInventory.getCupOfNoodles() == 4);

    //setters
    testInventory.setBuffBucks(255);
    if(testInventory.getBuffBucks() == 255)
    {
        cout << "1" << endl;
    }
    else
    {
        cout << "-1" << endl;
    }
    /*Expected 
    num_buff_bucks = 255
    */
    testInventory.setEnergyDrink(3);
    if(testInventory.getEnergyDrink() == 2)
    {
        cout << "1" << endl;
    }
    else
    {
        cout << "-1" << endl;
    }
    /*Expected 
    num_energy_drink = 2;
    */

    //Inventory > item setter
    
    


    // Item 
    Item testItem = Item();
    cout << testItem.getDamage() << endl;


    // location 
    
    

return 0;
}
