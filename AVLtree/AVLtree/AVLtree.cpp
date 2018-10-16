// AVLtree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "avl.h"

using namespace std;
void printMenu();
void printAll();
void addItem();
void populateTree();
void searchByName();
void deleteName();

TreeType tree;


int main()
{
	char option;
	populateTree();
	do
	{
		system("cls");
		printMenu();
		cin >> option;
		switch (option)
		{
		case '1':
			addItem();
			break;
		case '2':
			printAll();
			break;
		case '3':
			searchByName();
			break;
		case '4':
			deleteName();
			break;
		default:
			break;
		}
		cout << endl;
		system("pause");
	} while (option != '5');

    return 0;
}

void printMenu() {
	cout << "1) Add new Entry \n";
	cout << "2) Display tree. \n";
	cout << "3) Search by name. \n";
	cout << "4) Delete name. \n";
	cout << "5) Exit. \n";
	cout << "Please enter in your option: ";
}

void printAll()
{
	tree.PrintTree();
}

void addItem()
{
	string data;
	cout << "Please enter the data you wish to add: ";
	cin >> data;
	tree.InsertItem(data);
}

void populateTree() 
{
	string name;
	name = "A";
	tree.InsertItem(name);

	name = "Z";
	tree.InsertItem(name);

	name = "B";
	tree.InsertItem(name);

	name = "Y";
	tree.InsertItem(name);

	name = "C";
	tree.InsertItem(name);

	name = "X";
	tree.InsertItem(name);
}

void searchByName() {
	cout << "Please enter in a name to search: ";
	string temp;
	cin >> temp;
	bool found = false;
	tree.RetrieveItem(temp, found);
}

void deleteName() {
	cout << "Please enter a name you would like to delete: ";
	string temp;
	cin >> temp;
	tree.DeleteItem(temp);
	cout << temp << " has been deleted from the tree.";
}