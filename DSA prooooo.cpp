#include <bits/stdc++.h>
using namespace std;

class contactinfo
{
private:
     string name;
     string number;
     bool fav;
     string email;
     string profession;

public:
     contactinfo(string a, string b, bool e = 0, string c = "none", string d = "none")
     {
          name = a;
          number = b;
          fav = e;
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

     bool getfav()
     {
          return fav;
     }

     void mkfav()
     {
          fav = 1;
     }

     void nmkfav()
     {
          fav = 0;
     }

     void setname(string a)
     {
          name = a;
     }
     void setnum(string a)
     {
          number = a;
     }

     void setemail(string a)
     {
          email = a;
     }
     void setprofession(string a)
     {
          profession = a;
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

void displayContactsUtil(Triename *curNode, string prefix, vector<int> *p)
{

     if (curNode->isLast)
     {
          p->push_back(curNode->pos);
          cout << p->size() << ". " << prefix << endl;
     }

     for (char i = 'a'; i <= 'z'; i++)
     {
          Triename *nextNode = curNode->child[i];
          if (nextNode != NULL)
               displayContactsUtil(nextNode, prefix + (char)i, p);
     }
     for (char i = '0'; i <= '9'; i++)
     {
          Triename *nextNode = curNode->child[i];
          if (nextNode != NULL)
               displayContactsUtil(nextNode, prefix + (char)i, p);
     }
     Triename *nextNode = curNode->child[' '];

     if (nextNode != NULL)
     {
          displayContactsUtil(nextNode, prefix + ' ', p);
     }
}

void displayContactsUtil(Trienumber *curNode, string prefix, vector<int> *p)
{

     if (curNode->isLast)
     {
          p->push_back(curNode->pos);
          cout << p->size() << ". " << prefix << endl;
     }

     for (char i = '0'; i <= '9'; i++)
     {
          Trienumber *nextNode = curNode->child[i];
          if (nextNode != NULL)
               displayContactsUtil(nextNode, prefix + (char)i, p);
     }
}

bool displayContactsbyname(string str, vector<int> *p)
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
               cout << "\nNo Results Found for " << str
                    << "\n";
               i++;
               return 0;
          }

          if (i == len - 1)
          {
               cout << "\nSuggestions based on \"" << prefix
                    << "\" are \n";

               displayContactsUtil(curNode, prefix, p);
               return 1;
          }
          prevNode = curNode;
     }
     return 0;
}

bool displayContactsbynum(string str, vector<int> *p)
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
               cout << "\nNo Results Found for " << str
                    << "\n";
               i++;
               return 0;
          }

          if (i == len - 1)
          {
               cout << "\nSuggestions based on \"" << prefix
                    << "\" are \n";

               displayContactsUtil(curNode, prefix, p);
               return 1;
          }

          prevNode = curNode;
     }
     return 1;
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

void displaycontact(contactinfo p)
{
     cout << "Name: " << p.getname() << endl;
     cout << "Phone Number: " << p.getnum() << endl;
     cout << "Email: " << p.getemail() << endl;
     cout << "Profession: " << p.getprofession() << endl;

     string s;
     do
     {
          cout << "\n\nPress ENTER to exit" << endl;
          getline(cin, s);
     } while (s.length() != 0);
}

void addContact()
{
     string name = "", number = "", email = "", prof = "", temp;

     cout << "Enter the following details:\n";

     while (name.size() == 0)
     {
          cout << "Name(required): ";
          getline(std::cin, name, '\n');
          if (name.size() == 0)
          {
               cout << "Please enter a name!";
          }
     }

     while (number.size() != 10)
     {
          cout << "Phone Number(required): ";
          getline(std::cin, number, '\n');
          if (number.size() != 10)
          {
               cout << "Enter a valid 10 digit number!\n";
          }
     }

     cout << "Email: ";
     getline(std::cin, temp);
     if (!temp.empty())
     {
          std::istringstream stream(temp);
          stream >> email;
     }

     cout << "Profession: ";
     getline(std::cin, temp);
     if (!temp.empty())
     {
          std::istringstream stream(temp);
          stream >> prof;
     }

     int x = 1;
     if (email.size() >= 2)
          x += 1;
     else
          email = "";
     if (prof.size() >= 2)
          x += 2;
     else
          prof = "";

     ofstream ifile;
     ifile.open("contacts.txt", ios::app);
     ifile << "\n"
           << x << name << "$ " << number << " " << email << " " << prof;
     ifile.close();
     return;
}

