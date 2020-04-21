#include <iostream>
using namespace std;
namespace family
{

	enum gender
	{
		SELF = 0,
		FATHER = 1,
		MOTHER = 2
	};

	struct tree_node
	{
		string name;
		tree_node * mother;
		tree_node * father;
		int depth;
		gender family_role;

		tree_node(int depth, gender family_role);
	};

	typedef struct tree_node * node;

	class Tree
	{
		node root;

		public:
		Tree(string name);
		Tree addFather(string name, string father_name);
		Tree addMother(string name, string mother_name);
		string relation(string family_member_name);
		string find(string family_role);	//returns name
		void display();	//displays from root above
		void remove(string family_member_name);	//remove root+all parents//find family_member_name node and remove it's child's node
	};

}
