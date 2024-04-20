#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <windows.h>
#include "MMSystem.h"
#include "playlists.h"
#include "user.h"
#include <conio.h>
using namespace std;
#pragma comment(lib, "Winmm.lib")



class AVLNode {
public:
    MusicPlayer key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(MusicPlayer value) {
        key = value;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

class AllMusic {
public:
    AVLNode* root;

    AllMusic() {
        root = NULL;
    }

    int getHeight(AVLNode* node) {
        if (node == NULL) {
            return 0;
        }
        return node->height;
    }

    int getBalance(AVLNode* node) {
        if (node == NULL) {
            return 0;
        }
        return getHeight(node->left) - getHeight(node->right);
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLNode* insert(AVLNode* node, MusicPlayer key) {
        if (node == NULL) {
            return new AVLNode(key);
        }
        if (key.title < node->key.title) {
            node->left = insert(node->left, key);
        } 
		else if (key.title > node->key.title) {
            node->right = insert(node->right, key);
        } 
		else {
            return node;
        }
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        int balance = getBalance(node);

        if (balance > 1 && key.title < node->left->key.title) {
            return rightRotate(node);
        }
        if (balance < -1 && key.title > node->right->key.title) {
            return leftRotate(node);
        }
        if (balance > 1 && key.title > node->left->key.title) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key.title < node->right->key.title) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void insert(MusicPlayer key) {
        root = insert(root, key);
    }
    
    
	void showsongs(AVLNode *node, string data, string filter, int &flag) {
    	if (node != NULL) {
    	    if (data == "title") {
    	        cout << "Title: " << node->key.title << endl;
    	    } 
    	    else if (data == "artist") {
    	        if (node->key.artist == filter) {
    	            cout << "Music: " << node->key.title << endl;
    	            flag++;
    	        }
    	    } 
    	    else if (data == "album") {
    	        if (node->key.album == filter) {
    	            cout << "Music: " << node->key.title << endl;
    	            flag++;
    	        }
    	    } 
    	    else if (data == "genre") {
    	        if (node->key.genre == filter) {
    	            cout << "Music: " << node->key.title << endl;
    	            flag++;
    	        }
    	    } 
    	    else if (data == "year") {
    	        if (node->key.year == filter) {
    	            cout << "Music: " << node->key.title << endl;
    	            flag++;
    	        }
   	     	} 
   	     	else {
         	   	cout << "Invalid choice" << endl;
        	}	

        	showsongs(node->left, data, filter, flag);
        	showsongs(node->right, data, filter, flag);
    		}
		}
	
	void specificMusicFilter(){
		string choice;	
		cout << "================================================" << endl;
		cout << "Press 1 to show music by title" << endl;
		cout << "Press 2 to show music by artist" << endl;
		cout << "Press 3 to show music by album" << endl;
		cout << "Press 4 to show music by genre" << endl;
		cout << "Press 5 to show music by year" << endl;
		cout << "Press 0 to go back" << endl;
		cout << "================================================" << endl;
		cin >> choice;
		int flag=0;
		if(choice == "1"){
			showsongs(root, "title" , "title" , flag);
		}
		else if(choice == "2"){
			cout << "Enter artist name :" ;
			cin >> choice;
			showsongs(root , "artist" ,choice ,flag);
		}
		else if(choice == "3"){
			cout << "Enter album name :" ;
			cin >> choice;
			showsongs(root , "album" , choice ,flag);
		}
		else if(choice == "4"){
			cout << "Enter genre :" ;
			cin >> choice;
			showsongs(root , "genre" , choice ,flag);
		}
		else if(choice == "5"){
			cout << "Enter year :" ;
			cin >> choice;
			showsongs(root , "year" , choice ,flag);
		}
		else if(choice=="0"){
			return;
		}
		else{
			cout << "Invalid choice" <<endl;
		}
		if(flag==0){
			cout << "Not exists" << endl;
		}
	}
    void inorder() {
        inorderTraversal(root);
    }
	void showMusicDetails(AVLNode* node){
		if (node != NULL) {
            	cout << "==================" << endl;
            	cout << "Title: " << node->key.title << endl;
            	cout << "Artist: " << node->key.artist << endl;
            	cout << "Album: " << node->key.album << endl;
            	cout << "Genre: " << node->key.genre << endl;
            	cout << "Year: " << node->key.year << endl;
            	cout << "Duration: " << node->key.duration << endl;
				cout << "==================" << endl << endl;
            	return ;
        }
	}
	void toLower(string &strs) {
		int i=0;
    	char ch=strs[i];
		while(ch!='\0') {
    	    ch = tolower(ch);
    	    strs[i]=ch;
    	    i++;
    	    ch=strs[i];
    	}
	}
	
    void play(AVLNode* node, stack & obj) {
    	system("cls");
	    node->key.playing = true;
	    int hr=0,min=0,sec=0;
	    obj.push(node->key);
	    string music_name = node->key.title + ".wav";
	    int a = PlaySound(TEXT(music_name.c_str()), NULL, SND_FILENAME | SND_ASYNC);
	
    	if (a == 0) {
    	    cout << "Failed to play the sound. Error code: " << GetLastError() << endl;
    	}
		clock_t start_time = clock();
		clock_t current_time = start_time;
	
		bool isPaused = false;
	
		while (true) {
			float duration_run=min+0.01*sec;
		    if ((duration_run) > node->key.duration) { 
		    	PlaySound(NULL, NULL, 0);
		        return;
		    } 
			else {
		        if (GetAsyncKeyState('P') & 0x8000) {
    	        	if (!isPaused) {
    	            	PlaySound(NULL, NULL, 0); //Pause 
    	            	node->key.playing = false;
    	            	isPaused = true;
    	        	}
    	    	}	
	
	        if (isPaused) {
	    	    if (GetAsyncKeyState('R') & 0x8000) {
    		            PlaySound(TEXT(music_name.c_str()), NULL, SND_FILENAME | SND_ASYNC );
    		            node->key.playing = true;
    		            duration_run=0.0;
    		            sec=0;
    		            min=0;
    		            hr=0;
    		            isPaused = false;
   			        }
        		}
	
		        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // esc key ka naam hai VK_ESCAPE
    		        node->key.playing = false;
    	        	PlaySound(NULL, NULL, 0);
    	        	break; // Exit
    	    	}
	
		        current_time = clock();
				if (!isPaused){
	    	    	if ((current_time - start_time) / CLOCKS_PER_SEC >= 1) {
	    	    		system("cls");
	    	    		showMusicDetails(node);
	    	    		cout << "Press 'P' to pause" << endl;
						cout << "Press 'R' to replay" << endl;
						cout << "Press 'esc' key to exit from the song" << endl;
	    	    		cout << endl << endl;
	        		    cout << "\t\t" << hr << " hours : " << min << " minutes : " << sec << " seconds" << endl;
	           		 	sec++;
		        	    if (sec == 60) {
		        	        sec = 0;
    		    	        min++;	
    		            	if (min == 60) {
    		            	    min = 0;
    	    	        	    hr++;
    	    	        	}
    	    	    	}
    	       	 		start_time = current_time;
    	   			}	
				}
    		}
		}
		system("cls");		
	}

    void inorderTraversal(AVLNode* node) {
        if (node != NULL) {
            inorderTraversal(node->left);
            cout << "==================" << endl;
            cout << "Title: " << node->key.title << endl;
            cout << "Artist: " << node->key.artist << endl;
            cout << "Album: " << node->key.album << endl;
            cout << "Genre: " << node->key.genre << endl;
            cout << "Year: " << node->key.year << endl;
            cout << "Duration: " << node->key.duration << endl;
			cout << "==================" << endl << endl;
            
            inorderTraversal(node->right);
        }
    }
    
    AVLNode* search(AVLNode* node, string name) {
    	if (node == NULL) {
    	    cout << "No song named " << name << endl;
    	    return NULL;
    	}
    	if (node->key.title.compare(name) == 0) {
    	    return node;
    	} 
		else {
    	    if (node->key.title.compare(name) > 0) {
   		        return search(node->left, name);
       	 	} 
			else {
        	    return search(node->right, name);
        	}
    	}
	}
	void action(string username,queue *playlist ,stack &history){
		string alias; // for guest mode
		if(username=="none"){
			cout << "You are in guest mode please Enter your name : " << endl;
			cin >> alias;
		}
	    fstream inp("m.txt", ios::in | ios::out);
	    string year;
	    float duration;
	    string title, artist, album, genre;
	    if (!inp.is_open()) {
	        cout << "Error in opening the file!" << endl;
	    } 
		else {
			int i=0;
    	    while (inp >> year >> title >> artist >> album >> genre >> duration ) {
    	    	toLower(title);
	            insert(MusicPlayer(year, title, artist, album, genre, duration));
	            i++;
    		}
    		cout << "Total musics are " << i << endl << endl;
    	inp.close();
		}
		if(username!="none"){
			string f_name_p=username+"P.txt";  // Playlist file name
			fstream upl(f_name_p.c_str(), ios::in | ios::out); //UserPlayListData
	    	if(!upl.is_open()){
	        	cout << "Error in opening the file!" << endl;
	    	}	 
			else {
				string playlistname;
				int i=0;
    	    	while (upl >> playlistname){ // get playlist name
    	    		if(playlistname == "none"){
    	    			break;
					}
					playlist[i].name=playlistname;
    	    		string f_user_p=username+playlistname+"P.txt"; //list of files
    	    		fstream upls(f_user_p.c_str(), ios::in | ios::out); //UserPlayListData song list
    	    		while (upls >> title){
    	    			AVLNode *temp = search(root,title);
    	    			if(temp!=NULL){
    	    				playlist[i].enqueue(temp->key);
						}
					}
					i++; // iterator of playlist
					upls.close();
    			}
    		}
    		upl.close();
    		string f_name_h=username+"H.txt"; // History file name
    		fstream uhl(f_name_h.c_str(), ios::in | ios::out); //UserHistoryData
	    	if (!uhl.is_open()) {
	        	cout << "Error in opening the file!" << endl;
	    	}	 
			else {
				stack temp_s; // for getting in order of lifo
    	    	while (uhl >> title) {
    	    		AVLNode *temp = search(root,title);
    	    		if(temp!=NULL){
	    	    		temp_s.push(temp->key);
    				}	
				}
				while(!temp_s.isempty()){
					history.push(temp_s.peek());
					temp_s.pop();
				}
			}
			uhl.close();
		}
		string ch;
		while(1){
			cout << endl;
			cout << "+-------------------------------------+" << endl;
			cout << "|      Music Player - Main Menu       |" << endl;
			cout << "|                                     |" << endl;
			cout << "|-------------------------------------|" << endl;
			cout << "|   1. Add song to playlist           |" << endl;
			cout << "|   2. Show all songs with details    |" << endl;
			cout << "|   3. Filter songs by criteria       |" << endl;
			cout << "|   4. Run playlist                   |" << endl;
			cout << "|   5. Show playlist                  |" << endl;
			cout << "|   6. Remove song from playlist      |" << endl;
			cout << "|   7. Show playback history          |" << endl;
			cout << "|   8. Search and play song           |" << endl;
			cout << "|   9. Create new playlist            |" << endl;
			cout << "|  10. Delete playlist by name        |" << endl;
			cout << "|   E. Log out                        |" << endl;
			cout << "|                                     |" << endl;
			cout << "+-------------------------------------+" << endl << endl;
			cin >> ch;
			if(ch=="1"){
				bool flag=false;
				string name;
				cout << "Enter playlist name " << endl;
				cin >> name;
				for(int i=0;i<10;i++){
					if(playlist[i].name==name){
						flag=true;
						cout << "Enter song name " << endl;
						cin >> name;
						AVLNode *node =search(root , name);
						if(node!=NULL){
							if(playlist[i].checkPlaylist(node->key.title)){
								cout << "Already exists" << endl;	
							}
							else{
								playlist[i].enqueue(node->key);
								cout << "Successfully Added " << endl;			
							}
						}
						cout << endl;
						break;
					}
				}
				if(flag == false){
					cout << "no playlist found by this name " << endl;
					cout << "Please create playlist first"  << endl << endl << endl;
				}
			}
			else if(ch=="2"){
				cout << endl;
				inorder();
			}
			else if(ch=="3"){
				specificMusicFilter();
				cout << endl;
			}
			else if(ch=="4"){
				string name;
				bool flag=false;
				cout << "Enter Playlist name which you want to run " << endl;
				cin >> name;
				for(int i=0;i<10;i++){
					if(name==playlist[i].name){
						flag=true;
						if(!playlist[i].isempty()){
							while(1){
								MusicPlayer temp= playlist[i].dequeue();
								playlist[i].enqueue(temp);
								AVLNode * node= search(root , temp.title);
								play(node,history); // line 223
								cout << "If you want to pause the playlist to press 'P'. If not Press any other key "<< endl;
								cin >> ch;
								if(ch=="p" || ch=="P"){
									break;
									break;
								}
								cout << endl;		
							}
						}
						else{
							cout << "playlist is empty " << endl;
						}
					}
				}
				if(flag==false){
					cout << "No playlist name " << name << endl ;
				}
			}
			else if(ch=="5"){
				bool flag = false;  // empty sign for printing
				for(int i=0;i<10;i++){
					if(playlist[i].name!="none"){
						playlist[i].display();
						flag=true;
					}
				}
				if(flag==false){
					cout << "No playlist exists" << endl  << endl;
				}
			}
			else if(ch=="6"){
				string name;
				bool flag=false;
				cout << "Enter Playlist name in which you want to delete a song " << endl;
				cin >> name;
				for(int i=0;i<10;i++){
					if(name==playlist[i].name){
						playlist[i].display();
						flag=true;
						string MusicName;
						cout << "Enter Music name that you want to delete " << endl;
						cin >> MusicName;
						if(playlist[i].checkPlaylist(MusicName)){
							playlist[i].RemoveMusicFromPlaylist(MusicName);
						}
						else{
							cout << "Music not exists in playlist " << endl;
						}
					}
				}
				if(flag==false){
					cout << "No Playlist name " << name  << endl << endl;
				}
			}
			else if(ch=="7"){
				if(history.isempty()){
					cout << "No History found" << endl;
				}
				else{
					history.display();
				}
			}
			else if(ch=="8"){
				string MusicName;
				cout << "Enter Music name that you want to play " << endl;
				cin >> MusicName;
				toLower(MusicName);
				AVLNode *node = search(root,MusicName);
				if(node!=NULL){
					play(node,history);   // line 223
				}				
			}
			else if(ch=="9"){
				string name;
				if(playlist[9].name!="none"){
					cout << "You only have capacity to build 10 playlists " << endl;
				}
				else{
					cout << "Enter Playlist name : or press 'b' to go back " ;
					cin >> name;
					if(name=="b" || name=="B"){
						system("cls");
					}
					else{
						for(int i=0;i<10;i++){
							if(playlist[i].name==name){
								cout << "Already Exists " << endl << endl;
								break;
 							}
							if(playlist[i].name=="none"){
								playlist[i].name=name;
								string f_user_p=username+playlist[i].name+"P.txt";
    	    					ofstream temp_create; // creating playlist named file
    							temp_create.open(f_user_p.c_str());
								cout << "Playlist created successfully" << endl;
								break;
							}
						}
					}
				}
			}
			else if(ch=="10"){
				string name;
				bool flag=false;
				cout << "Enter Playlist name in which you want to delete" << endl;
				cin >> name;
				for(int i=0;i<10;i++){
					if(name==playlist[i].name){
						flag=true;
						while(!playlist[i].isempty()){
							playlist[i].dequeue();							
						}
						string p_name=username+playlist[i].name+"P.txt";
    					remove(p_name.c_str());
    					cout << p_name  << "DELETED" << endl;
						playlist[i].name="none";
						cout << endl << "Playlist " << name << " deleted successfully "<< endl << endl;
						break;
						}
				}
				if(flag==false){
					cout << "No Playlist name " << name  << endl << endl;
				}
				
					
			}
			else if(ch=="e" || ch=="E"){
				ch=3;
				cout << endl;
				if(username!="none"){
					string f_name_h = username+"H.txt"; // History file name
					fstream uhl(f_name_h.c_str(), ios::in | ios::out); //UserHistoryData
	    			if (!uhl.is_open()){
	    	    		cout << "Error in opening the file!" << endl;
	    			}	 
					else {
						while (!history.isempty()) {
        					uhl << history.peek().title << endl ;
        					history.pop();
    					}
					}
					uhl.close();
					string f_name_p = username+"P.txt"; // Playlist file name
					fstream upl(f_name_p.c_str(), ios::in | ios::out); //UserPlayListData
	    			if (!upl.is_open()) {
	    	    		cout << "Error in opening the file!" << endl;
	    			}	 
					else {
    	    			for(int i=0;i<10;i++){
    	    				upl << playlist[i].name << endl ;
							if(playlist[i].name=="none"){
    	    					continue;
							}
    	    				
    	    				string f_user_p=username+playlist[i].name+"P.txt";
    	    				fstream upls(f_user_p.c_str(), ios::in | ios::out); //UserPlayListData song list
    	    				while(!playlist[i].isempty()){
 		   	    				upls << playlist[i].peek().title << endl ;
    	    					playlist[i].dequeue();
							}
							upls.close();
    	    			}
					}
					upl.close();
				}
				cout << endl;
				cout << "Good bye " << alias << endl;
				cout << "Thankyou for using " << ch << endl;
				break;
			}
			else{
				cout << "Invalid Choice " << endl;
			}
		}
	}
};


int main() {
    AllMusic data;
    queue *Playlist;
    stack History;
    user person;
    Playlist=new queue[10];
    for(int i=0;i<10;i++){
    	Playlist[i].name="none";
	}
	
	string choice ;
	
	int check;
	while(choice!="0"){
		cout << endl << endl;
		cout << "Made by:" << endl;
		cout << "Muhammad Hasnain (22k-5099)" << endl;
		cout << "Ali Masood (22k-5127)" << endl;
		cout << "Syed Shees Ali (22k-5047)" << endl;
		cout << "===============================================" << endl;
		cout << "\t\t\tMusic Player \t\t\t" << endl;
		cout << "Press 1 to sign up " << endl;
		cout << "Press 2 to log in" << endl ;
		cout << "Press 3 to if you forget your password " << endl;
		cout << "Press 4 if you want to use as guest " << endl;
		cout << "Press 5 to see about " << endl;
		cout << "Press 0 to Exit " << endl ;
		cout << "===============================================" << endl;
		cin >> choice;
		
		if(choice=="1"){
			person.sign_up();
		}
		else if(choice=="2"){
			string username=person.log_in();
			if(username!="none"){
				system("cls");
				data.action(username,Playlist,History);
			}
		}	
		else if(choice=="3"){
			person.forget();
		}
		else if(choice=="4"){
			data.action("none",Playlist,History);
		}
		else if(choice=="5"){
			ifstream file("about.txt");
			char ch;
			while (file.get(ch)) {
        		cout << ch;
    		}
			file.close(); 

		}
		else if(choice=="0"){
			cout << "Thankyou " ;
		}
		else{
			cout << "Invalid Choice " << endl ;
			}
		}
		for (int i = 0; i < 10; ++i) {
    		while (!Playlist[i].isempty()) {
        		Playlist[i].dequeue();
    		}
		}
		delete [] Playlist;
	}
		
    


