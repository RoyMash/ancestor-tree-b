#include "FamilyTree.hpp"
#include <iostream>
#include <exception>
using namespace std;
using namespace family;

Tree* GetNewNode(Tree *Tree_P, string child_name)
{
    if (Tree_P->name == child_name) return Tree_P;

    if (Tree_P->father)
    {
        Tree *requested_root = GetNewNode(Tree_P->father, child_name);
        if (requested_root != nullptr) return requested_root;
    }

    if (Tree_P->mother)
    {
        Tree *requested_root = GetNewNode(Tree_P->mother, child_name);
        if (requested_root) return requested_root;
    }

    return nullptr;
}

Tree &Tree::addFather(string name, string father_name)
{
    Tree *Tree_P = GetNewNode(this, name);
    if (Tree_P)
    {
        if (!Tree_P->father)
        {
            Tree_P->father = new Tree(father_name);
            Tree_P->father->self = Tree_P;
            //if's for the relation
            if (Tree_P->relate == "me") Tree_P->father->relate = "father";
            else if (Tree_P->relate == "father" || Tree_P->relate == "mother") Tree_P->father->relate = "grandfather";
            else if (Tree_P->relate == "grandfather" || Tree_P->relate == "grandmother") Tree_P->father->relate = "great-grandfather";
            else
            {
                string temp = "great-" + Tree_P->relate;
                for (int j = 0; j < 6; j++) temp.pop_back();
                temp += "father";
                Tree_P->father->relate = temp;
            }
            Tree *ans = this;
            return * ans;
        }
        else
        {
            throw runtime_error(name + " already has a father !");
        }
    }
    else
    {
        throw runtime_error(name + " is not in the tree");
    }
}

Tree &Tree::addMother(string name, string mother_name)
{
    Tree *Tree_P = GetNewNode(this, name);
    if (Tree_P)
    {
        if (!Tree_P->mother)
        {
            Tree_P->mother = new Tree(mother_name);
            Tree_P->mother->self = Tree_P;
            //if's for the relation
            if (Tree_P->relate == "me") Tree_P->mother->relate = "mother";
            else if (Tree_P->relate == "mother" || Tree_P->relate == "father") Tree_P->mother->relate = "grandmother";
            else if (Tree_P->relate == "grandmother" || Tree_P->relate == "grandfather") Tree_P->mother->relate = "great-grandmother";
            else
            {
                string temp = "great-" + Tree_P->relate;
                for (int j = 0; j < 6; j++) temp.pop_back();
                temp += "mother";
                Tree_P->mother->relate = temp;
            }
            Tree *ans = this;
            return * ans;
        }
        else
        {
            throw runtime_error(name + " already has a mother !");
        }
    }
    else
    {
        throw runtime_error(name + " is not in the tree");
    }
}

string Tree::relation(string family_member_name)
{
    Tree *Tree_P = GetNewNode(this, family_member_name);
    if (Tree_P)
        return Tree_P->relate;
    return "unrelated";
}

void beautyPrint(Tree *Tree_P, int space)
{
    if (!Tree_P) return;
    space += 6;	// Increase distance between levels

    beautyPrint(Tree_P->father, space);
    cout << endl;
    for (int i = 10; i < space; i++)
        cout << " ";
    cout << Tree_P->name << "\n";
    beautyPrint(Tree_P->mother, space);	// Process mother node
}

void Tree::display()
{
    //
    beautyPrint(this, 0);
}

Tree* findRecursive(Tree *Tree_P, string str)
{
    if (Tree_P->relate == str)
    {
        return Tree_P;
    }
    if (Tree_P->father)
    {
        Tree *ans = findRecursive(Tree_P->father, str);
        if (ans != nullptr) return ans;
    }
    if (Tree_P->mother)
    {
        Tree *ans = findRecursive(Tree_P->mother, str);
        if (ans) return ans;
    }
    return nullptr;
}

string Tree::find(string family_role)
{
    Tree *Tree_P = findRecursive(this, family_role);
    if (Tree_P)
    {
        return Tree_P->name;
    }
    else
    {
        throw runtime_error("The tree cannot handle the '" + family_role + "' relation");
    }
}

void Tree::remove(string family_member_name)
{
    Tree *Tree_P = GetNewNode(this, family_member_name);
    if (Tree_P == this)
    {
        throw runtime_error("Can't remove the root of the tree (aka -> me");
    }
    if (Tree_P)
    {
        if (Tree_P->self->mother == Tree_P)
        {
            Tree_P->self->mother = nullptr;
        }
        if (Tree_P->self->father == Tree_P)
        {
            Tree_P->self->father = nullptr;
        }
        delete Tree_P;
    }
    else
    {
        throw runtime_error(family_member_name + " is not in the tree");
    }
}