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
    contactinfo(string a, string b,bool e=0, string c = "none", string d = "none")
    {
        name = a;
        number = b;
        fav=e;
        email = c;
        profession = d;
    }

    contactinfo(){}

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
        fav=1;
    }

    void nmkfav()
    {
        fav=0;
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

bool checkname(string s)
{
    int len = s.length();
    Triename *itr = rootname;

    for (int i = 0; i < len; i++)
    {
        Triename *nextNode = itr->child[s[i]];
        if (nextNode == NULL)
        {
            return 0;
        }

        itr = nextNode;

        if (i == len - 1)
        {
            if(itr->isLast)
            {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}

bool checknum(string s)
{
    int len = s.length();
    Trienumber *itr = rootnum;

    for (int i = 0; i < len; i++)
    {
        Trienumber *nextNode = itr->child[s[i]];
        if (nextNode == NULL)
        {
            return 0;
        }

        itr = nextNode;

        if (i == len - 1)
        {
            if(itr->isLast)
                return 1;
            
            return 0;
        }
    }
    return 0;
}

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
        cout << p->size() << ". " << prefix << endl;
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
        cout << p->size() << ". " << prefix << endl;
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
    cout << "Fav contact: ";
    if(p.getfav())
        cout << "YES\n";
    else
        cout << "NO\n";
    cout << "Email: " << p.getemail() << endl;
    cout << "Profession: " << p.getprofession() << endl;
   
    string s;
    do {
        getline(cin, s);
    } while (s.length() != 0);

}

contactinfo addContact(int n)
{
    string name = "", number = "", email = "", prof = "", temp;

    cout<<"Enter the following details:\n";

    string s;
    do {
    getline(cin, s);
    } while (s.length() != 0);
    cout << endl;

    while(name.size() == 0){
        cout<<"Name(required): ";
        getline(std::cin, name, '\n');
        if(name.size() == 0){
            cout<<"Please enter a name!";
        }     
    }

    while(number.size() != 10){
        cout<<"Phone Number(required): ";
        getline(std::cin, number, '\n');
        if(number.size() != 10){
            cout<<"Enter a valid 10 digit number!\n";
        }
    }

    cout << "Email: ";
    getline(std::cin, temp);
    if (!temp.empty()) {
        std::istringstream stream(temp);
        stream >> email;
    }

    cout<<"Profession: ";
    getline(std::cin, temp);
    if (!temp.empty()) {
        std::istringstream stream(temp);
        stream >> prof;
    }

    int x = 1;
    if(email.size()>=2)      x+=1;
    else                     email = "";
    if(prof.size()>=2)       x+=2;
    else                     prof = "";
    
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    transform(email.begin(), email.end(), email.begin(), ::tolower);
    transform(prof.begin(), prof.end(), prof.begin(), ::tolower);

    bool bb=1;
    while(bb)
    {
        bool c=checkname(name);
        bool d=checknum(number);
        if(c && d)
        {
            cout << "Same name and number already exists, enter valid details: \n";
        }
        else if(c)
        {
            cout << "Same name already exists, enter valid details: \n";
        }
        else if(d)
        {
            cout << "Same number already exists, enter valid number: \n";
        }
        else
        {
            bb=0;
            break;
        }
        name="";

        while(name.size() == 0){
            cout<<"Name(required): ";
            getline(std::cin, name, '\n');
            if(name.size() == 0){
                cout<<"Please enter a name!";
            }     
        }

        number="";
        while(number.size() != 10){
            cout<<"Phone Number(required): ";
            getline(std::cin, number, '\n');
            if(number.size() != 10){
                cout<<"Enter a valid 10 digit number!\n";
            }
        }

        cout << "Email: ";
        getline(std::cin, temp);
        if (!temp.empty()) {
            std::istringstream stream(temp);
            stream >> email;
        }

        cout<<"Profession: ";
        getline(std::cin, temp);
        if (!temp.empty()) {
            std::istringstream stream(temp);
            stream >> prof;
        }

        int x = 1;
        if(email.size()>=2)      x+=1;
        else                     email = "";
        if(prof.size()>=2)       x+=2;
        else                     prof = "";
        
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        transform(email.begin(), email.end(), email.begin(), ::tolower);
        transform(prof.begin(), prof.end(), prof.begin(), ::tolower);

    }


    contactinfo t(name,number,0,email,prof);
    ofstream ifile;
    ifile.open("contacts.txt", ios::app);
    ifile << "\n" << x << name << "$ " << number << " " << 0 << " " << email << " " << prof;
    ifile.close();
    
    insertname(name,n);
    insertnum(number,n);

    return t;
}

void showfav(vector<contactinfo> p,vector<int> q,vector<int> *f,vector<int> d={})
{
    int x=0,y=0;
    int n=q.size(),m=d.size();
    for(int i=0;i<n;i++)
    {
        if(q[i]==-1)
        {
            continue;
        }
        while(y<m && d[y]<q[i])
        {
            y++;
        }
        if(y<m && d[y]==q[i])
        {
            continue;
        }
        f->push_back(q[i]);
        cout << f->size() << ". " << p[q[i]].getname() << endl; 
    }

}

void options(int x=1)
{
    if(x)
    {
        string s;
        cin.sync();
        do {
         cout << "\nPress ENTER to return";
        getline(cin, s);
        } while (s.length() != 0);
    }

    cout << "\nWelcome to ASA Phone Directory\n";
	cout << "Please select a suitable option:\n";
	cout << "1. Search by name\n";     
	cout << "2. Search by number\n";   
	cout << "3. Add to contact\n";     
	cout << "4. Edit Contact\n";
	cout << "5. Delete a contact\n";   
	cout << "6. Show favourites\n";    
	cout << "7. Add to favourites\n";         
	cout << "8. Delete from favourites\n";
    cout << "9. Show all contacts\n";       
    cout << "10. Exit\n";                  
}

void delcontact(vector<int> p,int n,int m)  
{
    ifstream is("contacts.txt");
    int count = 0;

    ofstream ofs;
    ofs.open("temp.txt", ofstream::out);

    char c;
    int line_no = 1;
    sort(p.begin(),p.end());
    int x=0;
    ofs<<n<<" "<<m;

    while (is.get(c))
    {
        while(x<p.size() && p[x]<line_no -2)    
            x++;
        
        if (c == '\n')
            line_no++;

        if ((x<p.size() && p[x]==line_no - 2) || line_no==1)
            continue;
        else
            ofs << c;
    }

    ofs.close();
    is.close();

    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");
}

void dispall(vector<contactinfo> p)
{
    vector<int> q;
    displayContactsUtil(rootname,"",&q);
    cout << "\n--Enter 0 to cancel--\n";
    cout << "Choose contact number: ";
    int x;
    cin >> x;
    if(!x)
        return;
    else
    {
        while(x>q.size())
        {
            cout << "\nEnter a valid number: ";
            cin >> x;
        }
        
        displaycontact(p[q[x-1]]);
    }
}

void Editcontact(vector<contactinfo> &p, int q, int choice)
{
    
    if (choice == 1)
    {
        trieDelete(rootname, p[q].getname());
        string name="";
        cout << "Enter new name: ";
        
        string s;
        do {
            getline(cin, s);
        } while (s.length() != 0);
        
        while(name.size()==0)
        {
            getline(std::cin, name, '\n');
            if(name.size() == 0){
                cout<<"Please enter a name!";
            }     
        }

        if(checkname(name))
        {
            cout <<"Name already exists in the directory!\n";
            return;
        }
        else
        {
            cout << "Name edited successfully\n";
        }

        p[q].setname(name);
        insertname(p[q].getname(), q);
    }
    else if (choice == 2)
    {
        trieDelete(rootnum, p[q].getnum());
        string number="";
        // cout << "Enter new number: ";

        string s;
        do {
            getline(cin, s);
        } while (s.length() != 0);
        
        while(number.size() != 10)
        {
            cout<<"Enter new number: ";
            getline(std::cin, number, '\n');
            if(number.size() != 10)
            {
                cout<<"Enter a valid 10 digit number!\n";
            }
        }

        if(checknum(number))
        {
            cout <<"Number already exists in the directory!\n";
            return;
        }
        else
        {
            cout << "Number edited successfully\n";
        }


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

    ofs.close();
    is.close();

    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");
}

void copy(int x)
{
    string line;
    string inputfile="contacts.txt";
    string outputfile="contacts_backup.txt";
    
    if(!x)
    {
        swap(inputfile,outputfile);
    }
 
    ifstream file1 (inputfile);
    ofstream file2 (outputfile);

    if(file1 && file2){
 
        while(getline(file1,line)){
            file2 << line << "\n";
        }
    }
 
    file1.close();
    file2.close();

}

int main()
{
	fstream  file;

    copy(0);

    file.open("contacts.txt", ios::out | ios::in );
    

	int x, n,m;
	file >> n;
    file >> m;

	vector<contactinfo> p(n);
    vector<int> fav(m);
	string a, b, c, d;
    int favcount=0;
    bool f;

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

    file.close();
    x=0;
    for(int i=0;i<n;i++)
    {
        if(p[i].getfav())
        {
            fav[x++]=i;    
        }
    }    
    
    vector<int> del;
	options(0);    

    while (true)
	{
        int choice;
        cout<<"Option: ";
		cin >> choice;
		switch (choice)
		{
			case 1:         //search by name  
			{
                cout << "Enter prefix of name: ";
                string s="";
                while(s.length()<1)
                getline(cin,s,'\n');
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
                else
                {
                    cout << "No name of prefix " << s << endl;
                }
                options();
				break;
			}

			case 2:         //search by number    
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
                else
                {
                    cout << "No number of prefix " << s << endl;
                }
                options();
				break;
			}

			case 3:         //add to contacts       
			{                
                p.push_back(addContact(n));
                n++;

                cout << "\nContact added successfully\n";
                options();
				break;
			}

			case 4:         //edit contact          
			{
                if(!n){
                    cout<<"\nNo contacts available in phonebook to edit\n";
                } else {
                    cout << "\n1. Search contact by name\n";
                    cout << "2. Search contact by number\n";
                    cout << "Choose option number: ";
                    int x;
                    cin >> x;
                    while(!(x==1 || x==2))
                    {
                        cout << "Enter a valid number: ";
                        cin >> x;
                    }
                    string s;
                    if(x==1)
                    {
                        cout << "Enter prefix of name: ";
                    }
                    else
                    {
                        cout << "Enter prefix of number: ";
                    }
                    cin >> s;
                    vector<int> t;
                    int y=0;
                    if(x==1)
                    {
                        y=displayContactsbyname(s,&t);
                    }
                    else
                        y=displayContactsbynum(s,&t);

                    if(y==0)
                    {
                        cout << "No contact of prefix " << s << endl;
                        options();
                        break;
                    }
                    cout << "Select the contact you want to Edit ";
                    cout<<"\n--Press 0 to cancel--\n";
                    cin >> x;
                    if(!x){          
                        options();
                        break;
                    }
                    while(x>t.size())
                    {
                        cout << "Enter a valid number: ";
                        cin >> x;
                    }
                    int a = t[x - 1];
                    cout << "What do you want to edit?\n";
                    cout << "1.Name\n";
                    cout << "2.Phone Number\n";
                    cout << "3.Email\n";
                    cout << "4.Profession\n";
                    cout << "Enter your choice: ";
                    int choice;
                    cin >> choice;
                    Editcontact(p, a, choice);
                }
                options();
				break;
			}

			case 5:         //delete contact     
			{
                if(!n){
                    cout<<"\nNo contacts available in phonebook\n";
                } else {
                    cout << "\n1. Delete contact by name\n";
                    cout << "2. Delete contact by number\n";
                    cout << "Choose option number: ";
                    int x;
                    cin >> x;
                    while(!(x==1 || x==2))
                    {
                        cout << "Enter a valid number: ";
                        cin >> x;
                    }
                    string s;
                    if(x==1)
                    {
                        cout << "Enter prefix of name: ";
                    }
                    else
                    {
                        cout << "Enter prefix of number: ";
                    }
                    cin >> s;
                    vector<int> t;
                    int y=0;
                    if(x==1)
                    {
                        y=displayContactsbyname(s,&t);
                    }
                    else
                        y=displayContactsbynum(s,&t);

                    if(y==0)
                    {
                        cout << "No contact of prefix " << s << endl;
                    }
                    cout << "Select the contact you want to delete ";
                    cout << "\n--Enter 0 to cancel--\n";
                    cin >> x;
                    if(!x){          
                        options();
                        break;
                    }
                    while(x>t.size())
                    {
                        cout << "Enter a valid number: ";
                        cin >> x;
                    }
                    cout << "Contact " << p[t[x-1]].getname() << " Deleted \n";
                    trieDelete(rootname, p[t[x-1]].getname());
                    del.push_back(t[x-1]);
                    n--;
                }
                options();
				break;
			}

			case 6:         //show favourites 
			{
                    cout << "\nDisplaying Favourite Contacts:\n";
                    vector<int> f;
                    showfav(p,fav,&f,del);
                    if(f.size()==0)
                    {
                        cout << "No favourite Contacts\n";
                    }
                    else
                    {
                        cout << "Select favourite contact number: ";
                        int x;
                        cout << "\n--Enter 0 to cancel--\n";
                        cin >> x;
                        if(!x){          
                            options();
                            break;
                        }
                        while(x>f.size())
                        {
                            cout << "\nEnter a valid number: ";
                            cin >> x;
                        }
                        cout << endl;
                        displaycontact(p[f[x-1]]);
                    }
                options();
				break;
			}

			case 7:         //add to favourites    
			{
                if(!n){
                    cout<<"\nNo contacts in phonebook to add to favourites\n";
                } else {
                    cout << "\nEnter prefix contact name: ";
                    string s;
                    cin >> s;
                    vector<int> q;
                    if(displayContactsbyname(s,&q))
                    {
                        cout << "\nEnter number of contact: ";
                        int x;
                        cout << "\n--Enter 0 to cancel--\n";
                        cin >> x;
                        if(!x){          
                            options();
                            break;
                        }
                        while(x>q.size())
                        {
                            cout << "\nEnter a Valid number: ";
                            cin >> x;
                        }

                        if (find(fav.begin(), fav.end(), q[x - 1]) != fav.end())
                        {
                            cout << "Contact already in favourites\n";
                            options();
                            break;
                        }

                        Editcontact(p,q[x-1],5);

                        fav.push_back(q[x-1]);
                        m++;
                        cout << endl << p[q[x-1]].getname() << " contact added to favourites \n";
                    }
                    else
                    {
                        cout << "\nNo contacts with prefix " << s << endl;
                    }
                }
                options();
                break;
			}

			case 8:         //delete from favourites 
			{
                if(!fav.size())
                {
                    cout << "No favourites\n";
                    options();
                    break;
                }
                vector<int> t;
                showfav(p,fav,&t,del);
                cout << "\nEnter number of contact to be removed from favourite: ";
                int y;
                cout << "\n--Enter 0 to cancel--\n";
                cin >> y;
                if(!y){          
                    options();
                    break;
                }
                while(y>t.size())
                {
                    cout << "\nEnter a valid number: ";
                    cin >> y;
                }
                Editcontact(p,t[y-1],6);
                cout << endl << p[t[y-1]].getname() << " contact removed from favourites "; 
                m--;
                for(int i=0;i<fav.size();i++)
                {
                    if(fav[i]==t[y-1])
                    {
                        fav[i]=-1;
                        break;
                    }
                }
                options();
				break;
			}
            
            case 9:         //display all contacts  
            {
                if(!n){
                    cout<<"\nNo contacts available in phonebook\n";
                } else {
                    dispall(p);
                }
                options();
                break;
            }

            case 10:        //exit                 
            {
                delcontact(del,n,m);
                cout << "Exiting\n";
                copy(1);
				exit(0);
				break;
            }

            default:
            {
                cout<<"Wrong Option!!\n";
                options(0);
                break;
            }
        }
	}

	
    
    return 0;
}
