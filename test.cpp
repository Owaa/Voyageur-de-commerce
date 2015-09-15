
#include <iostream>
#include <lemon/list_graph.h>
#include <fstream>
#include <queue>          // std::queue
#include <lemon/lgf_writer.h>
#include <set>
#include <vector>
#include <time.h>       /* time */
#include <cmath>        // std::pow
#include <valarray>     // std::valarray, std::pow

using namespace lemon;
using namespace std;


int main(int argc, char **argv) 
{
		
	char aa[1];
	
	
	ListGraph g;
	int i = 0;
	while(i != 2)
	{
		ListGraph::Node aa = g.addNode();
		
		aa[0] = 'b';
	}
//	ListGraph::Node a = g.addNode();
	ListGraph::Node b = g.addNode();
	ListGraph::Node c = g.addNode();	

	ListGraph::Edge ac = g.addEdge(a, c);
	
  	  
  for (ListGraph::EdgeIt a(g ); a!= INVALID; ++a)	  
    {
      std::cout << "edge id  = " << g.id(a) <<"     Go  "<<g.id(g.v(a))  <<   "--->"   << g.id(g.u(a)) << std::endl;
    }
		
		
}