void showfav(vector<contactinfo> p, vector<int> q, vector<int> *f, vector<int> d = {})
{
     int x = 0, y = 0;
     int n = q.size(), m = d.size();
     for (int i = 0; i < n; i++)
     {
          while (y < m && d[y] < q[i])
          {
               y++;
          }
          if (y < m && d[y] == q[i])
          {
               continue;
          }
          f->push_back(q[i]);
          cout << f->size() << ". " << p[q[i]].getname() << endl;
     }
}

void options()
{
     cout << "\nWelcome to ASA Phone Directory\n";
     cout << "Please select a suitable option:\n";
     cout << "1. Search by name\n";   // done
     cout << "2. Search by number\n"; // done
     cout << "3. Add to contact\n";
     cout << "4. Edit Contact\n";
     cout << "5. Delete a contact\n"; // done
     cout << "6. Show favourites\n";  // done
     cout << "7. Add to favourites\n";
     cout << "8. Delete from favourites\n";
     cout << "9. Exit\n"; // done
}

bool contains(vector<int> vec, const int &elem)
{
     bool result = false;
     if (find(vec.begin(), vec.end(), elem) != vec.end())
     {
          result = true;
     }
     return result;
}

void delcontact(vector<int> p) // to be changed from n2 to n
{
     ifstream is("contacts.txt");
     int count = 0;

     ofstream ofs;
     ofs.open("temp.txt", ofstream::out);

     char c;
     int line_no = 1;
     while (is.get(c))
     {
          if (c == '\n')
               line_no++;

          if (!contains(p, line_no - 2))
               ofs << c;
     }

     ofs.close();

     is.close();

     remove("contacts.txt");
     rename("temp.txt", "contacts.txt");
}

