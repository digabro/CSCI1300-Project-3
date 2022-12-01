//Lachlan Kotarski and Diego Olin 

#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
using namespace std;

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

bool doesKingWookTrustThee()
{
    string answer;
    string wook_riddles[5][2] = 
    {{"What has keys but no locks space but no room you can enter but you can't exit?","keyboard"},
    {"What gets wet while drying?","towel"},
    {"What has a tongue but can't talk?","shoe"},
    {"What bus could cross the ocean?","columbus"},
    {"What disappears as soon as you say its name?","silence"}};
    srand(time(NULL));
    int randNum = rand() % 100; 
    cout << "Grettings traveler! I am King Wook, the sorcerer of Boulder who lives under the Broadway Bridge. I am able to protect you if you solve my riddle." << endl;
    if(randNum <= 0 && randNum <=20){
        cout << wook_riddles[0][0] << endl;
        cin >> answer;
        if(answer == wook_riddles[0][1]){
            cout << "King Wook: You got it correct my friend! I shall now help you with your quest. " << endl;
            return true; 
        }
        else{
            cout << "King Wook: Sorry please try again some other time. " << endl;
            return false;
        }
    }
    if(randNum <= 21 && randNum <=40){
        cout << wook_riddles[1][0] << endl;
        cin >> answer;
        if(answer == wook_riddles[1][1]){
            cout << "King Wook: You got it correct my friend! I shall now help you with your quest. " << endl;
            return true; 
        }
        else{
            cout << "King Wook: Sorry please try again some other time. " << endl;
            return false;
        }
    }
    if(randNum <= 41 && randNum <=60){
        cout << "King Wook: You got it correct my friend! I shall now help you with your quest. " << endl;
        cout << wook_riddles[2][0] << endl;
        cin >> answer;
        if(answer == wook_riddles[2][1]){
            return true; 
        }
        else{
            cout << "King Wook: Sorry please try again some other time. " << endl;
            return false;
        }
    }
    if(randNum <= 61 && randNum <=80){
        cout << wook_riddles[3][0] << endl;
        cin >> answer;
        if(answer == wook_riddles[3][1]){
            cout << "King Wook: You got it correct my friend! I shall now help you with your quest. " << endl;
            return true; 
        }
        else{
            cout << "King Wook: Sorry please try again some other time. " << endl;
            return false;
        }
    }
    if(randNum <= 81 && randNum <=100){
        cout << wook_riddles[4][0] << endl;
        cin >> answer;
        if(answer == wook_riddles[4][1]){
            cout << "King Wook: You got it correct my friend! I shall now help you with your quest. " << endl;
            return true; 
        }
        else{
            cout << "King Wook: Sorry please try again some other time. " << endl;
            return false;
        }
    }
    return false;
}

bool printHistoryQuestions()
{

    int num_history_qs = 6;
    int num_history_cols = 6;
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
return false;
}

