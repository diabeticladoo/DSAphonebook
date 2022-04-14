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
    contactinfo(string a, string b, string c = "none", string d = "none")
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

void displayContactsUtil(Triename *curNode, string prefix,vector<int> *p)
{

    if (curNode->isLast)
    {
        p->push_back(curNode->pos);
        cout << p->size() << " " << prefix << endl;
    }

    for (char i = 'a'; i <= 'z'; i++)
    {
        Triename *nextNode = curNode->child[i];
        if (nextNode != NULL)
        displayContactsUtil(nextNode, prefix + (char)i,p);
    }
    for (char i = '0'; i <= '9'; i++)
    {
        Triename *nextNode = curNode->child[i];
        if (nextNode != NULL)
        displayContactsUtil(nextNode, prefix + (char)i,p);
    }
    Triename *nextNode = curNode->child[' '];

    if (nextNode != NULL)
    {
        displayContactsUtil(nextNode, prefix + ' ',p);
    }


}

void displayContactsUtil(Trienumber *curNode, string prefix,vector<int> *p)
{

    if (curNode->isLast)
    {
        p->push_back(curNode->pos);
        cout << p->size() << " " << prefix << endl;
    }

    for (char i = '0'; i <= '9'; i++)
    {
        Trienumber *nextNode = curNode->child[i];
        if (nextNode != NULL)
            displayContactsUtil(nextNode, prefix + (char)i,p);
    }
    
}

bool displayContactsbyname(string str,vector<int> *p)
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

            displayContactsUtil(curNode, prefix,p);
            return 1;
        }
        prevNode = curNode;
    }
    return 0;

        
 
}

bool displayContactsbynum(string str,vector<int> *p)
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

            displayContactsUtil(curNode, prefix,p);
            return 1;
        }

        prevNode = curNode;
    }
    return 1;
  
}

void displaycontact(contactinfo p)
{
    cout << "Name: " << p.getname() << endl;
    cout << "Phone Number: " << p.getnum() << endl;
    cout << "Email: " << p.getemail() << endl;
    cout << "Profession: " << p.getprofession() << endl;
   
    string s;
    do {
     cout << "\n\nPress ENTER to exit" << endl;
     getline(cin, s);
    } while (s.length() != 0);
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


	// displayContactsbyname("an");
	// displayContactsbynum("11");

	int choice;
	cout << "Welcome to ASA Phone Directory\n";
	cout << "Please select a suitable option:\n";
	cout << "1. Search by name\n";          //done
	cout << "2. Search by number\n";        //done
	cout << "3. Add to contact\n";
	cout << "4. Edit Contact\n";
	cout << "5. Add to favourite\n";
	cout << "6. Delete a contact\n";
	cout << "7. Add to contact\n";
	cout << "8. Exit\n";                    //done
	// while (true)
	{
		cin >> choice;
        // choice=2;
		switch (choice)
		{
			case 1:
			{
                cout << "\nEnter prefix of name: ";
                string s;
                cin >> s;
                vector<int> q;
                if(displayContactsbyname(s,&q))
                {
                    cout << "\nEnter number of contact: ";
                    int x;
                    cin >> x;
                    while(x>q.size())
                    {
                        cout << "\nEnter a Valid number: ";
                        cin >> x;
                    }
                    displaycontact(p[q[x-1]]);
                }
				break;
			}
			case 2:
			{
                cout << "\nEnter prefix of num: ";
                string s;
                cin >> s;
                vector<int> q;
                if(displayContactsbynum(s,&q))
                {
                    cout << "\nEnter number of contact: ";
                    int x;
                    cin >> x;
                    while(x>q.size())
                    {
                        cout << "\nEnter a Valid number: ";
                        cin >> x;
                    }
                    displaycontact(p[q[x-1]]);
                }
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
