#include <iostream>
#include <cassert>
#include "Inventory.h"
#include "Item.h"
#include "location.h"
#include "person.h"
#include "npc.h"
#include "player.h"

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
    int n=10;
    int arr[] = {7,8,424,6,3,1,5,1,98,10};
    sort(arr,10);
    for(int i = 0; i < n; i++)
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

    
    Person testPerson1=Person();   //testing person class
    assert(testPerson1.getName()=="");
    assert(testPerson1.getHp()==0);
    assert(testPerson1.getArmor()==0);
    testPerson1.setArmor(10);   //setting them to other 
    testPerson1.setName("Name1");
    testPerson1.setHp(20);
    assert(testPerson1.getName()=="Name1");
    assert(testPerson1.getHp()==20);
    assert(testPerson1.getArmor()==10);

    Player testPlayer1=Player();   //testing player class
    assert(testPlayer1.getSkillLevel()==0);
    assert(testPlayer1.getMaxSkillLevel()==100);
    testPlayer1.setSkillLevel(30);
    assert(testPlayer1.getSkillLevel()==30);
    
    Npc testNpc1=Npc();   //testing npc class
    assert(testNpc1.getAgression()==0);
    assert(testNpc1.getAttack1()==0);
    testNpc1.setAgression(true);
    testNpc1.setAttack1(25);
    assert(testNpc1.getAgression()==1);
    assert(testNpc1.getAttack1()==25);
    assert(testNpc1.getAttack2()==0);

    Item testItem1=Item();  //testing item class
    assert(testItem1.getItemName()=="");
    assert(testItem1.getItemType()=="");
    assert(testItem1.getItemCost()==0);
    assert(testItem1.getItemIndex()==0);
    assert(testItem1.getDamage()==0);
    assert(testItem1.getProtection()==0);
    assert(testItem1.getDurability()==0);
    assert(testItem1.getMaxQuantity()==0);
    assert(testItem1.getQuantity()==0);
    testItem1.setItemName("Name1");
    testItem1.setItemType("Weapon");
    testItem1.setItemCost(25);
    testItem1.setItemIndex(1);
    testItem1.setDamage(2);
    testItem1.setProtection(10);
    testItem1.setDurability(100);
    testItem1.setMaxQuantity(3);
    testItem1.setQuantity(1);
    assert(testItem1.getItemName()=="Name1");
    assert(testItem1.getItemType()=="Weapon");
    assert(testItem1.getItemCost()==25);
    assert(testItem1.getItemIndex()==1);
    assert(testItem1.getDamage()==2);
    assert(testItem1.getProtection()==10);
    assert(testItem1.getDurability()==100);
    assert(testItem1.getMaxQuantity()==3);
    assert(testItem1.getQuantity()==1);

    Location testLoc1=Location();  //testing location class
    assert(testLoc1.getName()=="");
    assert(testLoc1.getDifficulty()==0);
    assert(testLoc1.getSymbol()==' ');
    testLoc1.setName("Location1");
    testLoc1.setDifficulty(2);
    testLoc1.setSymbol('W');
    assert(testLoc1.getName()=="Location1");
    assert(testLoc1.getDifficulty()==2);
    assert(testLoc1.getSymbol()=='W');

    //testing add item function 
    Inventory testInventory3=Inventory();
    Item item1=Item();
    item1.setItemName("Item1");
    Item item2=Item();
    item2.setItemName("Item2");
    Item item3=Item();
    item3.setItemName("Item3");

    testInventory3.setBuffBucks(20);
    testInventory3.addItem(item2); //trying to fix this function
    assert(testInventory3.getItem(0).getItemName()=="Item2");//getting an item from the item array and calling its name 
    item3.setItemCost(10);
    testInventory3.buyItem(item3);
    assert(testInventory3.getBuffBucks()==10);//cost of item3 gets reduced from total buffbucks


return 0;
}
