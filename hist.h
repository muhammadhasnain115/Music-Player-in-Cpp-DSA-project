#include "mp.h"
class StackNode{
	public:
		MusicPlayer data;
		StackNode * next;
		StackNode(){
			next=NULL;
		}
		
		StackNode(MusicPlayer d){
			data=d;
			next=NULL;
		}
};

class stack{
	StackNode *top;
	
	public:
		stack(){
			top=NULL;
		}
		void push(MusicPlayer d)
		{
			StackNode * temp=new StackNode(d);
			if(top==NULL){
				top=temp;
			}
			else{
				temp->next=top;
				top=temp;
				top->data;
			}
		}
		bool isempty(){
			if(top==NULL){
				return true;
			}
			return false;
		}
		MusicPlayer peek(){
				return top->data;
		}
		MusicPlayer pop(){
			if(isempty()){
				cout << "Stack is empty " << endl;
			}
			else{
				MusicPlayer data=peek();
				StackNode * temp=top;
				top=top->next;
				delete temp;
				return data;
			}
		}
		void display(){
			cout << endl << "          History " <<  endl;
			cout << "===============================" << endl;
			stack tempStack;
			while(!isempty()){
				MusicPlayer temp=pop();
				cout << temp.title << endl;
				tempStack.push(temp); 
			}
			while(!tempStack.isempty()){
				MusicPlayer temp=tempStack.pop();
				push(temp); 
			}
			cout << endl;
			cout << "===============================" << endl;
		}
};
