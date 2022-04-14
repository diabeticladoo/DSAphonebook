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
  contactinfo(string a, string b, string c = "", string d = "")
  {
    name = a;
    number = b;
    email = c;
    profession = d;
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
// add star cont adding bool
// taking user input, add,delete making menu

struct Triename
{
  unordered_map<char, Triename *> child;

  bool isLast;
  int pos;

  Triename()
  {

    for (char i = 'a'; i <= 'z'; i++)
      child[i] = NULL;
	
	for (char i = '0'; i <= '9'; i++)
      child[i] = NULL;
	

    child[' '] = NULL;

    isLast = false;
  }
};

struct Trienumber
{
  unordered_map<char, Trienumber *> child;

  bool isLast;
  int pos;
  Trienumber()
  {
    for (char i = '0'; i <= '9'; i++)
      child[i] = NULL;

    isLast = false;
  }
};

Triename *rootname = new Triename();
Trienumber *rootnum = new Trienumber();

void insertname(string s, int j)
{
  int len = s.length();

  Triename *itr = rootname;

  for (int i = 0; i < len; i++)
  {
    Triename *nextNode = itr->child[s[i]];
    if (nextNode == NULL)
    {
      nextNode = new Triename();

      itr->child[s[i]] = nextNode;
    }

    itr = nextNode;

    if (i == len - 1)
    {
      itr->isLast = true;
      itr->pos = j;
    }
  }
}

void insertnum(string s, int j)
{
  int len = s.length();
  Trienumber *itr = rootnum;

  for (int i = 0; i < len; i++)
  {
    Trienumber *nextNode = itr->child[s[i]];
    if (nextNode == NULL)
    {

      nextNode = new Trienumber();

      itr->child[s[i]] = nextNode;
    }

    itr = nextNode;

    if (i == len - 1)
    {
      itr->isLast = true;
      itr->pos = j;
    }
  }
}

void displayContactsUtil(Triename *curNode, string prefix)
{

  if (curNode->isLast)
  {
    cout << curNode->pos << " " << prefix << endl;
  }

  for (char i = 'a'; i <= 'z'; i++)
  {
    Triename *nextNode = curNode->child[i];
    if (nextNode != NULL)
      displayContactsUtil(nextNode, prefix + (char)i);
  }
  for (char i = '0'; i <= '9'; i++)
  {
    Triename *nextNode = curNode->child[i];
    if (nextNode != NULL)
      displayContactsUtil(nextNode, prefix + (char)i);
  }
  Triename *nextNode = curNode->child[' '];

  if (nextNode != NULL)
  {
    displayContactsUtil(nextNode, prefix + ' ');
  }


}

void displayContactsUtil(Trienumber *curNode, string prefix)
{

  if (curNode->isLast)
  {
    cout << curNode->pos << " " << prefix << endl;
  }

  for (char i = '0'; i <= '9'; i++)
  {
    Trienumber *nextNode = curNode->child[i];
    if (nextNode != NULL)
      displayContactsUtil(nextNode, prefix + (char)i);
  }
  Trienumber *nextNode = curNode->child[' '];
  if (nextNode != NULL)
  {
    displayContactsUtil(nextNode, prefix + ' ');
  }
}

void displayContactsbyname(string str)
{
  Triename *prevNode = rootname;

  string prefix = "";
  int len = str.length();

  int i;
  for (i = 0; i < len; i++)
  {

    prefix += (char)str[i];

    char lastChar = prefix[i];

    Triename *curNode = prevNode->child[lastChar];

    if (curNode == NULL)
    {
      cout << "\nNo Results Found for " << prefix
           << "\n";
      i++;
      break;
    }

    if (i == len - 1)
    {
      cout << "\nSuggestions based on \"" << prefix
           << "\" are \n";

      displayContactsUtil(curNode, prefix);
    }
    prevNode = curNode;
  }

  for (; i < len; i++)
  {
    prefix += (char)str[i];
    cout << "\nNo Results Found for \"" << prefix
         << "\" \n";
  }
}

void displayContactsbynum(string str)
{
  Trienumber *prevNode = rootnum;

  string prefix = "";
  int len = str.length();

  int i;
  for (i = 0; i < len; i++)
  {

    prefix += (char)str[i];

    char lastChar = prefix[i];

    Trienumber *curNode = prevNode->child[lastChar];

    if (curNode == NULL)
    {
      cout << "\nNo Results Found for " << prefix
           << "\n";
      i++;
      break;
    }

    if (i == len - 1)
    {
      cout << "\nSuggestions based on \"" << prefix
           << "\" are \n";

      displayContactsUtil(curNode, prefix);
    }

    prevNode = curNode;
  }

  for (; i < len; i++)
  {
    prefix += (char)str[i];
    cout << "\nNo Results Found for \"" << prefix
         << "\" \n";
  }
}




int main()
{
	fstream  file;
    file.open("contacts.txt", ios::out | ios::in );
	// freopen("contacts.txt", "r", stdin);
  
	int x, n;
	file >> n;

	vector<contactinfo> p(n);
	string a, b, c, d;

	for (int i = 0; i < n; i++)
	{
		c = "";
		d = "";
		file >> x;
		getline(file, a, '$');
		// file >> a;
		file >> b;
		if (x == 2)
		{
			file >> c;
		}
		else if (x == 3)
		{
			file >> d;
		}
		else if (x == 4)
		{
			file >> c >> d;
		}

		contactinfo t(a, b, c, d);
		p[i] = t;

		insertname(p[i].getname(), i);
		insertnum(p[i].getnum(), i);
	}


	displayContactsbyname("an");
	displayContactsbynum("11");

	int choice;
	cout << "Welcome to ASA Phone Directory\n";
	cout << "Please select a suitable option:\n";
	cout << "1. Search by name\n";
	cout << "2. Search by number\n";
	cout << "3. Add to contact\n";
	cout << "4. Edit Contact\n";
	cout << "5. Add to favourite\n";
	cout << "6. Delete a contact\n";
	cout << "7. Add to contact\n";
	cout << "8. Exit\n";
	while (true)
	{
		cin >> choice;
		switch (choice)
		{
			case 1:
			{

				break;
			}
			case 2:
			{

				break;
			}
			case 3:
			{

				break;
			}
			case 4:
			{

				break;
			}
			case 5:
			{

				break;
			}
			case 6:
			{

				break;
			}
			case 7:
			{

				break;
			}
			case 8:
			{
				cout << "Exiting\n";
				exit(0);
				break;
			}
		}
	}
	cout << "Working" << endl;

	return 0;
}
