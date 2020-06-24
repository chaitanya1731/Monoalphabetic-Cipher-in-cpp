#include <iostream>
#include <fstream>
#include <string>
#define NUMS 26
using namespace std;

string LETTERS = "abcdefghijklmnopqrstuvwxyz";
void printMappings(string key){
   cout << "The mappings are - \n";
   for(int i=0; i<LETTERS.length(); i++)
   {
      cout << LETTERS[i] << "-";
      cout << key[i] << "  ";
   }
   cout << "\n";
}

void getTranslatedMessage(ifstream& infile, ofstream& outfile, string line, string key) {
   string message;
   
   if (infile.is_open() && outfile.is_open()) {
      int i, index;
      getline (infile,line);
      
      if(line.length() < 10000){
         printMappings(key);

         for(i = 0; i < line.length(); i++) {
            index = LETTERS.find(line[i]);
            message += key[index];
         }
         // cout << "\nTranslated text is = " << message;
         outfile << message;

         infile.close();
         outfile.close();
      }
      else {
         cout << "Line size greater than 10000";
      }
   }
   else {
      cout << "Unable to open file";
   }
}

string generateKey(){
   int randomSequence[NUMS] = {0}, i = 0, randomNum; 
   bool numExists[NUMS] = {false};
   srand(9);
   while(i != NUMS)
   {
      randomNum = rand() % NUMS;
      if(numExists[randomNum] == false) {
         randomSequence[i++] = randomNum;
         numExists[randomNum] = true;
      }
   }
   
   string key;
   for(int i=0;i<NUMS;i++){
      key += 97 + randomSequence[i];
   }
   return key;
}

int main (int argc, char *argv[]) {
   string line; string tempKey;
   int n = atoi(argv[3]);
   ifstream infile (argv[1]);
   ofstream outfile (argv[2]);
   string key = generateKey();
   
   switch (n) {
      case 1:     // Code for Encryption
         getTranslatedMessage(infile, outfile, line, key);
         break;
      case 0:     // Code for Decryption
         tempKey = key;
         key = LETTERS;
         LETTERS = tempKey;
         getTranslatedMessage(infile, outfile, line, key);
         break;
      default: 
         printf("Choose 1 for encryption or 0 for decryption");
         break;
   }
   return 0;
}