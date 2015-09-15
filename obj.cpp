#include <iostream>
 #include "voyage.h"
using namespace std;
 
void Obj::setNode_select(int n)
{
    node_select = n;
}
 
int Obj::getNode_select(void)
{
    return node_select;
}


 
void Obj::setEdge_select(int n)
{
    edge_select = n;
}
 
int Obj::getEdge_select(void)
{
    return edge_select;
}

void Obj::setNb_Edge(int n)
{
    nbedge = n;
}
 
int Obj::getNb_Edge(void)
{
    return nbedge;
}

void Obj::setNb_Node(int n)
{
    nbnode = n;
}
 
int Obj::getNb_Node(void)
{
    return nbnode;
}


// Main function for the program
/*
int main( )
{
   Obj variab;
 
   // set line length
   variab.setnode_select(6.0); 
   cout << "Length of line : " << variab.getnode_select() <<endl;
 
   return 0;
}
*/