bool printBusinessQuestions()
{

    const static int num_business_qs = 3;
    const static int num_business_cols = 6;
    string answer;
    // answers to each question
    int score = 0;
    // allows us to create variables arrays with these variables as the arguments in the function. 

    // business college:     Q#&Q  a   b   c   d   A
    string business[num_business_qs][num_business_cols] =
   {{"1. When should you invest?","a. When the stock starts high.","b. When the stock starts low","c. When the stock is green which means go.","d. When the stock is unhappy.","b"}, 
    {"2. Is 1 greater than 0?","a. Yes","b. No","c. Maybe","d. Is this test curved?","a"},
    {"3. What letter does Blue start with?","a. B","b. g","c. z","d. 3","a"}};
for(int i = 0; i < num_business_qs; i++){
    if(i == 0){
        cout << "Welcome to the college of Business. Here's a quiz if you really know your stuff.(Select the answer that makes the most sense.)" << endl;
        cout << endl;
    }
    for(int j = 0; j < num_business_cols - 1; j++){// doesn't print answer
        cout << business[i][j] << endl; 
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
    if(isAnswerRight(answer, i, num_business_cols - 1, business) == 1){
        score = score + 1;
    }
    if(i == num_business_qs - 1)
    {
        cout << "You scored " << score << "/3 on the Business quiz. Which means you ";
        if(score >= 2){
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
return false;
}

bool printBiologyQuestions()
{
    const static int num_biology_qs = 4;
    const static int num_biology_cols = 6;
    string answer;
    // answers to each question
    int score = 0;
    // allows us to create variables arrays with these variables as the arguments in the function. 

    // business college:     Q#&Q  a   b   c   d   A
    string biology[num_biology_qs][num_biology_cols] =
   {{"1. ___________ is the powerhouse of the cell.","a. Mitochondria","b. Nucleus","c. DNA","d. ATP","a"}, 
    {"2. Is it okay to shake a baby?","a. Hell yeah.","b. NO.","c. I mean don't knock it unitl you try it...","d. None of the above.","b"},
    {"3. What is the thigh bone called?","a. phlanges","b. fibula","c. tibia","d. femur","d"},
    {"4. What does the frontal lobe do?","a. Motor function","b. controls the eyes","c. controls the mouth ","d. main computing","a"}};
for(int i = 0; i < num_biology_qs; i++){
    if(i == 0){
        cout << "Welcome to the college of Pre-Med. Today we will be learning the history of this school and Boulder, Colorado." << endl;
        cout << endl;
    }
    for(int j = 0; j < num_biology_cols - 1; j++){// doesn't print answer
        cout << biology[i][j] << endl; 
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
    if(isAnswerRight(answer, i, num_biology_cols - 1, biology) == 1){
        score = score + 1;
    }
    if(i == num_biology_qs - 1)
    {
        cout << "You scored " << score << "/4 on the Biology quiz. Which means you ";
        if(score >= 3){
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
return false;
}

bool printMathQuestions()
{
    const static int num_math_qs = 10;
    const static int num_math_cols = 6;
    string answer;
    // answers to each question
    int score = 0;
    // allows us to create variables arrays with these variables as the arguments in the function. 

    // business college:     Q#&Q  a   b   c   d   A
    string math[num_math_qs][num_math_cols] =
   {{"1. Solve 4 x 4.","a. 1","b. 4","c. 16","d. 20","c"}, 
    {"2. Solve 9 x 9.","a. 63","b. 72","c. 81","d. 90","c"},
    {"3. Solve 6 x 6.","a. 36","b. 33","c. 27","dd. 39","a"},
    {"4. If f(x) = 4x^5 + 7x^3 - 2x, solve f`(x). Pick one of the answers below.","a. f`(x) = 20x + 22x^2 - 4.","b. F(x) = x^5 + (7/4)x^4 -x^2 + c.","c. f`(x) = 20x^4 + 21x^2 - 2. ","d. f`(x) = x^5 + (7/4)x^4 -x^2 + c.","c"},
    {"5. Solve 2 + 2. ","a. 1","b. 2","c. 4","d. 5","c"},
    {"6. Solve 2 - 2. ","a. -1","b. 0","c. 1.99","d. 2.01","b"},
    {"7. Solve 7 x 0. ","a. 7","b. 0","c. 1","d. none of the above","b"},
    {"8. Solve 7 x 1. ","a. 7","b. 1","c. 0 ","d. none of the above.","a"},
    {"9. Solve 7 x 0.001.","a. 0.07","b. 1","c. 0.7","d. 0.007","d"},
    {"10. Solve 100 - 4(7-5)^2.","a. 4","b. 36","c. 84","d. 0","c"}};
for(int i = 0; i < num_math_qs; i++){
    if(i == 0){
        cout << "Welcome to the college of Mathematics. Here's a quiz if you really know your stuff. (Select the answer that makes the most sense)" << endl;
        cout << endl;
    }
    for(int j = 0; j < num_math_cols - 1; j++){// doesn't print answer
        cout << math[i][j] << endl; 
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
    if(isAnswerRight(answer, i, num_math_cols - 1, math) == 1){
        score = score + 1;
    }
    if(i == num_math_qs - 1)
    {
        cout << "You scored " << score << "/10 on the Math quiz. Which means you ";
        if(score >= 7){
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
return false;
}

int main(){

    doesKingWookTrustThee();


    return 0;
}