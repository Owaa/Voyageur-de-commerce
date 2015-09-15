

#ifndef __VOYAGE_H__
#define __VOYAGE_H__


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

extern ListGraph g;

extern ListGraph::EdgeMap <int> map_passage;
extern ListGraph::EdgeMap <int> map_distance;
extern ListGraph::EdgeMap <float> map_pheromone;
extern ListGraph::NodeMap <int> map_fourmie;
extern ListGraph::NodeMap <int> map_fourmie_apres;
extern ListGraph::EdgeMap <float> map_pourcentage;

class Obj
{
   public:
      void setNode_select(int n);
      int getNode_select(void);
      void setEdge_select(int n);
      int getEdge_select(void);
      void setNb_Edge(int n);
      int getNb_Edge(void);
      void setNb_Node(int n);
      int getNb_Node(void);
        
   private:
      int node_select;
      int edge_select;
      int nbedge;
      int nbnode;

      
    
  
};


class Fourmi
{
   public:
      int view_city(int city);
      void insert_city(int city);
      void clean_city(void);
      int get_city();
      std::vector<int> fourmi_view;
      int distance;
};



int compare(float a , float b);
void init(ListGraph &g);
float proba (float ph,int dist);
int choix_chemin (ListGraph &g, ListGraph::Node node,std::vector<float> pourcentage );
void voyage();
void initialiser_fourmi(void);
#endif
