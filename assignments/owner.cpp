/**********|**********|**********|**********|**********|**********|**********|
Program :               oop_proj_y2s5.cpp
Course :                Object Oriented Programming
Year :                  2020/21 Trimester 1
Name :                  Elton Wong Chun Meng
ID:                     1181203056
Lecture Section:        TC02
Tutorial Section :      TT04
Email :                 eltonwcm00@gmail.com / 1181203056@student.mmu.edu.my
Phone :                 01111207201
/**********|**********|**********|**********|**********|**********|**********/



/**
  * Class - Input from user
  * Function - Feature logic
  * Main Function - Call others function
  */



#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<time.h>
using namespace std;

void registerLogic();
void loginUserValidationLogic();
void loginPassValidationLogic();
void menuLogic();
void insertNewItemsLogic();

/*********************************************** REGISTER CLASS ***********************************************/

class Register {
	
	private:
		string oname;
		string pass, cfrmpass;
	
	public:
		void usernameRegister() {
			cout<<"Set a username : ";
			getline(cin, oname);
			cout<<endl;	
		}
		
		void passRegister() {
			cout<<"Enter a password : ";
			cin>>pass;
			cout<<"Re-enter the password : ";
			cin>>cfrmpass;	
		
			while(pass != cfrmpass) {
				cout<<"The password you entered is not matched ! Please try again"<<endl<<endl;
				cout<<"Enter a password : ";
			    cin>>pass;
			    cout<<"Re-enter the password : ";
			    cin>>cfrmpass;	
			}	
		}
		
		string getUser() {
			return oname;
		}
		
		string getPass() {
			return pass;
		}	
		
		string getCfrmpass() {
			return cfrmpass;
		}		
};

/*********************************************** LOGIN CLASS ***********************************************/

class Login {
	
	private:
		string username;
		string pass;
		
	public:
		usernameLogin() {	
			cout<<"Enter your username : ";
			cin.ignore();
			getline(cin, username);
		}
		
		passLogin() {
			cout<<"Enter your password : ";
			cin>>pass;
		}
		
		string getUser() {
			return username;
		}
		
		string getPass() {
			return pass;
		}		
};

/*********************************************** OWNER MENU CLASS ***********************************************/

class Menu {
	
	private:
		int selection;
		
	public:
		menuDisplay() {
			cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
			cout<<"          WELCOME TO MMU SHOPPING KIOSK OWNER SYSTEM          "<<endl;
			cout<<"++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
			cout<<endl<<endl;
			cout<<" 1. Login "<<endl;
			cout<<" 2. Register "<<endl;
			cout<<" 3. View Items "<<endl;
			cout<<" 4. Insert New Items "<<endl;
			cout<<" 5. Update Information Of Items "<<endl;
			cout<<" 6. Delete Items "<<endl;
			cout<<" 0. Exit "<<endl;
		}
		
		menuSelection() {
			cout<<endl;
			cout<<"Please choose an operation to proceed !"<<endl;
			cin>>selection;
			
			cin.ignore();
		}
				
		friend void menuLogic();	
};

/*********************************************** OWNER INSERT CLASS ***********************************************/

class InsertNewItems {

	private:
		int new_item_id, new_item_units, number, category_number ;
		string new_item_name, new_item_company;
		float new_item_price;

	public:
		insertItemsCategory() {
			cout<<"----------------------"<<endl;
			cout<<"    Item Categories    "<<endl;
			cout<<"----------------------"<<endl;
			cout<<" 1. Magazine "<<endl<<" 2. Book "<<endl<<" 3. Movie "<<endl;
			
			cout<<"Please choose a category that you would like to insert new items";
			cin>>category_number;
		}
		
		insertItemsInput() {
			cout<<"How many new items you would like to add into system : ";
			cin>>number;
			cout<<endl;

			cin.ignore();
		}

		insertgetNumber() {
			return number;
		}

		insertItemsMenuDetails() {
			cout<<"Product name : ";
			getline(cin, new_item_name);

			cout<<"Product price : ";
			cin>>new_item_price;
			cout<<"Number of product units available : ";
			cin>>new_item_units;
			
			cin.ignore();

			cout<<"Name of the company which produces the item : ";
			getline(cin, new_item_company);
			
			cout<<endl;
		}

		friend void insertNewItemsLogic();
};

class ShopItem {

	protected: 
		int shopitem_yr, shopitem_month;
		string shopitem_author;
		string shopitem_actor;

	public:
		virtual void itemDisplay() = 0;

