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
// make tree for numbers
// add star cont adding bool
// taking user input, add,delete making menu
//

struct Triename
{
  unordered_map<char, Triename *> child;

  bool isLast;
  int pos;

  Triename()
  {

    for (char i = 'a'; i <= 'z'; i++)
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

Triename *root = new Triename();
Trienumber *root2 = new Trienumber();

void insert(string s, int i, Triename *root)
{
  int len = s.length();

  Triename *itr = root;

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
      itr->pos = i;
    }
  }
}

void insert(string s, int pos, Trienumber *root2)
{
  int len = s.length();
  Trienumber *itr = root2;

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
      itr->pos = i;
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
  Triename *prevNode = root;

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
  Trienumber *prevNode = root2;

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
  freopen("contacts.txt", "r", stdin);
  int x, n;
  cin >> n;

  vector<contactinfo> p(n);
  string a, b, c, d;

  for (int i = 0; i < n; i++)
  {
    c = "";
    d = "";
    cin >> x;
    getline(std::cin, a, '$');
    // cin >> a;
    cin >> b;
    if (x == 2)
    {
      cin >> c;
    }
    else if (x == 3)
    {
      cin >> d;
    }
    else if (x == 4)
    {
      cin >> c >> d;
    }

    contactinfo t(a, b, c, d);
    p[i] = t;

    insert(p[i].getname(), i, root);
    insert(p[i].getnum(), i, root2);
  }

  for (int i = 0; i < n; i++)
  {
    contactinfo t = p[i];
    cout << t.getname() << " " << t.getnum() << "\n";
    cout << t.getemail() << " " << t.getprofession() << endl;
  }
  cout << "end\n\n";

  displayContactsbyname("al");
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