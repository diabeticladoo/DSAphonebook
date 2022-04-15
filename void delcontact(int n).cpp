void delcontact(int n)
{
 // open file in read mode or in mode
 ifstream is("contacts.txt");

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
  if (line_no != n)
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
