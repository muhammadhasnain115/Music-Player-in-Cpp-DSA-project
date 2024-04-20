
#include "hist.h"
class QueNode{
	public:
		MusicPlayer data;
		string name;
		QueNode * next;
		QueNode(){
			next=NULL;
			name="none";
		}
		
		QueNode(MusicPlayer d){
			data=d;
			next=NULL;
		}
};
class queue{
		QueNode * front ;
		QueNode * rear ;
	public:
		string name;
		int size;
		queue(){
			front=NULL;
			rear=NULL;
			size=0;
		}
		
		bool isempty(){
			if(front==NULL){
				return true;
			}
			return false;
		}
		
		MusicPlayer peek(){
			return front->data;
		}
		
		void enqueue(MusicPlayer d){
			QueNode * temp=new QueNode(d);
			if(front==NULL){
				size++;
				front = temp;
				rear = temp;
			}
			else{
				size++;
				rear->next=temp;
				rear=temp;
			}
		}
		
		bool checkPlaylist(string name){
			queue tempQueue;
			bool flag=false;
			while(!isempty()){
				MusicPlayer temp= dequeue();
				if(temp.title==name){
					flag=true;
				}
				tempQueue.enqueue(temp);
			}
			while(!tempQueue.isempty()){
				MusicPlayer temp= tempQueue.dequeue(); 
				enqueue(temp);
			}
			if(flag==true){
				return true;
			}
			return false;
		}
		
		MusicPlayer dequeue(){
			if(isempty()){
				cout << "No songs in Playlists " << endl;
			}
			else{
				MusicPlayer data=peek();
				QueNode * temp = front ; 
				front=front->next;
				delete temp;
				size--;
				return data;
			}
		}
		
		void display(){
			cout <<endl << "===============================" << endl;
			cout << endl << "        Playlist Details " << endl << endl;
			cout << "Playlist name is " << name << "                         ";
			if(size==0){
				cout << "No songs in Playlist" << endl;
				return ;
			}
			queue tempQueue;
			cout << "Total songs in Playlist are " << size << endl << endl;
			cout << "Songs list " << endl << endl;
			while(!isempty()){
				MusicPlayer temp= dequeue();
				cout << temp.title << endl; 
				tempQueue.enqueue(temp);
			}
			while(!tempQueue.isempty()){
				MusicPlayer temp= tempQueue.dequeue(); 
				enqueue(temp);
			}
			cout << endl;
			cout << "===============================" << endl;
		}
		void RemoveMusicFromPlaylist(string name){
			queue tempQueue;
			while(!isempty()){
				MusicPlayer temp= dequeue();
				if(temp.title==name){
					continue;
				}
				tempQueue.enqueue(temp);
			}
			while(!tempQueue.isempty()){
				MusicPlayer temp= tempQueue.dequeue(); 
				enqueue(temp);
			}
		}
};

