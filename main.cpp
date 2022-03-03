#include <iostream>
#include <cstring>

using namespace std;

struct Node {
  Node* next = NULL;
  char firstName[100];
  char lastName[100];
  int id;
  float gpa;
};

int main() {
  cout << "welcome to studentlist" << endl;
  bool playing = true;
  Node* table[100];
  while (playing == true) {
    cout << "would you like to add, print, delete or quit" << endl;
    char input[10];
    cin >> input;
    if (strcmp(input, "ADD") == 0) {//Calls the add function
      int i = hashFunction(returnID());
      addStudent(table, i);
    }
    else if (strcmp(input, "PRINT") == 0) {//Calls the print function
      
    }
    else if (strcmp(input, "DELETE") == 0) {//Calls the delete function
   
    }
    else if (strcmp(input, "QUIT") == 0) {//Returns false
      playing = false;//Exits while Loop stopping game
    }
  }
}

int hashFunction(int &num) {
  return num%100;
}

void addStudent(Node* table[], int newID) {
  cout << "Adding studnet" << endl;
  table[newID]->firstName;
  table[newID]->lastName;
  table[newID]->id;
  table[newID]->gpa;
  table[newID]->next = NULL;
  cout << table[newID] << endl;
}

void printStudent() {

}

void deleteStudent() {

}

int returnID() {

}
