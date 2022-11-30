#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int split(int j)
{
    //ex
    return j;
}

bool isValidAnswer(string answer){
    if(answer == "a"||answer == "b"||answer == "c"||answer == "d"){
        return true;
    }
    else{
        return false;
    }
}

bool isAnswerRight(string answer, int i, int j, string array[6][6]){

    if(answer == array[i][j]){
        return true;
    }
    else{
        return false;
    }
}

bool printHistoryQuestions()
{

    int num_history_qs = 6;
    int num_history_cols = 6;
    int i = 0; 
    string answer;
    // answers to each question
    int score = 0;
    // allows us to create variables arrays with these variables as the arguments in the function. 

    // history college:     Q#&Q  a   b   c   d   A
    string history[7][6] =
   {{"1. When was the town of Bolder built?","a. 1878","b. 1865","c. 1892","d. 1871","d"}, 
    {"2. What year was the University of Colorado-Boulder founded?","a. 1676","b. 1870","c. 1895","d. 1909","b"},
    {"3. When was the first Ralphie Buffalo introduced to the university?","a. 1919","b. 1957","c. 1892","d. 1909","b"},
    {"4. Why are the flat irons named the flat irons?","a. The pioneers saw that it was flat and filled with with iron.","b. The pioneers thought that it looked flat like an iron used to iron clothes.","c. The pioneers thought they were magnetic and thought their magnetic field would protect them from the sun.","d. When Boulder was founded, there was a large iron deposit found in the mountains.","b"},
    {"5. Who was Alfred Packer?","a. He was a settler on an expedition and became a cannibal after the trip went sour.","b. Famous rooster.","c. Famous Boulderite.","d. none of the above.","a"},
    {"6. Which musician referenced Boulder in one of his songs?","a. Johnny Cash.","b. The Highway Men.","c. Both a & b.","d. None of the above.","c"}};
for(int i = 0; i < num_history_qs; i++){
    if(i == 0){
        cout << "Welcome to the college of History. Today we will be learning the history of this school and Boulder, Colorado." << endl;
        cout << endl;
    }
    for(int j = 0; j < 5; j++){// doesn't print answer
        cout << history[i][j] << endl; 
        if(j==0)
        {
            cout << endl;
        }
        if(j==4)
        {
            cout << endl;
        }
    }
    cin >> answer;
    while(isValidAnswer(answer) == 0){
        cout << "Invalid Input. Please try again." << endl;
        cin >> answer;
    }
    if(isAnswerRight(answer, i, 5, history) == 1){
        score = score + 1;
    }
    if(i == num_history_qs - 1)
    {
        cout << "You scored " << score << "/6 on the history quiz. Which means you ";
        if(score >= 5){
            cout << "passed the quiz!" << endl;
            cout << endl; 
            return true;  
        }
        else{
            cout << "didn't pass the quiz, please try again." << endl;
            cout << endl;
            return false;
        }
    }  
}
}





int main(){
    
    printHistoryQuestions();

    return 0;
}