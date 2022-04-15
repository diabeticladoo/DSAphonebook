case 8:         //delete from favourites // edit in file
			{
                vector<int> t;
                showfav(p,fav,&t,del);
                cout << "\n Enter number of contact to be removed from favourite: ";
                int x;
                cin >> x;
                while(x>t.size());
                {
                    cout << "\nEnter a valid number: ";
                    cin >> x;
                }

                cout << endl << p[t[x-1]].getname() << " contact removed from favourites "; 
                m--;
                for(int i=0;i<fav.size();i++)
                {
                    if(fav[i]==t[x-1])
                    {
                        fav[i]=-1;
                        break;
                    }
                }

				break;
			}
