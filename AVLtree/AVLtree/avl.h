#pragma once
#include <string>
#include <iostream>
using namespace std;


typedef enum {LH,EH,RH} BalFactor;

struct NodeType {
	string data;
	NodeType* left;
	NodeType* right;
	BalFactor bf;
};

void Print(NodeType* tree);
void Destroy(NodeType*& tree);
void RightBalance(NodeType*& tree, bool& taller);
void LeftBalance(NodeType*& tree, bool& taller);
void RotateRight(NodeType*& tree);
void RotateLeft(NodeType*& tree);
void Insert(NodeType*& tree, string item, bool& taller);
void Retrieve(NodeType* tree, string item, bool& found);


class TreeType {
public:
	TreeType();
	~TreeType();
	void makeEmpty();
	bool isEmpty() const;
	bool isFull() const;
	void InsertItem(string item);
	void PrintTree() const;
	void RetrieveItem(string item, bool& found);
private:
	NodeType *root;
};

TreeType::TreeType()
{
	root = NULL;
}

TreeType::~TreeType()
{
	Destroy(root);
}

void TreeType::makeEmpty() 
{
	Destroy(root);
	root = NULL;
}

bool TreeType::isEmpty() const
{
	return root == NULL;
}

bool TreeType::isFull() const
{
	NodeType* location;
	try
	{
		location = new NodeType;
		delete location;
		return false;
	}
	catch (const std::exception&)
	{
		//ignore
	}
	return true;
}

void TreeType::PrintTree() const
{
	Print(root);
}

void TreeType::InsertItem(string item)
{
	bool taller;
	Insert(root, item, taller);
}

void TreeType::RetrieveItem(string item, bool& found) {
	Retrieve(root,item,found);
}

void Retrieve(NodeType* tree, string item, bool& found) {
	if (tree == NULL)
	{
		found = false;
	}
	else if (item[0] < tree->data[0])
	{
		Retrieve(tree->left, item, found);
	}
	else if (item[0] > tree->data[0])
	{
		Retrieve(tree->right, item, found);
	}
	else
	{
		Retrieve(tree->left, item, found);
		cout << tree->data;
		Retrieve(tree->right, item, found);
		found = true;
	}
}

void Insert(NodeType*& tree, string item, bool& taller)
{
	if (tree == NULL)
	{
		tree = new NodeType;
		tree->left = NULL;
		tree->right = NULL;
		tree->data = item;
		tree->bf = EH;
		taller = true;
		cout << "Item added!";
	}
	else if (item == tree->data)
	{
		cerr << "Duplicate key is not allowed in AVL tree." << endl;
	}
	else if (item < tree->data)
	{
		Insert(tree->left, item, taller);
		if (taller)
		{
			switch (tree->bf)
			{
			case LH: LeftBalance(tree, taller); break;
			case EH: tree->bf = LH; break;
			case RH: tree->bf = EH; taller = false; break;
			}
		}
	}
	else
	{
		Insert(tree->right, item, taller);
		if (taller)
		{
			switch (tree->bf)
			{
			case RH: RightBalance(tree, taller); break;
			case EH: tree->bf = RH; break;
			case LH: tree->bf = EH; taller = false; break;
			}
		}
	}
}

void RotateLeft(NodeType*& tree)
{
	NodeType * rs;
	if (tree == NULL)
	{
		cerr << "It is impossible to rotate an empty tree in RotateLeft" << endl;
	}
	else if (tree->right == NULL)
	{
		cerr << "It is impossible to make an empty subtree the root in RotateLeft" << endl;
	}
	else
	{
		rs = tree->right;
		tree->right = rs->left;
		rs->left = tree;
		tree = rs;
	}
}

void RotateRight(NodeType*& tree)
{
	NodeType* ls;
	if (tree == NULL)
	{
		cerr << "It is impossible to rotate an empty tree in RotateRight" << endl;
	}
	else if (tree->left == NULL)
	{
		cerr << "It is impossible to make an empty subtree the root in  RotateRight" << endl;
	}
	else
	{
		ls = tree->left;
		tree -> left = ls -> right;
		ls->right = tree;
		tree = ls;
	}
}

void LeftBalance(NodeType*& tree, bool& taller)
{
	NodeType * ls = tree->left;
	NodeType * rs;
	switch (ls->bf)
	{
	case LH:
		tree->bf = ls->bf = EH;
		RotateRight(tree);
		taller = false;
		break;
	case EH:
		cerr << "Tree already balanced." << endl;
	case RH:
		rs = ls->right;
		switch (rs->bf)
		{
		case LH:
			tree->bf = RH;
			ls->bf = EH;
			break;
		case EH:
			tree->bf = ls->bf = EH;
			break;
		case RH:
			tree->bf = EH;
			ls->bf = LH;
			break;
		}
		rs->bf = EH;
		RotateLeft(tree->left);
		RotateRight(tree);
		taller = false;
	}
}

void RightBalance(NodeType*& tree, bool& taller)
{
	NodeType * rs = tree->right;
	NodeType * ls;

	switch (rs->bf)
	{
	case RH:
		tree->bf = rs->bf = EH;
		RotateLeft(tree);
		taller = false;
		break;
	case EH: 
		cerr << "Tree already balanced" << endl;
		break;
	case LH:
		ls = rs->left;
		switch (ls->bf)
		{
		case RH:
			tree->bf = LH;
			rs->bf = EH;
			break;
		case EH:
			tree->bf = rs->bf = EH;
			break;
		case LH:
			tree->bf = EH;
			rs->bf = RH;
			break;
		}
		ls->bf = EH;
		RotateRight(tree->right);
		RotateLeft(tree);
		taller = false;
	}

}

void Destroy(NodeType*& tree) 
{
	if (tree != NULL)
	{
		Destroy(tree->left);
		Destroy(tree->right);
		delete tree;
	}
}

void Print(NodeType* tree)
{
	if (tree != NULL)
	{
		Print(tree->left);
		cout << tree->data;
		if (tree->left == NULL)
		{
			cout << " Left: Leaf.";
		}
		else
		{
			cout << " Left: " + tree->left->data;
		}

		if (tree->right == NULL)
		{
			cout << " Right: Leaf.";
		}
		else
		{
			cout << " Right: " + tree->right->data;
		}

		switch (tree->bf)
		{
		case LH:
			cout << " BF: LH.\n";
			break;
		case EH:
			cout << " BF: EH.\n";
			break;
		case RH:
			cout << " BF: RH.\n";
			break;
		}
		Print(tree->right);
	}
}