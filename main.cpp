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

void addStudent(Node* table[], int &newID, int nsize);
int hashF(int &num, int nsize);
void printStudent(Node* table[], int nsize);

int main() {
  srand(time(0));
  cout << "welcome to studentlist" << endl;
  bool playing = true;
  Node* table[100];
  int currID = 0;
  int size = 100;
  while (playing == true) {
    cout << "would you like to add, print, delete or quit" << endl;
    char input[10];
    cin >> input;
    if (strcmp(input, "ADD") == 0) {//Calls the add function
      //int i = hashFunction(returnID());
      addStudent(table, currID, size);
    }
    else if (strcmp(input, "PRINT") == 0) {//Calls the print function
      printStudent(table, size);
    }
    else if (strcmp(input, "DELETE") == 0) {//Calls the delete function
   
    }
    else if (strcmp(input, "QUIT") == 0) {//Returns false
      playing = false;//Exits while Loop stopping game
    }
  }
}

int hashF(int &num, int nsize) {
  return num%nsize;
}

void addStudent(Node* table[], int &newID, int nsize) {
  cout << "How many students would you like to add" << endl;
  int numStudents;
  cin >> numStudents;
  for (int i = 0; i < numStudents; i++) {
    Node* student = new Node();
    char input[100];
    char input2[100];
    int num = (rand() % 20) + 1;
    int num2 = (rand() % 20) + 1;
    cout << num << endl;
    cout << num2 << endl;
    fstream myfile("firstName.txt");
    fstream lastfile("lastName.txt");
    char firstNameTemp[100];
    int count = 1;
    while (myfile.getline(input,100, '\n')) {
      if (count == num) {
	cout << input << endl;
	strcpy(firstNameTemp, input);
	count++;
      }
      count++;
    }
    myfile.close();
    char lastNameTemp[100];
    int count2 = 1;
    while (lastfile.getline(input2,100, '\n')) {
      if (count2 == num2) {
	cout << input2 << endl;
	strcpy(lastNameTemp, input2);
	count2++;
      }
      count2++;
    }
    lastfile.close();
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    r *= 23;
    while(r > 4){
      r -= 4;
      while(r < 2){
	r += 1;
      }
    }
    cout << firstNameTemp << endl;
    cout << lastNameTemp << endl;
    cout << r << endl;
    cout << newID << endl;
    
    strcpy(student->firstName, firstNameTemp);
    cout << student->firstName;
    strcpy(student->lastName, lastNameTemp);
    student->gpa = r;
    student->id = newID;

    if (table[hashF(newID, nsize)] == NULL) {
      table[hashF(newID, nsize)] = student;
    }

    newID++;
  }
}

void printStudent(Node* table[], int nsize) {
  Node* curr;
  for (int i = 0; i < nsize; i++) {
    curr = table[i];
    cout << curr->firstName << " " << curr->lastName << " ID:" << curr->id << " GPA:" << curr->gpa << endl;
  }
}

void deleteStudent() {

}

int returnID() {

}
