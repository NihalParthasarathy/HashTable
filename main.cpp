#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <time.h>
#include <limits>

using namespace std;

struct Node {
  Node* next = NULL;
  char firstName[100];
  char lastName[100];
  int id;
  float gpa;
};

void addStudent(Node* table[], int newID);

int main() {
  srand(time(0));
  cout << "welcome to studentlist" << endl;
  bool playing = true;
  Node* table[100];
  while (playing == true) {
    cout << "would you like to add, print, delete or quit" << endl;
    char input[10];
    cin >> input;
    if (strcmp(input, "ADD") == 0) {//Calls the add function
      //int i = hashFunction(returnID());
      int i = 5;
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
  char input[100];
  char input2[100];
  int num = (rand() % 20) + 1;
  int num2 = (rand() % 20) + 1;
  cout << num << endl;
  cout << num2 << endl;
  fstream myfile("firstName.txt");
  fstream lastfile("lastName.txt");
  /*myfile.open("firstName.txt", ios::in);
  if (!myfile) {
    cout << "no file" << endl;
  }
  else {
    for (int i = 0; i < num; i++) {
      cin >> input;
    }
  }
  cout << input << endl;
  myfile.close();*/
  int count = 1;
  while (myfile.getline(input,100, '\n')) {
      if (count == num) {
	cout << input << endl;
	count++;
      }
      count++;
  }
  int count2 = 1;
  while (lastfile.getline(input2,100, '\n')) {
    if (count2 == num2) {
      cout << input2 << endl;
      count2++;
    }
    count2++;
  }
  
  /*table[newID]->firstName;
  table[newID]->lastName;
  table[newID]->id;
  table[newID]->gpa;
  table[newID]->next = NULL;
  cout << table[newID] << endl;*/
}

void printStudent() {

}

void deleteStudent() {

}

int returnID() {

}
