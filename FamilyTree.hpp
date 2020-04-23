#include <iostream>
#include <string>
using namespace std;
namespace family
{
	class Tree
	{
	public:
	
	  	string name , relate;
	   	Tree *father , *mother , *self;

        // constructor
		Tree(string n): 
				name(n),
				relate("me"),
				father(nullptr),
				mother(nullptr){};


		Tree& addFather(string name, string father_name);
		Tree& addMother(string name, string mother_name);
		string relation(string family_member_name);
		string find(string family_role);	//returns name
		void display();	//displays from root above
		void remove(string family_member_name);	//remove root+all parents//find family_member_name node and remove it's child's node
    };
};
