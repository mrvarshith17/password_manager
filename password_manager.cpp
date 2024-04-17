#include<iostream>
#include<random>
#include<vector>
#include<algorithm>
#include <ctime>
#include<fstream>
#include<string>
#include <Windows.h> 
#include <winuser.h>
using namespace std;

class password_generator {
string my_password;
 vector<char> numbers ={'0','1','2','3','4','5','6','7','8','9'};
 vector<char> alphabets = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
 vector<char> characters = {'!','@','#','$','%','^','&','*'};
public:
string password_gen(){

     my_password.clear();
     for(int i =0 ;i<7;i++){
        my_password.push_back(alphabets[rand()%26]);
     }
     for(int i =0 ;i< 4 ;i++){
        my_password.push_back(numbers[rand()%4]);
     }
     for(int i =0;i< 2 ;i++){
      my_password.push_back(characters[rand()%8]);
     }
     
      random_device rd; 
    mt19937 g(rd()); 

    shuffle(my_password.begin(), my_password.end(), g); 


    return my_password;
}

};

class password_manager: public password_generator{
   string gmail;
   string website;
   string password;
public:

void create_password(){
   password = password_gen();
}

vector<string> split_string(string actual_string, char seperator){

vector<string> list;
string word="";
for(int i =0 ;i<actual_string.length();i++){
 if(actual_string[i]==seperator){
   list.push_back(word);
   word = "";
 }
 else{
   word = word + actual_string[i];
 }
}
 list.push_back(word);
 word="";
return list;
}


void search(){
string site;
cout<<"Enter the name of the website : ";

cin>>site;
transform(site.begin(), site.end(), site.begin(), ::tolower);
fstream fin;

vector<string> coloumn;
string row;
fin.open("passwords.csv",ios::in);
string previous = "";
bool check = false;
 while(fin>>row){
   if(previous==row){
       break;
   }
    coloumn = split_string(row,',');
    if(coloumn[0]==site){
      cout<<"*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"<<endl;
      cout<<"Website : "<<coloumn[0]<<endl;
      cout<<"Gmail   : "<<coloumn[1]<<endl;
      cout<<"Password : "<<coloumn[2]<<endl;
	   toClipboard(coloumn[2]);
      cout<<"*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~"<<endl;
      check =  true;
      break;
    }
 }
 if(check == false){
   cout<<"**********Website doesnt Exist***********"<<endl;
 }
cout<<"==============================================================================================================================="<<endl;

 
}

void insert_data(){
string site;string gmail;
string pass;

cout<<"Website : ";
cin>>site;
transform(site.begin(), site.end(), site.begin(), ::tolower);
cout<<"Gmail : ";
cin>>gmail;
cout<<"____________________________"<<endl;
cout<<"For password \n1.) y -> your own\n2.) g->generate "<<endl;
cout<<"____________________________"<<endl;
char input;
cin>>input;
cout<<"==============================================================================================================================="<<endl;

if(input == 'y'){
   cout<<"Enter the password : ";
   cin>>pass;
}
else{
   create_password();
   pass = password;
   toClipboard(pass);
}
   fstream fout;
   
   fout.open("passwords.csv",ios::out|ios::app);

   fout<<site<<","<<gmail<<","<<pass<<"\n";

   fout.close();

    cout<<"Password : "<<pass<<endl;

    cout<<"******** Details are stored perfectly *********"<<endl;
}


void print_lock(){

   string lock= R"(                                          

                                                               (&&&&&&&&@,                        
                                                            &&&&&&&&&&&&&&&&%                     
                                                          @&&&&&#       &&&&&&,                   
                                                         &&&&&(           @&&&&,                  
                                                         &&&&&             &&&&@                  
                                                         &&&&&             &&&&@                  
                                                         &&&&&&&&&&&&&&&&&&&&&&@                  
                                                      @&&&&&&&&&&&&&&&&&&&&&&&&&&&.               
                                                      &&&&&&&&&&&&&&&&&&&&&&&&&&&&&               
                                                      &&&&&&&&&&&&    *&&&&&&&&&&&&               
                                                      &&&&&&&&&&&       &&&&&&&&&&&               
                                                      &&&&&&&&&&&&    ,&&&&&&&&&&&&               
                                                      &&&&&&&&&&&&@   &&&&&&&&&&&&&               
                                                      &&&&&&&&&&&&@   &&&&&&&&&&&&&               
                                                      &&&&&&&&&&&&&* %&&&&&&&&&&&&&               
                                                      &&&&&&&&&&&&&&&&&&&&&&&&&&&&%               
                                                         &&&&&&&&&&&&&&&&&&&&&&&&(    

                                          **********WELCOME TO YOUR PASSWORD MANAGER*********          
                                               
   )";

   cout<<lock<<endl;
}



void toClipboard(const std::string &s){

   HWND hwnd = GetDesktopWindow();

	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size()+1);
	if (!hg){
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg),s.c_str(),s.size()+1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT,hg);
	CloseClipboard();
	GlobalFree(hg);
   cout<<"*******Password Copied to clipboard **************"<<endl;
}


};
int main(){
srand(time(nullptr));
password_manager p;
p.print_lock();
 
while(true){
char choice;
cout<<"==============================================================================================================================="<<endl;
cout<<"1.)Search Password : enter 'h' "<<endl;
cout<<"2.)Store  Password : enter 'j' "<<endl;
cout<<"3.)To Exit         : enter 'x' "<<endl;
cout<<"*****Enter your choice : ";
cin>>choice;
cout<<"==============================================================================================================================="<<endl;
if(choice=='h'){
   p.search();
}
else if(choice == 'j'){
   p.insert_data();
}
else{
   cout<<"xxxxxxxxxxx You are exited from the program xxxxxxxxxxx";
   break;
}
}
return 0;
}