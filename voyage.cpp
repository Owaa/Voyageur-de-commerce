#include <iostream>
#include <lemon/list_graph.h>
#include <string> 
#include <fstream>
#include <queue>          // std::queue
#include <lemon/lgf_writer.h>
#include <set>
#include <vector>
#include <time.h>       /* time */
#include <cmath>        // std::pow
#include <valarray>     // std::valarray, std::pow
#include "voyage.h"     // std::valarray, std::pow

ListGraph g;

#define NB_NODE 100
//#define NB_EDGE 15
ListGraph::EdgeMap <int> map_passage(g);
ListGraph::EdgeMap <int> map_distance(g);
ListGraph::EdgeMap <float> map_pheromone(g);
ListGraph::NodeMap <int> map_fourmie(g);
ListGraph::NodeMap <int> map_fourmie_apres(g);
ListGraph::EdgeMap <float> map_pourcentage(g);


int compare(float a , float b)  
{
  if(a  < b)
    return 1;
  else
    return 0;
}

void init(ListGraph &g){
  
  
  for (ListGraph::NodeIt node(g); node != INVALID; ++node){ 
    map_fourmie[node] = 2;
    map_fourmie_apres[node] = 2;
  }
  for (ListGraph::EdgeIt a(g ); a!= INVALID; ++a)	  
    {
     
      map_pheromone[a] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/1));
      map_passage[a] = 0;
     

    }



  
   
}
float proba (float ph,int dist){

 if(dist == 0)
   dist =1;

 return  ph/(std::pow (dist,7)) ;
 
}

int choix_chemin (ListGraph &g, ListGraph::Node node,std::vector<float> pourcentage ){
  int i;
  float acc = pourcentage[0];
  float random =  static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100));


  
  for (i = 0; i<pourcentage.size(); ++i){

    if(random <= acc){
      for (ListGraph::EdgeIt ar(g) ; ar!= INVALID; ++ar)	  
	{
	  if(pourcentage[i] ==  map_pourcentage[ar] )	  {


	     
	    return g.id(ar);	    
	  }
	}
      
    }
    else
      acc+= pourcentage[i+1];
	 
  }
 
  
  for (ListGraph::EdgeIt ar(g) ; ar!= INVALID; ++ar)	  
    {
      if(pourcentage[pourcentage.size()-1] ==  map_pourcentage[ar] )	  {

	return g.id(ar);	    
      }
      }
  
}



void voyage(){


  int i = 0 ,j,z;
  int nb_edge = 0;

  for (i= NB_NODE -1; i >=1 ; i--){

    nb_edge += i;

  }
  
  ListGraph::Node node_tab[NB_NODE];
  ListGraph::Edge edge_tab[nb_edge];
    
  for(i = 0; i< NB_NODE; i++){
    node_tab[i] = g.addNode();
  }

  for (ListGraph::NodeIt node(g); node != INVALID; ++node){ 
    printf("g.id( %d )", g.id(node));
  }

    
  for(z = 0 ,i = 0 , j= 1; z<nb_edge; z++){ 
    printf("g.id( %d   %d)\n", g.id(node_tab[i]) ,  g.id(node_tab[j]));

    edge_tab[z] = g.addEdge(node_tab[i] ,node_tab[j]);
    j++;

    if(j%NB_NODE== 0){	 
      i++;
      j=i+1;
    }
  }
  
  
   init(g);
	  
  for (ListGraph::EdgeIt a(g ); a!= INVALID; ++a)	  
    {
      std::cout << "edge id  = " << g.id(a) <<"     Go  "<<g.id(g.v(a))  <<   "--->" << g.id(g.u(a)) <<" distance = " <<  map_distance[a]<<" passage " <<map_passage[a] << std::endl;
      
    }
  
  




}