		/*void setVar(int yr_shopitem, int month_shopitem, string author_shopitem,
					string actor_shopitem) {
						shopitem_yr = yr_shopitem;
						shopitem_month = month_shopitem;
						shopitem_author = author_shopitem;
						shopitem_actor = actor_shopitem;*/
		}

	friend void insertNewItemsLogic();
};

class Magazine: public ShopItem {

	public:
		void itemDisplay() {
			cout<<"Year of publication : ";
			cin>>shopitem_yr;
			cout<<"Month of publication : ";
			cin>>shopitem_month;
		}
};

class Book: public ShopItem {

	public:
		void itemDisplay() {
			cout<<"Name of the author : ";
			getline(cin, shopitem_author);
		}
};

class Movie: public ShopItem {
	
	public:
		void itemDisplay() {
			cout<<"Name of the actor : ";
			getline(cin, shopitem_actor);
		}
};

/*********************************************** registerLogic() ***********************************************/

void registerLogic() {
	
	Register reg_obj;
	ofstream out_reg_file;
	
	string oname;
	string password, cfrmpassword;
	
	out_reg_file.open("owner-details.txt", std::ios_base::app);

	if(!out_reg_file) {
		cout<<"File is not found !"<<endl;
	} else {
		
		reg_obj.usernameRegister();
		reg_obj.passRegister();
		
		oname = reg_obj.getUser();
		password = reg_obj.getPass();
		cfrmpassword = reg_obj.getCfrmpass();
		
		cout<<endl;
		cout<<"Register is completed and the data is saved !"<<endl<<endl;
		
		out_reg_file<<oname<<setw(15)<<password<<setw(15)<<cfrmpassword<<endl;		
	}
			
	out_reg_file.close();
}

/*********************************************** loginUserValidationLogic() ***********************************************/

void loginUserValidationLogic() {
	
	Login log_obj;
	ifstream in_log_file_user;

	string username, oname;
	int offset_name;
	bool validate_name;
	
	in_log_file_user.open("owner-details.txt");

	log_obj.usernameLogin();
	username = log_obj.getUser();
	
	if(in_log_file_user.is_open()) {

		while(!in_log_file_user.eof()) {
			
			getline(in_log_file_user, oname);
			
			if((offset_name = oname.find(username, 0))!= string::npos) {	
				validate_name = true;
				break;
			} else {
				validate_name = false;	
			}	
		}
		
		if (validate_name == true) {
			cout<<"Username is matched ! You can proceed to enter your password "<<endl<<endl;
			loginPassValidationLogic();
		} else {
			cout<<"Name is incorrect or not found ! Please exit the program and try again "<<endl<<endl;
			exit(1);
		}
	
		in_log_file_user.close();
	} else {
		cout<<"File is not found !";
	}		
}

/*********************************************** loginPassValidationLogic() ***********************************************/

void loginPassValidationLogic() {
	
	Login log_obj;
	ifstream in_log_file_user;

	string pass, password;
	int offset_pass;
	bool validate_pass;
	
	in_log_file_user.open("owner-details.txt");

	log_obj.passLogin();
	pass = log_obj.getPass();
	
	if(in_log_file_user.is_open()) {

		while(!in_log_file_user.eof()) {
			
			getline(in_log_file_user, password);
			
			if((offset_pass = password.find(pass, 0))!= string::npos) {	
				validate_pass = true;
				break;
			} else {
				validate_pass = false;	
			}	
		}
		
		if(validate_pass == true) {
			cout<<"Password is matched !"<<endl<<endl;
		} else {
			cout<<"Password incorrect ! Please try again later"<<endl<<endl;
			exit(1);	
		}
	
		in_log_file_user.close();
	}
}

/*********************************************** menuLogic() ***********************************************/

void menuLogic() {
	
	Menu menu_obj;
	char proceed;
	
	do {
		menu_obj.menuDisplay();
		menu_obj.menuSelection();
		cout<<endl;
		
		switch(menu_obj.selection) {
			case 0 : cout<<"Thank you for using !";
					 exit(0);
				 	 break;
				 		
			case 1 : cout<<"Reading from the file...."<<endl<<endl;
				 	 cout<<"===================================="<<endl;
				 	 cout<<"              LOGIN                 "<<endl;
	             	 cout<<"===================================="<<endl<<endl;
				 	 cout<<endl;

				 	 loginUserValidationLogic();
				 	 break;
				 
			case 2 : cout<<"===================================="<<endl;
				 	 cout<<"              REGISTER              "<<endl;
		         	 cout<<"===================================="<<endl<<endl;
					 cout<<endl;

		         	 registerLogic();
				 	 break;
				 
			case 4 : cout<<"=========================================="<<endl;
				 	 cout<<"              INSERT NEW ITEMS            "<<endl;
		         	 cout<<"=========================================="<<endl;
					 cout<<endl;

					 insertNewItemsLogic();
					 break;

			//case 3, 5, 6
		}
	
		cout<<"Would you like to continue ? [ Y / N ]"<<endl;
		cin>>proceed;
	
		cin.ignore();	

	} while (proceed == 'Y' || proceed == 'y');
	
	cout<<"Thank you for using !";	
}

