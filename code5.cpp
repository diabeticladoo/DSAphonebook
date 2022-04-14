#include <bits/stdc++.h>
using namespace std;


class contactinfo
{
	private:
	string name;
	string number;
	string email;
	string profession;

	public:
	contactinfo(string a,string b,string c="",string d="")
	{
		name=a;
		number=b;
		email=c;
		profession=d;

	}
	contactinfo()
	{

	}
	
	string getname()
	{
		return name;
	}

	string getnum()
	{
		return number;
	}

	string getemail()
	{
		return email;
	}

	string getprofession()
	{
		return profession;
	}

};

// WORK TO DO
// make tree for numbers
// add star cont adding bool 
// taking user input, add,delete making menu
// 

struct TrieNode
{
	// Each Trie Node contains a Map 'child'
	// where each alphabet points to a Trie
	// Node.
	// We can also use a fixed size array of
	// size 256.
	unordered_map<char,TrieNode*> child;

	// 'isLast' is true if the node represents
	// end of a contact
	bool isLast;
	contactinfo *loc;

	// Default Constructor
	TrieNode()
	{
		// Initialize all the Trie nodes with NULL
		for (char i = 'a'; i <= 'z'; i++)
			child[i] = NULL;
		child[' ']=NULL;

		isLast = false;
	}
};

// Making root NULL for ease so that it doesn't
// have to be passed to all functions.
TrieNode *root = new TrieNode();

// Insert a Contact into the Trie
void insert(string s,contactinfo *q)
{
	int len = s.length();

	// 'itr' is used to iterate the Trie Nodes
	TrieNode *itr = root;
	for (int i = 0; i < len; i++)
	{
		// Check if the s[i] is already present in
		// Trie
		TrieNode *nextNode = itr->child[s[i]];
		if (nextNode == NULL)
		{
			// If not found then create a new TrieNode
			nextNode = new TrieNode();

			// Insert into the Map
			itr->child[s[i]] = nextNode;
		}

		// Move the iterator('itr') ,to point to next
		// Trie Node
		itr = nextNode;

		// If its the last character of the string 's'
		// then mark 'isLast' as true
		if (i == len - 1)
		{
			itr->isLast = true;
			itr->loc=q;
		}
	}
}

// This function simply displays all dictionary words
// going through current node. String 'prefix'
// represents string corresponding to the path from
// root to curNode.
void displayContactsUtil(TrieNode *curNode, string prefix)
{
	// Check if the string 'prefix' ends at this Node
	// If yes then display the string found so far
	if (curNode->isLast)
	{
		cout << prefix << "--";
		cout << curNode->loc->getnum() << "\n\n";
	}
	// Find all the adjacent Nodes to the current
	// Node and then call the function recursively
	// This is similar to performing DFS on a graph
	for (char i = 'a'; i <= 'z'; i++)
	{
		TrieNode *nextNode = curNode->child[i];
		if (nextNode != NULL)
			displayContactsUtil(nextNode, prefix + (char)i);
	}
	TrieNode *nextNode = curNode->child[' '];
	if(nextNode !=NULL)
	{
		displayContactsUtil(nextNode, prefix + ' ');
	}
}

// Display suggestions after every character enter by
// the user for a given query string 'str'
void displayContacts(string str)
{
	TrieNode *prevNode = root;

	string prefix = "";
	int len = str.length();

	// Display the contact List for string formed
	// after entering every character
	int i;
	for (i=0; i<len; i++)
	{
		// 'prefix' stores the string formed so far
		prefix += (char)str[i];

		// Get the last character entered
		char lastChar = prefix[i];

		// Find the Node corresponding to the last
		// character of 'prefix' which is pointed by
		// prevNode of the Trie
		TrieNode *curNode = prevNode->child[lastChar];

		// If nothing found, then break the loop as
		// no more prefixes are going to be present.
		if (curNode == NULL)
		{
			cout << "\nNo Results Found for " << prefix
				<< "\n";
			i++;
			break;
		}

		// If present in trie then display all
		// the contacts with given prefix.
		cout << "\nSuggestions based on \"" << prefix
			<< "\" are \n";
		displayContactsUtil(curNode, prefix);

		// Change prevNode for next prefix
		prevNode = curNode;
	}

	// Once search fails for a prefix, we print
	// "Not Results Found" for all remaining
	// characters of current query string "str".
	for (; i<len; i++)
	{
		prefix += (char)str[i];
		cout << "\nNo Results Found for \"" << prefix
			<< "\" \n";
	}
}

// Insert all the Contacts into the Trie
// void insertIntoTrie(string name)
// {
// 	// Initialize root Node
// 	root = new TrieNode();

// 	insert(name);
// }

// Driver program to test above functions
int main()
{
	freopen("contacts.txt", "r", stdin); 
	int x,n;
	cin >> n;
	
	vector<contactinfo> p(n);
	string a,b,c,d;

	for(int i=0;i<n;i++)
	{
		c="";
		d="";
		cin >> x;	
		getline(std::cin,a,'$');
		// cin >> a;
		cin >> b;
		if(x==2)
		{
			cin >> c;
		}
		else if(x==3)
		{
			cin >> d;
		}
		else if(x==4)
		{
			cin >> c >> d;
		}
		
		contactinfo t(a,b,c,d);
		p[i]=t;
		
		insert(p[i].getname(),&p[i]);
	}
	
	for(int i=0;i<n;i++)
	{
		contactinfo t=p[i];
		cout << t.getname() << " " << t.getnum() << "\n";
		cout << t.getemail() << " " << t.getprofession() << endl;
	}
	cout << "end\n\n";
	fclose(stdin);
	displayContacts("a");
	int choice;
	cout<<"Welcome to ASA Phone Directory\n";
	cout<<"Please select a suitable option:\n";
	cout<<"1. Search by name\n";
	cout<<"2. Search by number\n";
	cout<<"3. Add to contact\n";
	cout<<"4. Edit Contact\n";
	cout<<"5. Add to favourite\n";
	cout<<"6. Delete a contact\n";
	cout<<"7. Exit\n";
	while(true){
		cin>>choice;
		switch(choice){
			case 1:{

				break;
			}
			case 2:{

				break;
			}
			case 3:{

				break;
			}
			case 4:{

				break;
			}
			case 5:{

				break;
			}
			case 6:{

				break;
			}
			case 7:{

				break;
			}
			case 8:{
				cout<<"Exiting\n";
				exit(0);
				break;
			}
		}
	}

	// Insert all the Contacts into Trie
	// insertIntoTrie(contacts, n);

	// string query = "gekk";

	// Note that the user will enter 'g' then 'e', so
	// first display all the strings with prefix as 'g'
	// and then all the strings with prefix as 'ge'
	// displayContacts(query);
	cout << "Working" << endl;

	return 0;
}