
//rabiaaydemir_rabia_aydemir_23492
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct node {
	int laptime;
	string drivername;
	node *next; 
	int lap;
	node::node ()
	{}

	node::node (string dname,const int & s, node * link,int a)
		: drivername(dname),laptime(s), next (link),lap (a)
	{}
};

/* Begin: code taken from linkedList.cpp and updating */ 
int SearchList(node * &head, string searchname,node* & ptr3,int time)
{ /*node* ptr3= head;*/
	
	int isfound =0;
	while (ptr3 != NULL)  // ptr3 yap head;
	{
		if(ptr3->drivername == searchname ) //If the node with the given drivername is found
		{   
			if(ptr3->laptime< time)
				return 1;
			
			else
				return 2;
			
				
		}
		ptr3 = ptr3->next;
	}
	
	//If the code proceeds from here, it means that the whole list is traversed 
	//and a node with drivername== searchname could not be found. 
	return isfound; 
}
/* End: code taken from linkedList.cpp and updating */ 

void Printing (node*head,string name,int time)
{ 
	int ctr=1;
	while(head!=NULL)
	{

	  if(head->drivername==name)
		{
		 cout<< name << "current personal best is" << " " <<head->laptime <<"current position"<< " " << ctr <<endl; 
		}
		head= head->next;
		ctr++;
	}


}

/* Begin: code taken from 2.2-pointers-linkedLists.ppt */ 
void DeleteOneNode (node * toBeDeleted, node * & head)
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
	node*ptr=head;
	
	     ptr= head;
	while (ptr->next!=NULL && ptr->next != toBeDeleted)
		ptr = ptr->next;
		//after while, ptr points to the node just before toBeDeleted
		
		//connect the previous node to the next node and delete
	ptr->next = toBeDeleted->next;
	    //delete &toBeDeleted;
		delete toBeDeleted;
	
	
}
/* End: code taken from 2.2-pointers-linkedLists.ppt */

node * deleteHead(node * toBeDeleted, node * & head)
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
	node*ptr=head;
	if (toBeDeleted == head)  //if the node to be deleted is the first node
	{    // head =new node ( head->next->drivername, head->next->laptime,head->next->next,head->next->lap);
			head = ptr->next;
			ptr = toBeDeleted;
		delete ptr;
		return head;
		
	}
}

/* Begin: code taken from ptrfunc.cpp and updating */ 
node * AddInOrder(node * head, string driver, int time, int&a)
// pre: list is sorted
// post: add newkey to list, keep list sorted, return head of new list with newkey in it
{
    node *  ptr = head;   // loop variable

    // if new node should be first, handle this case and return  
    // in this case, we return the address of new node since it is new head  
	if (head == NULL || time <= head->laptime)        
    {   
		node * temp = new node; //node to be inserted 
		temp -> drivername= driver;
		temp->laptime = time;
		temp->lap = a;
	
		temp->next = head; //connect the rest
		return temp;
		//return new node(head, driver, time);   
    }
	node * ptr_1 = ptr;
    // check node one ahead so we don't pass!
    while (ptr->next != NULL && ptr->next->laptime <= time)
    {   ptr_1 = ptr;
		ptr = ptr->next;
    } // postcondition: new node to be inserted just after the node that ptr points
	if(ptr->lap < a && ptr ->laptime == time)
	{
    //now insert node with newkey after where ptr points to
		//if(ptr->next != NULL && ptr->laptime == time)
		//ptr = ptr->next;
	node * temp = new node;  //node to be inserted
	temp->drivername = driver;
	temp->laptime = time;
	temp->lap = a;
	temp->next = ptr->next; //connect the rest
	ptr->next = temp;
	}else if (ptr->lap > a&& ptr ->laptime == time){
		node * temp = new node;  //node to be inserted
	temp->drivername = driver;
	temp->laptime = time;
	temp->lap = a;
	temp->next = ptr_1->next; //connect the rest
	ptr_1->next = temp;
	}else{
	node * temp = new node;  //node to be inserted
	temp->drivername = driver;
	temp->laptime = time;
	temp->lap = a;
	temp->next = ptr->next; //connect the rest
	ptr->next = temp;
	}
    //ptr->next = new node(newkey,ptr->next);   //alternative to prev. 4 lines

	
    return head;
}
/* End: code taken from ptrfunc.cpp and updating */ 

/* Begin: code taken from linkedList.cpp */ 
void ClearList(node *head)
{
	node *ptr;
	while(head!=NULL)
	{
		ptr=head;
		head=head->next;
		delete ptr;
	}
}
/* End: code taken from linkedList.cpp */

int main()	
{ int g_counter=0;
	ifstream inputtxt;
	string txtname;
	cout << "Please enter a file name." <<endl;
	do
	{
		cin >> txtname;
		inputtxt.open(txtname);
		if (inputtxt.fail())
			cout <<"Unable to open file" <<txtname << endl;
		cout << "Please enter a different file name. " <<endl;
	}while (!inputtxt.is_open());

	cout << "Successfully opened file" << txtname<< endl;
	cout << endl;
	cout << "###############################" <<endl;
	cout << "Qualifying Laps: " << endl;
	cout << "###############################" << endl;
	
	
	node* head=NULL;
	
	string line;
	while (getline(inputtxt,line))
	{
		istringstream ss(line);
		string driver;
		int time;
		ss >> driver>> time;
		cout <<driver<<"completed the lap in" << time <<  "milliseconds" <<endl; 
		node* ptr5=head;
		node *ptr3=head;
		node* ptr4=head;

		int isFound;
		isFound=SearchList(ptr5,driver,ptr3,time);   
		if(isFound==0)                                 
		{                                                 //if isfound is 0, the program can not find the same driver name.
			head=AddInOrder(head,driver,time,g_counter);
			Printing (head,driver, time);
		}                                            
		else if (isFound==1)                              //if isfound is 1, the program can find the same driver name
		{                                                 //we compare the laptime in the same driver names and if the new one is bigger than the previous one
			Printing(head,driver, time);                  // we dont add that node inside the list.
		}                                           
		                                             
		else if (isFound==2)                               //if isfound is 2, the new node which is the same driver name
		{  
			if(head == ptr3)	
			{
				
				head = deleteHead(ptr3,ptr4);
			}
			else
			{	
				DeleteOneNode (ptr3,ptr4);
			head=AddInOrder(head,driver,time,g_counter);
			}
			Printing(head,driver, time);
		}
		
		
	
		
	}

	cout<<endl;
	cout <<"###############################"<<endl;
	cout <<"Results:"<<endl;
	cout <<"###############################"<<endl;

	int counter = 0;
	
	while (head != NULL)             //its printing results
		{ counter++;
			cout <<counter<<"." <<" "<< head->drivername << " " << head -> laptime << endl;
			head=head->next;
			
		}
	ClearList(head);


	return 0;
}