/*********************************************** insertNewItemsLogic() ***********************************************/

void insertNewItemsLogic() {
	
	InsertNewItems insert_new_obj;
	Magazine insert_magazine_obj;
	Book insert_book_obj;
	Movie insert_movie_obj;

	ofstream out_insert_file;

	int new_itemid, new_itemunits;
	string new_itemname, new_itemcompany;
	float new_itemprice;

	int shop_itemyr, shop_itemmonth;
	string shop_itemauthor;
	string shop_itemactor;

	int rand_number;

	insert_new_obj.insertItemsCategory();
	
	switch(insert_new_obj.category_number) {
		
		case 1 : out_insert_file.open("owner-magazine-insert.txt", std::ios_base::app);
				 break;
		case 2 : out_insert_file.open("owner-book-insert.txt", std::ios_base::app);
				 break;
		case 3:  out_insert_file.open("owner-movie-insert.txt", std::ios_base::app);
				 break;
		default: cout<<"The option is unavailable at the moment ! Please try again later";
				 exit(1);
	}

	if(!out_insert_file) {
		cout<<"File is not found !"<<endl;
	} else {
		
		insert_new_obj.insertItemsInput();

		for(int x=0; x<insert_new_obj.insertgetNumber(); x++) {

			insert_new_obj.insertItemsMenuDetails();

			srand (time(NULL));
			rand_number=rand()%20;

			new_itemname = insert_new_obj.new_item_name;
			new_itemprice = insert_new_obj.new_item_price;
			new_itemunits = insert_new_obj.new_item_units;
			new_itemcompany = insert_new_obj.new_item_company;

			shop_itemyr = insert_magazine_obj.shopitem_yr;
			shop_itemmonth = insert_magazine_obj.shopitem_month;
			shop_itemauthor = insert_book_obj.shopitem_author;
			shop_itemactor = insert_movie_obj.shopitem_actor;
			
			if(insert_new_obj.category_number == 1) {
				insert_magazine_obj.itemDisplay();

				out_insert_file<<rand_number<<setw(15)<<new_itemname<<setw(15)<<new_itemprice<<setw(15)<<
							new_itemunits<<setw(15)<<new_itemcompany<<setw(15)<<shop_itemyr
							<<shop_itemmonth<<endl;

			} else if(insert_new_obj.category_number == 2) {
				insert_book_obj.itemDisplay();

				out_insert_file<<rand_number<<setw(15)<<new_itemname<<setw(15)<<new_itemprice<<setw(15)<<
							new_itemunits<<setw(15)<<new_itemcompany<<setw(15)<<shop_itemauthor<<endl;
				
			} else if(insert_new_obj.category_number == 3) {
				insert_movie_obj.itemDisplay();

				out_insert_file<<rand_number<<setw(15)<<new_itemname<<setw(15)<<new_itemprice<<setw(15)<<
							new_itemunits<<setw(15)<<new_itemcompany<<setw(15)<<shop_itemactor<<endl;

			} else {
				cout<<"The option is unavailable at the moment ! Please try again later";
			  	exit(1);
			} 

			cout<<endl;
			cout<<"Insertion of new products is completed and the data is saved !"<<endl<<endl;	
		}
	}

	out_insert_file.close();
}

/*********************************************** insertNewItemsExtraLogic() ***********************************************/

void insertNewItemsExtraLogic() {

}

/*********************************************** int main() ***********************************************/

int main() {	
	
	menuLogic();
		
	return 0;
}

// CREDIT : https://stackoverflow.com/questions/2393345/how-to-append-text-to-a-text-file-in-c
//          https://www.youtube.com/watch?v=s3-DmI1ZWxE&t=151s
//			http://key-to-programming.blogspot.com/2015/01/program-for-auto-number-generator-auto.html
//			https://www.educative.io/edpresso/what-is-a-cpp-abstract-class