void Editcontact(vector<contactinfo> p, int q, int choice)
{

     if (choice == 1)
     {
          trieDelete(rootname, p[q].getname());
          string name;
          cout << "Enter new name: ";
          cin >> name;
          p[q].setname(name);
          insertname(p[q].getname(), q);
     }
     else if (choice == 2)
     {
          trieDelete(rootnum, p[q].getnum());
          string number;
          cout << "Enter new number: ";
          cin >> number;
          p[q].setnum(number);
          insertnum(p[q].getnum(), q);
     }
     else if (choice == 3)
     {
          string email;
          cout << "Enter new email: ";
          cin >> email;
          p[q].setemail(email);
     }
     else if (choice == 4)
     {
          string prof;
          cout << "Enter new profession: ";
          cin >> prof;
          p[q].setprofession(prof);
     }
     else if(choice == 5)
     {
          p[q].mkfav();
     }
     else if(choice == 6)
     {
          p[q].nmkfav();
     }
     else
     {
          cout << "Invalid choice\n";
     }

     int x = 1;
     if (p[q].getemail().size() >= 2)
          x += 1;
     if (p[q].getprofession().size() >= 2)
          x += 2;

     ifstream is("contacts.txt");

     // open file in write mode or out mode
     ofstream ofs;
     ofs.open("temp.txt", ofstream::out);

     // loop getting single characters

     char c;
     int line_no = 1;
     int flag = 0;
     while (is.get(c))
     {

          if (c == '\n')
               line_no++;
          if (line_no == (q + 2) && flag == 0)
          {
               ofs << "\n"
                   << x << p[q].getname() << "$ " << p[q].getnum() << " " << p[q].getfav() << " " << p[q].getemail() << " " << p[q].getprofession();
               flag = 1;
          }

          if (line_no != q + 2)
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
}

int main()
{
     fstream file;
     file.open("contacts.txt", ios::out | ios::in);
     // freopen("contacts.txt", "r", stdin);

     int x, n, m;
     file >> n;
     file >> m;

     vector<contactinfo> p(n);
     vector<int> fav(m);

     string a, b, c, d;
     bool f;
     int favcount = 0;

     for (int i = 0; i < n; i++)
     {
          c = "";
          d = "";
          file >> x;
          getline(file, a, '$');
          // file >> a;
          file >> b;
          file >> f;
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

          contactinfo t(a, b, f, c, d);
          p[i] = t;

          insertname(p[i].getname(), i);
          insertnum(p[i].getnum(), i);
     }

     x = 0;
     for (int i = 0; i < n; i++)
     {
          if (p[i].getfav())
          {
               fav[x++] = i;
          }
     }

     int choice;
     options();
     while (true)
     {
          cin >> choice;
          // choice=7;
          switch (choice)
          {
          case 1: // search by name        //done
          {
               cout << "\nEnter prefix of name: ";
               string s;
               cin >> s;
               vector<int> q;
               if (displayContactsbyname(s, &q))
               {
                    cout << "\nEnter number of contact: ";
                    int x;
                    cin >> x;
                    while (x > q.size())
                    {
                         cout << "\nEnter a Valid number: ";
                         cin >> x;
                    }
                    displaycontact(p[q[x - 1]]);
               }
               break;
          }
          case 2: // search by number      //done
          {
               cout << "\nEnter prefix of num: ";
               string s;
               cin >> s;
               vector<int> q;
               if (displayContactsbynum(s, &q))
               {
                    cout << "\nEnter number of contact: ";
                    int x;
                    cin >> x;
                    while (x > q.size())
                    {
                         cout << "\nEnter a Valid number: ";
                         cin >> x;
                    }
                    displaycontact(p[q[x - 1]]);
               }
               break;
          }
          case 3: // add to contacts
          {
               addContact();
               break;
          }
          case 4: // edit contact
          {
               file.close();
               cout << "\nEnter prefix of name: ";
               string s;
               cin >> s;
               vector<int> q;
               if (displayContactsbyname(s, &q))
               {
                    cout << "\nEnter number of contact: ";
                    int x;
                    cin >> x;
                    while (x > q.size())
                    {
                         cout << "\nEnter a Valid number: ";
                         cin >> x;
                    }
                    int a = q[x - 1];
                    cout << "1.Name\n";
                    cout << "2.Phone Number\n";
                    cout << "3.Email\n";
                    cout << "4.Profession\n";
                    cout << "Enter your choice: ";
                    int choice;
                    cin >> choice;
                    Editcontact(p, a, choice);
               }
               break;
          }
          case 5: // delete contact
          {

               break;
          }
          case 6: // show favourites       //done
          {
               cout << "\nDisplaying Favourite Contacts:\n";
               vector<int> f;
               showfav(p, fav, &f);
               if (f.size() == 0)
               {
                    cout << "No favourite Contacts to show\n";
               }
               else
               {
                    cout << "Select favourite contact number: ";
                    int x;
                    cin >> x;
                    while (x > f.size())
                    {
                         cout << "\nEnter a valid number: ";
                         cin >> x;
                    }
                    cout << endl;
                    displaycontact(p[f[x - 1]]);
               }
               break;
          }
          case 7: // add to favourites     //to delete and add from file
          {
               cout << "\nEnter name prefix: ";
               string s;
               cin >> s;
               vector<int> q;
               if (displayContactsbyname(s, &q))
               {
                    cout << "\nEnter number of contact: ";
                    int x;
                    cin >> x;
                    while (x > q.size())
                    {
                         cout << "\nEnter a Valid number: ";
                         cin >> x;
                    }
                    fav.push_back(q[x - 1]);
                    Editcontact(p, q[x - 1], 5);
                    cout << "\nAdded to favourites: ";
               }
               break;
          }
          case 8: // delete from favourites
          {
               file.close();
               delcontact({0, 3});
               break;
          }
          case 9: // exit                  //to be edit
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
