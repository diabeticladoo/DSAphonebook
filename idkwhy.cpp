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

bool isEmpty(Triename *rootname)
{
 for (char i = 'a'; i <= 'z'; i++)
  if (rootname->child[i])
   return false;

 for (char i = '0'; i <= '9'; i++)
  if (rootname->child[i])
   return false;

 if (rootname->child[' '])
  return false;

 return true;
}

bool isEmpty(Trienumber *rootnum)
{
 for (char i = 'a'; i <= 'z'; i++)
  if (rootnum->child[i])
   return false;

 for (char i = '0'; i <= '9'; i++)
  if (rootnum->child[i])
   return false;

 if (rootnum->child[' '])
  return false;

 return true;
}
Triename *trieDelete(Triename *rootname, string word, int height = 0)
{
 if (!rootname)
 {
  return NULL;
 }

 if (height == word.size())
 {

  if (rootname->isLast)
  {
   rootname->isLast = false;
  }

  if (isEmpty(rootname))
  {
   delete (rootname);
   rootname = NULL;
  }
  return rootname;
 }

 Triename *itr = rootname;
 Triename *nextNode = itr->child[word[height]];
 itr->child[word[height]] = trieDelete(itr->child[word[height]], word, height + 1);

 if (isEmpty(rootname) && rootname->isLast == false)
 {
  delete (rootname);
  rootname = NULL;
 }
 return rootname;
}

Trienumber *trieDelete(Trienumber *rootname, string word, int height = 0)
{
 if (!rootnum)
 {
  return NULL;
 }

 if (height == word.size())
 {

  if (rootnum->isLast)
  {
   rootnum->isLast = false;
  }

  if (isEmpty(rootnum))
  {
   delete (rootnum);
   rootnum = NULL;
  }
  return rootnum;
 }

 Trienumber *itr = rootnum;
 Trienumber *nextNode = itr->child[word[height]];
 itr->child[word[height]] = trieDelete(itr->child[word[height]], word, height + 1);

 if (isEmpty(rootnum) && rootnum->isLast == false)
 {
  delete (rootnum);
  rootnum = NULL;
 }
 return rootnum;
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

void delcontact(int n, vector<contactinfo> p)
{
 // open file in read mode or in mode
 ifstream is("contacts.txt");
 trieDelete(rootname, p[n].getname());

 // open file in write mode or out mode
 ofstream ofs;
 ofs.open("temp.txt", ofstream::out);

 // loop getting single characters
 char c;
 int line_no = 1;
 while (is.get(c))
 {
  // if a newline character
  if (c == '\n')
   line_no++;

  // file content not to be deleted
  if (line_no != n + 2)
   ofs << c;
 }

 // closing output file
 ofs.close();

 // closing input file
 is.close();

 // remove the original file
 remove("contacts.txt");

 // rename the file
 rename("temp.txt", "contacts.txt");

 for (int i = 0; i < p.size() - 1; i++)
 {
  if (i >= n)
  {
   swap(p[i], p[i + 1]);
  }
 }
 p.pop_back();
}

int main()
{
 fstream file;
 file.open("contacts.txt", ios::out | ios::in);
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
   displayContactsbyname("a");

   break;
  }
  case 2:
  {

   break;
  }
  case 3:
  {
   // addcontact();
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
   file.close();
   delcontact(0, p);

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