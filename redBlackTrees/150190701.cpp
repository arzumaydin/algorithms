// ARZUM AYDIN 10.01.2022

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>

using namespace std;

// defining a Node struct with appropriate attributes
typedef struct Node {
  string publisher;
  float na_sales;
  float eu_sales;
  float other_sales;
  Node *parent;
  Node *left;
  Node *right;
  string color;
  float total = na_sales + eu_sales + other_sales;
} Node;

typedef struct RBTree
{
    struct Node* root;
} RBTree;


void init(Node* root, RBTree rb) // initialize root pointer when first created
{
    root = NULL;
    rb.root = root;
}

// implement rotations
void leftRotate(Node* node, RBTree &rbtree)
{
	Node* ptr = node->right; // set ptr
	node->right = ptr->left; // ptr's left subtree will be node's right subtree
	
	if(ptr->left != NULL)
	{
		ptr->left->parent = node; // node should be left child
	}
	ptr->parent = node->parent; // ptr's parents is node's parents

	if(node->parent == NULL) // if node is root
	{
		rbtree.root = ptr; // set ptr as root 
	}
	else if(node == node->parent->left) // if node is left child
	{
		node->parent->left = ptr; // set ptr to it
	}
	else
	{
		node->parent->right = ptr; // if right child, set ptr to it
	}
	ptr->left = node; // node is now left child of ptr
	node->parent = ptr; 
}

void rightRotate(Node* node, RBTree &rbtree)
{
	Node* ptr = node->left;	// set ptr
	node->left = ptr->right; // ptr's right subtree will be node's left subtree
	
	if(ptr->right != NULL)
	{
		ptr->right->parent = node; // node should be right child
	}
	ptr->parent = node->parent; // ptr's parents is node's parents

	if(node->parent == NULL) // if node is root
	{
		rbtree.root = ptr; // set ptr as root
	}
	else if(node == node->parent->right)  // if node is right child
	{
		node->parent->right = ptr; // set ptr to it
	}
	else
	{
		node->parent->left = ptr; // if left child, set ptr to it
	}
	ptr->right = node; // node is now right child of ptr
	node->parent = ptr;
}

// new node is inserted but there might be violating properties of RB Tree
// so fix them up
void insertFixUp(Node* node, RBTree &rbtree)
{
	Node* uncle = nullptr;

    while(node->parent->color == "RED") // node is red and parent is red so there is a violation
    {
		if(node->parent == node->parent->parent->left) // check if parent is left child
		{
			uncle = node->parent->parent->right; // if it is, set uncle as right child
			
			if(uncle != NULL && uncle->color == "RED") // if uncle is red
			{
				node->parent->color = "BLACK"; // color parent to black
				uncle->color = "BLACK"; // color uncle to black
				node->parent->parent->color = "BLACK"; // color grandparent to black
				node = node->parent->parent; // set node as grandparent
			}
			else if(uncle == NULL || uncle->color == "BLACK")// uncle is black
			{
				if(node == node->parent->right) // if node is right child
				{
					node = node->parent; // set node as parent
					leftRotate(node, rbtree); // left rotate the tree
				}
				node->parent->color = "BLACK"; // if parent is black and grandparent is red, right rotate
				node->parent->parent->color = "RED";
				rightRotate(node->parent->parent, rbtree);
			}
		}
		else // if parent is right child, do the opposite operations
		{
			if(node->parent == node->parent->parent->right) // check if parent is right child
			{
				uncle = node->parent->parent->left; // if it is, set uncle as left child
				
				if(uncle != NULL && uncle->color == "RED") // if uncle is red
				{
					node->parent->color = "BLACK"; // color parent to black
					uncle->color = "BLACK"; // color uncle to black
					node->parent->parent->color = "BLACK"; // color grandparent to black
					node = node->parent->parent; // set node as grandparent
				}
				else if(uncle == NULL || uncle->color == "BLACK")// uncle is black
				{
					if(node == node->parent->left) // if node is left child
					{
						node = node->parent; // set node as parent
						rightRotate(node, rbtree); // right rotate the tree
					}
					node->parent->color = "BLACK"; // if parent is black and grandparent is red, left rotate
					node->parent->parent->color = "RED";
					leftRotate(node->parent->parent, rbtree);
				}
			}
			
			if(node == rbtree.root)
			{
				break;
			}
			
		}
    }
	rbtree.root->color = "BLACK";
}

