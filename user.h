#include <iostream>
using namespace std;
class user{
	private:
		string password;
	protected:
		string userid;
		string email;
		string ph_no;
		string address;
		int zipcode;
		string country;
	public:
	void sign_up(){
		int count=0;
		string id;
		system("cls");
		cout << "Enter User Name " << endl;
		cin >> userid ;
		ifstream inp("Users.txt");
		while(inp >> id){
			if(id==userid ){
				cout << "user already exist" << endl; 
				count=1;
				break;
			}
		}
		if(count==0){
			inp.close();
			cout << "Enter Password " << endl ;
			cin >> password;
			cout << "Enter Email " << endl;
			cin >> email ;
			cout << "Enter phone number " << endl ;
			fflush(stdin);
			getline(cin, ph_no);
			cout << "Enter Address " << endl;
			getline(cin, address);
			cout << "Enter Zip code " << endl ;
			cin >> zipcode;
			cout << "Enter country " << endl ;
			cin >> country;
			ofstream obj_wr("Users.txt",ios::app);
			obj_wr << userid << " " << password << " "<< email << " " <<  ph_no << " " << address << " " <<  zipcode << " " << country << endl;	
			obj_wr.close();
			system("cls");
			cout << "Your account successfully created " << endl;
			string f_name_p=userid+"P.txt";
			string f_name_h=userid+"H.txt";
			ofstream obw_P(f_name_p.c_str(),ios::app);
			ofstream obw_H(f_name_h.c_str(),ios::app);
  			obw_P.close();
  			obw_H.close();
			}
		}
	
	
	string log_in(){
		int count = 0;
    	ifstream inp("Users.txt");
		string id,pass;
		cout << "Enter user id: ";
		cin >> id;
		cout << "Enter Password: " ;
		cin >> pass;
		if (!inp.is_open()) {
	        cout << "Error in opening the file!" << endl;
	    } 
	    else{
   	 		while (inp >> userid >> password >> email >> ph_no >> address >> zipcode >> country ) {
        		if (id == userid && pass == password) {
            		count = 1;
            		system("cls");
            		break;
        		}
    		}		
		}
    	inp.close();

    	if (count == 1) {
        	cout << "Login Successful" << endl;
        	return userid;
    	} 
		else {
        	cout << "User does not exist" << endl;
        	return "none";
    	}
	}
	void forget(){
		int opt,count=0,coun=0;
		string id, pass;
		cout << "Enter user id: ";
		cin >> id;
		ifstream inp("Users.txt");
		int temp;
		while(inp >> userid >> password >> email >> ph_no >> address >> zipcode >> country ){
			if(id==userid){
					inp.close();
//					password= pass;
					cout << "Your password is "  << password << endl ;
					inp.close();
					count=1;//if user found
					cout << "Do you want change password to enter 1 " << endl ;
					cout << "If not want to change password enter 0" << endl;
					int choice;
					cin >> choice ;
					if( choice ==1){
							cout << "Enter new password: " ;
							cin >> password;
							ifstream input_file("Users.txt");
    						ofstream output_file("Users_temp.txt");
    						int temp;
							while(input_file >> id >> pass >> email >> ph_no >> address >> zipcode >> country ){
								if(id==userid){
									coun=1;
									output_file << id << " " << password << " " << email << " " << ph_no << " " << address << " " << zipcode << " " << country  <<endl;
								}
								else {
            						output_file << id << " " << pass << " " << email << " " << ph_no << " " << address << " " << zipcode << " " << country << endl;
            					}
							}
							input_file.close();
							output_file.close();
    				}
					break;	
				}
				else {
					count=0;
				}
			}
		if (count == 0) {    	
       		cout << "User not found" << endl;
			
    	}
    	else if (coun==0){
    		remove("Users_temp.txt");
		}
		else if(coun==1){
   			remove("Users.txt");
   			rename("Users_temp.txt", "Users.txt");
    		remove("Users_temp.txt");
		}
	}
};
