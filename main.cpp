//Nihal Parthasrathy
//3/16/2022
//This code makes a student list where you can add, print, and delete students. It does this implementing a HashTable.
//Help from Kushal

//Inclusions
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

struct Node {//Struct for students
  Node* next = NULL;
  char firstName[100];
  char lastName[100];
  int id;
  float gpa;
};

//Function Prototypes
Node** addStudent(Node** table, int &newID, int &nsize);
int hashF(int &num, int nsize);
void printStudent(Node** table, int nsize);
void printNext(Node* current);
Node** rehash(Node** table, int &nsize, Node** newTable, int ID);
Node** typeStudent(Node** table, int &newID, int &nsize);
void searchPrint(Node** table, int nsize);
void deleteStudent(Node** table, int nsize);

int main() {
  srand(time(0)); //Initilizes random seed
  cout << "welcome to studentlist" << endl;
  //Initilize varubles
  bool playing = true;
  Node** table = new Node*[100];
  int currID = 0;
  int size = 100;
  
  for (int i = 0; i < size; i++) {//Sets everything in table to null
    table[i] = NULL;
  }
  while (playing == true) {//While loop
    cout << "would you like to add(ADD), Manualy add(TYPE), print(PRINT), search print(SEARCH), delete(DELETE) or quit(QUIT)" << endl;
    char input[10];
    cin >> input;
    if (strcmp(input, "ADD") == 0) {//Calls the add function
      //int i = hashFunction(returnID());
      table = addStudent(table, currID, size);
    }
    else if (strcmp(input, "TYPE") == 0) {//Calls type function
      table = typeStudent(table, currID, size);
    }
    else if (strcmp(input, "SEARCH") == 0) {//Calls search function
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

int hashF(int &num, int nsize) {//Hash Function returns modules of the number and size
  return num%nsize;
}

Node** typeStudent(Node** table, int &newID, int &nsize) {//Function to manully add student
  //Adds student
  Node* student = new Node();
  cout << "Add first name" << endl;
  cin >> student->firstName;
  cout << "Add last name" << endl;
  cin >> student->lastName;
  cout << "Add gpa" << endl;
  cin >> student->gpa;
  student->id = newID;
  if (table[hashF(newID, nsize)] == NULL) {//If there is no collisions
    table[hashF(newID, nsize)] = student;//Adds student to the hashtable
  }
  else if (table[hashF(newID, nsize)]->next == NULL) {//If there is a collision
    table[hashF(newID, nsize)]->next = student;//Adds student to the next of the other node
  }
  else if (table[hashF(newID, nsize)]->next->next == NULL) {//IF there is two collisions
    table[hashF(newID, nsize)]->next->next = student;//Adds student to the next of the next of the other node
  }
  else {//If there is 3 collisions
    Node** newTable = new Node*[nsize*2];//New table with a size of * 2
    for (int i = 0; i < nsize*2; i++) {//Clears and sets to null
      newTable[i] = NULL;
    }
    table = rehash(table, nsize, newTable, newID);//Calls rehash function
    table[hashF(newID, nsize)]->next = student;//Adds student to the table after rehash
    
  }
  newID++;//Incrments id
  return table;
}

Node** addStudent(Node** table, int &newID, int &nsize) {//Adds student to the hashtable
  //Asks how much students to enter
  cout << "How many students would you like to add" << endl;
  int numStudents;
  cin >> numStudents;
  
  for (int i = 0; i < numStudents; i++) {//Makes new Students
    Node* student = new Node();
    char input[100];
    char input2[100];
    
    int num = (rand() % 20) + 1;//Random
    int num2 = (rand() % 20) + 1;

    fstream myfile("firstName.txt");//Opens the files
    fstream lastfile("lastName.txt");

    char firstNameTemp[100];
    int count = 1;
    
    while (myfile.getline(input,100, '\n')) {//Goes through each line in the file
      if (count == num) {//Checks if the line is the randomly generated one
	strcpy(firstNameTemp, input);//Takes the name and copies into a temp var
	count++;
      }
      count++;
    }
    myfile.close();
    
    char lastNameTemp[100];
    int count2 = 1;
    
    while (lastfile.getline(input2,100, '\n')) {//Goes through each line in the file
      if (count2 == num2) {//Checks if the line is the randomly generated one
	strcpy(lastNameTemp, input2);//Copies bame into temp var
	count2++;
      }
      count2++;
    }
    lastfile.close();

    //Randomly generates the gpa
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    r *= 23;
    while(r > 4){
      r -= 4;
      while(r < 2){
	r += 1;
      }
    }

    //Adds the varubles to the student
    strcpy(student->firstName, firstNameTemp);
    strcpy(student->lastName, lastNameTemp);
    student->gpa = r;
    student->id = newID;

    if (table[hashF(newID, nsize)] == NULL) {//If there is no collisions
      table[hashF(newID, nsize)] = student; //Adds student to hashtable
    }
    else if (table[hashF(newID, nsize)]->next == NULL) {//If there is a collision
      table[hashF(newID, nsize)]->next = student;//Adds student to hashtable
    }
    else if (table[hashF(newID, nsize)]->next->next == NULL) {//If there is 2 collisions
      table[hashF(newID, nsize)]->next->next = student; //Adds student to hashtable
    }
    else {//If there is 3 collisions
      Node** newTable = new Node*[nsize*2];//Makes new table with size * 2
      for (int i = 0; i < nsize*2; i++) {//Clears newtable makes everything null
	newTable[i] = NULL;
      }
      table = rehash(table, nsize, newTable, newID);//Calls rehash function
      table[hashF(newID, nsize)]->next = student;//Adds the student to hashtable after rehash
    }
    newID++;
  }
  cout << "Added!" << endl;
  return table;
}

void searchPrint(Node** table, int nsize) {//Searches for student and prints
  int IDinput;
  cout << "Eneter the id you want to print" << endl;
  cin >> IDinput;
  
  for (int i = 0; i < nsize; i++) {
    if (table[i]->id == IDinput) {//If its equal to the id
      cout << table[i]->firstName << " " << table[i]->lastName << " ID:" << table[i]->id << " GPA:" << fixed << setprecision(2) << table[i]->gpa << endl;
      return;
    }
    else if (table[i]->next != NULL) {
      if (table[i]->next->id == IDinput) {//If equal to its next id
	cout << table[i]->next->firstName << " " << table[i]->next->lastName << " ID:" << table[i]->next->id << " GPA:" << fixed << setprecision(2) << table[i]->next->gpa << endl;
	return;
      }
      else if (table[i]->next->next != NULL) {
	if (table[i]->next->next->id == IDinput) {//If its equal to next next id
	  cout << table[i]->next->next->firstName << " " << table[i]->next->next->lastName << " ID:" << table[i]->next->next->id << " GPA:" << fixed << setprecision(2) << table[i]->next->next->gpa << endl;
	  return;
	}
      }
    }
  }
}

void printStudent(Node** table, int nsize) {//Prints student
  Node* curr;
  for (int i = 0; i < nsize; i++) {
    curr = table[i];
    printNext(curr);//Calls printNext function
  }  
}

void printNext(Node* current) {
  if (current != NULL) {//If curr != NULL
    cout << current->firstName << " " << current->lastName << " ID:" << current->id << " GPA:" << fixed << setprecision(2) << current->gpa << endl; //Prints student info
    printNext(current->next);//Recursion call
  }
}

void deleteStudent(Node** table, int nsize) {//Deletes student
  int IDinput;
  cout << "what is the ID of the student to delete" << endl;
  cin >> IDinput;
  
  Node* temp = table[IDinput%nsize]; //For less repetion
  
  if (temp->id == IDinput) {//If id is same
    table[IDinput%nsize] = temp->next;//Becomes its next
  }
  else if (temp->next->id == IDinput) {//If temps next id is same
    table[IDinput%nsize] = temp->next->next;//The next becomes its nexts
  }
  else if (temp->next->next->id == IDinput) {//If temps next next id is same
    table[IDinput%nsize]->next->next = NULL;
  }
}

Node** rehash(Node** table, int &nsize, Node** newTable, int ID) {//Rehash function
  int oSize = nsize; //Old size
  nsize = nsize*2;
  for (int i = 0; i < ID; i++) {//Increments through each ID
    if (i < oSize) {//If the id is less than old size rehash to same place
      newTable[i] = table[i];
    }
    else if (i < oSize*2) {//If the id is less than osize*2 adds to the second half of the table
      newTable[i] = table[hashF(i, oSize)]->next;
    }
    else {//If id is more than osize*2 it becomes the next
      newTable[hashF(i, nsize)]->next = table[hashF(i, oSize)]->next->next;
    }
  }
  for (int j = oSize; j < nsize; j++) {//Clears all of the second half of the tables pointers to NULL
    newTable[j]->next = NULL;
  }
  
  return newTable;
}


 