void insert(vector<string> row, RBTree &rb, Node* maxEU, Node* maxNA, Node* maxOther) {
    Node* node = new Node; // create new node and assign the values inside vector to the node's attributes
    node->parent = nullptr;
    node->publisher = row[3];
    node->na_sales = stof(row[4]);
    node->eu_sales = stof(row[5]);
    node->other_sales = stof(row[6]);
    node->left = NULL;
    node->right = NULL;
    node->color = "RED"; // color the new node red, fix it later

	if(maxEU != nullptr)
	{
		if(maxEU->eu_sales < node->eu_sales)
		{
			maxEU = node;
		}
		else if(maxNA->na_sales < node->na_sales)
		{
			maxNA = node;
		}
		else if(maxOther->other_sales < node->other_sales)
		{
			maxOther = node;
		}
	}

    Node* y = nullptr; // nil leaf pointer
    Node* x = rb.root; // x is root pointer

    while (x != NULL) {
      y = x; // y points to the root as well
      
      if (node->publisher < x->publisher) { // if key of new node is smaller than root node
        x = x->left; // add to left side
      } else {
        x = x->right; // add to right side
      }
    }

    node->parent = y; // node's parent is y, which points to the root
    if (y == nullptr) { // if y is null which means there is no node in the tree
      rb.root = node; // set tree's root as node
    } else if (node->publisher < y->publisher) { // if root exists then set root's child as node
      y->left = node;
    } else {
      y->right = node;
    }

    if (node->parent == nullptr) { // if node's parent is null which means node will be the root node
      node->color = "BLACK"; // color the root black
      return;
    }

    if (node->parent->parent == nullptr) { // if 
      return;
    }

    insertFixUp(node, rb);
}

// search tree for the same publisher
Node* searchTree(string publisher, Node* node)
{
    if(node == NULL || node->publisher == publisher)
	{
		return node; // if node is null or same publisher is found, return node
	}

	if(publisher < node->publisher) // compare names and search left subtree if it is smaller
	{
		return searchTree(publisher, node->left);
	}

	return searchTree(publisher, node->right); // search right subtree if it is bigger
}

int findDepthOfNode(Node* node) // traverse tree from leaf to root until root is reached
{
	Node* ptr = node;
	int depth = 0;
	while(ptr->parent != NULL)
	{
		ptr = ptr->parent;
		depth += 1; // increment depth every time 
	}
	return depth;
}

void printTree(Node* node) // preorder traversal
{
	if(node == NULL) // if node is null return
	{
		return;
	}
	
	int depth = findDepthOfNode(node);

	for(int i = 0; i < depth; i++)
	{
		cout << "-";
	}
	cout << "(" << node->color << ") " << node->publisher <<endl;

	printTree(node->left);
	printTree(node->right);
}

int findDecade(string s)
{
	if(s == "1980") // i hard coded this because there is no data before 1980
	{
		return 1990;
	}
	int year = stoi(s);
	while(year % 10 != 0)
	{
		year++;
	}
	return year;
}

int main(int argc, char *argv[])
{
    ifstream fin;
    string line, word;
    int count_lines = 0;
    vector <string> row;
	int lastDecade = 0;
	int newDecade = 0;
	Node* maxEU = nullptr;
	Node* maxNA = nullptr;
	Node* maxOther = nullptr;
    RBTree rbtree;
	rbtree.root = nullptr;
    Node* root = new Node;
    init(root, rbtree); // initialize head values for the tree

    fin.open(argv[1]);
    //fin.open("VideoGames.csv");
    if (!fin.is_open()) // error handling
    {
      cerr<<"Could not open file\n";
      exit(1);
    }
    else {
        while(fin) // while not end of file
        {
            getline(fin, line); // get the next line from file
            row.clear();
            stringstream mystr(line); // break line into words via stringstream
            
            if(count_lines != 0) // do not include first row of headers
            {
                while(getline(mystr, word, ',')) // get words that are seperated with a delimeter
                {
                    row.push_back(word); // push word into vector row
                }

				newDecade = findDecade(row[2]);
				if(lastDecade != 0 && lastDecade != newDecade) // print tree if new decade data has started to come
				{
					Node* r = rbtree.root;
					cout << "End of the " << lastDecade << " Year" << endl;
					cout << "Best Seller in North America: " << maxNA->publisher << " - " << maxNA->na_sales << " million" << endl;
					cout << "Best Seller in Europe: " << maxEU->publisher << " - " << maxEU->eu_sales << " million" << endl;
					cout << "Best Seller rest of the world: " << maxOther->publisher << " - " << maxOther->other_sales << " million" << endl;
					printTree(r);
				}

				Node* n = searchTree(row[3], rbtree.root); // search if publisher is in tree already
                if(n != NULL)
                {
                    n->na_sales += stof(row[4]); // if publisher in the list already, don't insert it.
					n->eu_sales += stof(row[5]);
					n->other_sales += stof(row[6]);

					if(maxEU->eu_sales < n->eu_sales)
					{
						maxEU = n;
					}
					else if(maxNA->na_sales < n->na_sales)
					{
						maxNA = n;
					}
					else if(maxOther->other_sales < n->other_sales)
					{
						maxOther = n;
					}
                }
                else // if new publisher -> insert into tree
                {
                	insert(row, rbtree, maxEU, maxNA, maxOther);

                }
				lastDecade = findDecade(row[2]);
				if(maxEU == NULL)
				{
					maxEU = rbtree.root;
					maxNA = rbtree.root;
					maxOther = rbtree.root;
				}

            } 
            
            count_lines++;
        }
    }

    fin.close();

    return EXIT_SUCCESS;
}