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

TreeType tree;


int main()
{
	int option;
	populateTree();
	do
	{
		system("cls");
		printMenu();
		cin >> option;
		switch (option)
		{
		case 1:
			addItem();
			cout << "Item added!";
			break;
		case 2:
			printAll();
			break;
		default:
			break;
		}
		system("pause");
	} while (option != 3);
    return 0;
}

void printMenu() {
	cout << "1) Add new Entry \n";
	cout << "2) Display tree. \n";
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
	name = "Adam";
	tree.InsertItem(name);

	name = "Jack";
	tree.InsertItem(name);

	name = "Gavin";
	tree.InsertItem(name);

	name = "Mark";
	tree.InsertItem(name);

	name = "Nazmul";
	tree.InsertItem(name);
}