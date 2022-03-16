#include <iostream>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <time.h>
#include <limits>
#include <iomanip>

using namespace std;

struct Node {
  Node* next = NULL;
  char firstName[100];
  char lastName[100];
  int id;
  float gpa;
};

Node** addStudent(Node** table, int &newID, int &nsize);
int hashF(int &num, int nsize);
void printStudent(Node** table, int nsize);
void printNext(Node* current);
Node** rehash(Node** table, int &nsize, Node** newTable, int ID);
Node** typeStudent(Node** table, int &newID, int &nsize);
void searchPrint(Node** table, int nsize);
void deleteStudent(Node** table, int nsize);

int main() {
  srand(time(0));
  cout << "welcome to studentlist" << endl;
  bool playing = true;
  Node** table = new Node*[100];
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
    else if (strcmp(input, "TYPE") == 0) {
      typeStudent(table, currID, size);
    }
    else if (strcmp(input, "SEARCH") == 0) {
      searchPrint(table, size);
    }
    else if (strcmp(input, "PRINT") == 0) {//Calls the print function
      printStudent(table, size);
    }
    else if (strcmp(input, "DELETE") == 0) {//Calls the delete function
      deleteStudent(table, size);
    }
    else if (strcmp(input, "QUIT") == 0) {//Returns false
      playing = false;//Exits while Loop stopping game
    }
  }
}

int hashF(int &num, int nsize) {
  return num%nsize;
}

Node** typeStudent(Node** table, int &newID, int &nsize) {
  Node* student = new Node();
  cout << "Add first name" << endl;
  cin >> student->firstName;
  cout << "Add last name" << endl;
  cin >> student->lastName;
  cout << "Add gpa" << endl;
  cin >> student->gpa;
  student->id = newID;
  if (table[hashF(newID, nsize)] == NULL) {
    table[hashF(newID, nsize)] = student;
  }
  else if (table[hashF(newID, nsize)]->next == NULL) {
    table[hashF(newID, nsize)]->next = student;
  }
  else if (table[hashF(newID, nsize)]->next->next == NULL) {
    table[hashF(newID, nsize)]->next->next = student;
  }
  else {
    Node** newTable = new Node*[nsize*2];
    for (int i = 0; i < nsize*2; i++) {
      newTable[i] = NULL;
    }
    table = rehash(table, nsize, newTable, newID);
    table[hashF(newID, nsize)]->next = student;
  }
  newID++;
  return table;

}

Node** addStudent(Node** table, int &newID, int &nsize) {
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
    /*cout << firstNameTemp << endl;
    cout << lastNameTemp << endl;
    cout << r << endl;
    cout << newID << endl;*/
    
    strcpy(student->firstName, firstNameTemp);
    cout << student->firstName;
    strcpy(student->lastName, lastNameTemp);
    student->gpa = r;
    student->id = newID;

    if (table[hashF(newID, nsize)] == NULL) {
      table[hashF(newID, nsize)] = student;
    }
    else if (table[hashF(newID, nsize)]->next == NULL) {
      table[hashF(newID, nsize)]->next = student;
    }
    else if (table[hashF(newID, nsize)]->next->next == NULL) {
      table[hashF(newID, nsize)]->next->next = student;
    }
    else {
      Node** newTable = new Node*[nsize*2];
      for (int i = 0; i < nsize*2; i++) {
	newTable[i] = NULL;
      }
      table = rehash(table, nsize, newTable, newID);
      table[hashF(newID, nsize)]->next = student;
    }

    newID++;
  }
  return table;
}

void searchPrint(Node** table, int nsize) {
  int IDinput;
  cout << "Eneter the id you want to print" << endl;
  cin >> IDinput;
  for (int i = 0; i < nsize; i++) {
    if (table[i]->id == IDinput) {
      cout << table[i]->firstName << " " << table[i]->lastName << " ID:" << table[i]->id << " GPA:" << fixed << setprecision(2) << table[i]->gpa << endl;
      return;
    }
    else if (table[i]->next != NULL) {
      if (table[i]->next->id == IDinput) {
	cout << table[i]->next->firstName << " " << table[i]->next->lastName << " ID:" << table[i]->next->id << " GPA:" << fixed << setprecision(2) << table[i]->next->gpa << endl;
	return;
      }
      else if (table[i]->next->next != NULL) {
	if (table[i]->next->next->id == IDinput) {
	  cout << table[i]->next->next->firstName << " " << table[i]->next->next->lastName << " ID:" << table[i]->next->next->id << " GPA:" << fixed << setprecision(2) << table[i]->next->next->gpa << endl;
	  return;
	}
      }
    }
  }
}

void printStudent(Node** table, int nsize) {
  Node* curr;
  for (int i = 0; i < nsize; i++) {
    curr = table[i];
    printNext(curr);
  }  
}

void printNext(Node* current) {
  if (current != NULL) {
    cout << current->firstName << " " << current->lastName << " ID:" << current->id << " GPA:" << fixed << setprecision(2) << current->gpa << endl;
    printNext(current->next);
  }
}

void deleteStudent(Node** table, int nsize) {
  int IDinput;
  cout << "what is the ID of the student to delete" << endl;
  cin >> IDinput;
  Node* temp = table[IDinput%nsize];
  if (temp->id == IDinput) {
    table[IDinput%nsize] = temp->next;
  }
  else if (temp->next->id == IDinput) {
    table[IDinput%nsize] = temp->next->next;
  }
  else if (temp->next->next->id == IDinput) {
    table[IDinput%nsize]->next->next = NULL;
  }
}

Node** rehash(Node** table, int &nsize, Node** newTable, int ID) {
  int oSize = nsize;
  nsize = nsize*2;
  for (int i = 0; i < ID; i++) {
    if (i < oSize) {
      newTable[hashF(i, nsize)] = table[hashF(i, oSize)];
    }
    else if (i < oSize*2) {
      newTable[hashF(i, nsize)] = table[hashF(i, oSize)]->next;
      cout << table[101]->id << endl;
    }
    else {
      newTable[hashF(i, nsize)]->next = table[hashF(i, oSize)]->next->next;
    }
  }
  return newTable;
}


 
