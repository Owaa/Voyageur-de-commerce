#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <time.h>
#include <unistd.h>
#include "voyage.h"
#include <string.h>
/*

 */

int dejavu = 0;
int loop = 0;

int bool_sleep = 0;
int depart=0,arrive=1;
int ibest = 0;
int ibestbest = 0;
int best[1000];
int boolz = 0;
int bestbest[1000];
int bestdist = 5000;
Obj variab;

void output(int x, int y,int z, char *string);
void *font = GLUT_BITMAP_TIMES_ROMAN_24;
void *fonts[] =
  {
    GLUT_BITMAP_9_BY_15,
    GLUT_BITMAP_TIMES_ROMAN_10,
    GLUT_BITMAP_TIMES_ROMAN_24
  };

float red=1.0f, blue=1.0f, green=1.0f;

// angle of rotation for the camera direction
float angles=0.0;
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z= 50.0f;
float deltaAngle = 0.0f;
int xOrigin = -1;


  Fourmi tab_fourmi[1000];

struct pos{
  float x , y , z;
};


struct pos mapp[100];



void changeSize(int w, int h) {

  if (h == 0)
    h = 1;

  float ratio =  w * 1.0 / h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(45.0f, ratio, 0.1f, 1000.0f);
  glMatrixMode(GL_MODELVIEW);
}





void cube(int i) {
  if(blue < 0)
    blue = 1;
  if(depart == i || arrive == i)
    glColor3f(1,1,0);
  else
    glColor3f(1,1,blue);
  glutSolidCube(0.2);


}

void formi(int i) {
  int nbformi = 0;
  int ii;
  for (ListGraph::NodeIt node(g); node != INVALID; ++node)
    {
    if(i == g.id(node))
      {

	for (ii = 0; ii<  variab.getNb_Node()*2; ii++)
	  {
	    
	  if(tab_fourmi[ii].get_city() == g.id(node) )
	    {
	    nbformi++;
	 
	    }

  
	  }
	break;
      }
    }
  float distance = 0;
  for(int j = 0;j < nbformi;j++,distance += 0.1)
    {
      glPushMatrix();
      glTranslatef( mapp[i].x+distance ,mapp[i].y  ,mapp[i].z);
      glColor3f(1,0,0);  
      glutSolidCube(0.2);
      glPopMatrix();
    }
}

float color(int src , int dest){

  int all_passage = 0;
  int id_edge;
  for (ListGraph::EdgeIt a(g ); a!= INVALID; ++a)	  
    {
      all_passage += map_passage[a];
    }
  for (ListGraph::EdgeIt a(g ); a!= INVALID; ++a)	  
    {
      if( src == g.id(g.u(a)) && dest == g.id(g.v(a)) ){	
	return (float) map_passage[a] /(float)all_passage;
      }
    }
  return 0;
}


void affiche_text()
{

  char buf[255];


  // affiche les nodes
  for (ListGraph::NodeIt node(g); node != INVALID; ++node)
    { 
      if(variab.getNode_select()  == g.id(node))
	{
	  sprintf(buf,"ville n°: %d ",variab.getNode_select());
	  glColor3f(0,1,0);
	  output(-35,0,0,buf);	 
	  break;
	}
      
    }
  // affiche les edges
  for (ListGraph::EdgeIt a(g ); a!= INVALID; ++a)	  
    {
      if(  variab.getEdge_select() == g.id(a))
	{
	  depart = g.id(g.u(a));
	  arrive = g.id(g.v(a));
	  sprintf(buf,"ville n°: %d a n°: %d ",g.id(g.u(a)),g.id(g.v(a)));
	  glColor3f(0,1,0);
	  output(-35,0,6,buf);
	  sprintf(buf,"nb passage : %d ",map_passage[a]);
	  glColor3f(0,1,0);
	  output(-35,0,9,buf);
	  sprintf(buf,"nb pheromone : %f",map_pheromone[a]);
	  glColor3f(0,1,0);
	  output(-35,0,12,buf);
	  sprintf(buf,"distance: %d",map_distance[a]);
	  glColor3f(0,1,0);
	  output(-35,0,15,buf);
	   sprintf(buf,"Best distance: %d",ibestbest);
	  glColor3f(0,1,0);
	  output(-35,0,18,buf);
	  sprintf(buf,"Current distance: %d",bestdist);
	  glColor3f(0,1,0);
	  output(-35,0,21,buf);
	}
      
    }

}
void drawLines(){
  int i , j;
  float r = 1 , g = 1 , b = 1;
  for(i=0;i < variab.getNb_Node();i++)
    {
      glPushMatrix();
      glTranslatef( mapp[i].x ,mapp[i].y  ,mapp[i].z);   
      cube(i);
      glPopMatrix();
      for(j=i+1;j<variab.getNb_Node();j++)
	{
	  glEnable(GL_BLEND) ;
	  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) ;
	  
	  glLineWidth(2.5);
	  r =   color( i, j); // Va calculer le niveau de transparence selon 
	  glColor4f(1,  1, 1,r );

	  glBegin(GL_LINES);
	  glVertex3f(mapp[i].x,mapp[i].y,mapp[i].z);
	  glVertex3f(mapp[j].x,mapp[j].y,mapp[j].z );

	  glDisable(GL_BLEND) ;
	  glEnd();
	}
      //    formi(i);
	
    }
  affiche_text();
  if(bool_sleep == 1)
    usleep(300000);
}


void drawLinesbest(){
  int i , j;
  float r = 1 , g = 1 , b = 1;

  for( i =0  ,j=i+1;j<variab.getNb_Node();j++,i++)
    {
    
      glLineWidth(1.5);
      glColor3f(0,  1, 0 );

      glBegin(GL_LINES);
      glVertex3f(mapp[ bestbest[i]].x,mapp[ bestbest[i] ].y,mapp[ bestbest[i]  ].z);
      glVertex3f(mapp[ bestbest[j] ].x,mapp[ bestbest[j]  ].y,mapp[ bestbest[j]  ].z );

      glDisable(GL_BLEND) ;
      glEnd();
    }
  glLineWidth(1.5);
  glColor3f(0,  1, 0 );

  glBegin(GL_LINES);
  glVertex3f(mapp[ bestbest[i]].x,mapp[ bestbest[i] ].y,mapp[ bestbest[i]  ].z);
  glVertex3f(mapp[ bestbest[0] ].x,mapp[ bestbest[0]  ].y,mapp[ bestbest[0]  ].z );

  glDisable(GL_BLEND) ;
  glEnd();
  
  //  formi(i);
  
    for( i =0  ,j=i+1;j<variab.getNb_Node();j++,i++)
    {
    
      glLineWidth(5.5);
      glColor3f(1,  0, 0 );

      glBegin(GL_LINES);
      glVertex3f(mapp[ best[i]].x,mapp[ best[i] ].y,mapp[ best[i]  ].z);
      glVertex3f(mapp[ best[j] ].x,mapp[ best[j]  ].y,mapp[ best[j]  ].z );

      glDisable(GL_BLEND) ;
      glEnd();
    }

    
      glLineWidth(5.5);
      glColor3f(1,  0, 0 );

      glBegin(GL_LINES);
      glVertex3f(mapp[ best[i]].x,mapp[ best[i] ].y,mapp[ best[i]  ].z);
      glVertex3f(mapp[ best[0] ].x,mapp[ best[0]  ].y,mapp[ best[0]  ].z );

      glDisable(GL_BLEND) ;
      glEnd();
  
  affiche_text();
  if(bool_sleep == 1)
    usleep(300000);
}


void initialiser_fourmi(void)
{
  int i;

  for(i=0 ;i <variab.getNb_Node()*2 ;i++){
    tab_fourmi[i].distance = 0;
    tab_fourmi[i].clean_city();		     
  }
    printf("Test 12 !!!!!\n\n");

  for(i = 0; i < variab.getNb_Node()*2; i+=2){
    tab_fourmi[i].insert_city(i/2);
    tab_fourmi[i+1].insert_city(i/2);
    
  }
  printf("Test ,13 !!!!!\n\n");

  for (ListGraph::NodeIt node(g); node != INVALID; ++node) /* pour cchaque node */
    {
      map_fourmie_apres[node] =2;
      map_fourmie[node] =2;
    }



  
}

void renderScene(void) {
  std::vector<float> myvector;
  std::vector<float> pourcentage;
  float total=0;
  int id_edge_ok = 0;
  int current_fourmi =0;
  int ii;
  // Clear Color and Depth Buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Reset transfomations
  glLoadIdentity();
  // Set the camera
  int ff;
  int ifourmi =0, plpt =5000 ,id_plpt=0;
 
  gluLookAt(	x, 1.0f, z,
		x+lx, 1.0f,  z+lz,
		0.0f, 1.0f,  0.0f);

 
  glRotatef(90, 1.0f, 0.0f, 0.0f);
  glTranslatef(-5, 00  ,-5);

    printf("Test entre !!!!!\n\n");

  if(loop%variab.getNb_Node() == 0 && loop!= 0){
        
    for (ifourmi = 0; ifourmi<  variab.getNb_Node()*2; ifourmi++){
      if ( plpt > tab_fourmi[ifourmi].distance){
	plpt = tab_fourmi[ifourmi].distance;
	id_plpt = ifourmi;
      }
      
      printf(" \n fourmi %d    %d \n",ifourmi ,tab_fourmi[ifourmi].distance);    
      
    }
    
    printf(" la plus petite fourmie id %d et distance  %d \n",id_plpt ,tab_fourmi[id_plpt].distance);   
    ibest = id_plpt;
    bestdist = tab_fourmi[id_plpt].distance;
    for(int i =0 ;i<variab.getNb_Node();i++)
      {
	best[i] =tab_fourmi[ibest].fourmi_view[i];
      }

    if(boolz == 0)
      {
	ibestbest = bestdist;	   
	for(int i =0 ;i<variab.getNb_Node();i++)
	  {
	    bestbest[i] = best[i];
	  }
	boolz = 1;
      }
    else
      {
	if(ibestbest > bestdist)
	  {
	    ibestbest =  bestdist;
	    for(int i =0 ;i<variab.getNb_Node();i++)
	      {
		bestbest[i] = best[i];
	      }

	  }
	
      }
    
    printf("\n----------------Grande Etape n %d----------------------------\n\n",loop%variab.getNb_Node());
    
    // loop++;
    // sleep(1);
    initialiser_fourmi();
    //     exit(0);
  }


  
  printf("\n------------------loop = %d-------------------------------\n",loop); 

  for(ff = 0; ff<  variab.getNb_Node()*2; ff++)
    {
      
      int i;
      printf("Size : %d \n",tab_fourmi[ff].fourmi_view.size());
      for(i = 0; i<tab_fourmi[ff].fourmi_view.size();i++){
	printf(" %d",tab_fourmi[ff].fourmi_view[i]);
     
      }
      printf("\n");
      
    }


  
  
  for (ListGraph::NodeIt node(g); node != INVALID; ++node)
    {
     

      for (ii = 0; ii<  variab.getNb_Node()*2; ii++){

	if(tab_fourmi[ii].fourmi_view.size() -1 != loop%variab.getNb_Node()) continue;
	
	current_fourmi = -1;	   
	if( tab_fourmi[ii].get_city()  == g.id(node) ){
	  current_fourmi = ii;	  	  
	}
      
      

	if(current_fourmi != -1){
	
	  for (ListGraph::IncEdgeIt ar(g,node); ar!= INVALID; ++ar)   
	    {
	     
	      if( g.id(g.v(ar)) ==  tab_fourmi[current_fourmi].get_city()){
        
		if( tab_fourmi[current_fourmi].view_city(g.id(g.u(ar))) ){
		  myvector.push_back(0.0 );
		   continue;
		}
	      }
	      else if( g.id(g.u(ar)) ==  tab_fourmi[current_fourmi].get_city()){

		if( tab_fourmi[ current_fourmi].view_city(g.id(g.v(ar))) ){		  
		  myvector.push_back(0.0);
		  continue;
		}
	      }
	      
	     
	      myvector.push_back(proba( map_pheromone[ar] , map_distance[ar]) );
	    }

	
	  int i = 0;

	  for (i = 0; i<myvector.size(); i++)
	    {
	      total +=  myvector[i];
	      //   printf(" myvector: %f total: %f  ",myvector[i],total);
	    }
	  //   printf("\n");
	  i = 0;
	  
	  for (ListGraph::InArcIt ar(g,node ) ; ar!= INVALID; ++ar , i++)	  
	    {
	      if(myvector[i] == 0.0){

		map_pourcentage[ar] = 0;
		pourcentage.push_back(map_pourcentage[ar]);
		//	  printf(" 1pp= %f",map_pourcentage[ar]);
		continue;
	      }
	      map_pourcentage[ar] = (100*myvector[i]/total);
	      pourcentage.push_back(map_pourcentage[ar]);
	      //     printf(" 2pp= %f",map_pourcentage[ar]);
	    
	    }

	  
	  /* Je connais pour chaque edge qui parte de node la probbilite d y aller */
	  sort ( pourcentage.begin(),pourcentage.end() , compare);	    
	  id_edge_ok = choix_chemin (g , node , pourcentage );

	  //	   printf("id_edege_ok : %d\n",id_edge_ok);
	 
	  /*
	    deplacemment de la fourmie 
	     Mise a jour des pheromones 
	     Mise a jour de passage 
	  */
	  for (ListGraph::EdgeIt ar(g ); ar!= INVALID; ++ar)   
	    {

	   
	      if(g.id(ar) == id_edge_ok ){

		if( g.id(node) == g.id(g.u(ar)) ){
		  tab_fourmi[current_fourmi].insert_city(g.id(g.v(ar)));
		}
		else{
		  tab_fourmi[current_fourmi].insert_city(g.id(g.u(ar)));
		}
		tab_fourmi[current_fourmi].distance += map_distance[ar];
		map_passage[ar]++;
		map_pheromone[ar] = ( map_pheromone[ar]/2 ) + ( 100 * map_passage[ar]);
		break;
	      }
	     
	    }
	  
	  /*	  for( int j = 0 ; j< tab_fourmi[current_fourmi].fourmi_view.size() -1; j++)
	    {
	      for(int i = j+1;i<tab_fourmi[current_fourmi].fourmi_view.size()-1;i++)
		{
		  if(  tab_fourmi[current_fourmi].fourmi_view[j] == tab_fourmi[current_fourmi].fourmi_view[i]){

		    printf(" currnt %d i %d", current_fourmi, i);

		    exit(0);

		  }
		}
	      
	      
		}*/

	  
	  for (ListGraph::EdgeIt ar(g ); ar!= INVALID; ++ar)   
	    {
	      map_pourcentage[ar] =0;
	    }
	  myvector.clear();
	  pourcentage.clear();
	  total = 0;   	  
	  
	}
      }  
    }
  drawLinesbest();
  drawLines();
  angle+=0.1f;
  loop++;
  glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y) {

  if (key == 27)
    exit(0);
}

void processSpecialKeys(int key, int x, int y) {

  float fraction = 0.5f;
  switch(key) {
  case GLUT_KEY_F1 :
    bool_sleep = 1;
    break;
  case GLUT_KEY_F2 :
    bool_sleep = 0;
    break;
  case GLUT_KEY_F3 :
    red = 0.0;
    green = 0.0;
    blue = 1.0;
    break;
  case GLUT_KEY_RIGHT :
    if(variab.getEdge_select() == variab.getNb_Edge() -1 )
      variab.setEdge_select(0);
    else
      variab.setEdge_select(variab.getEdge_select()+1);
    break;
  case GLUT_KEY_LEFT :
    if(variab.getEdge_select()  ==0)
      variab.setEdge_select( variab.getNb_Edge() -1 );
    else
      variab.setEdge_select(variab.getEdge_select()-1);
    break;

  case GLUT_KEY_UP :
    if(variab.getNode_select() == variab.getNb_Node() -1)
      variab.setNode_select(0);
    else
      variab.setNode_select((variab.getNode_select())+1);
    break;
  case GLUT_KEY_DOWN :
    if(variab.getNode_select()  ==0)
      variab.setNode_select(variab.getNb_Node() -1);
    else
      variab.setNode_select((variab.getNode_select())-1);
    break;
  case GLUT_KEY_F6:
    mapp[variab.getNode_select()].x++;
    break;
  case  GLUT_KEY_F5:
    mapp[variab.getNode_select()].x--;
    break;
  case GLUT_KEY_F7:
    mapp[variab.getNode_select()].z++;
    break;
  case  GLUT_KEY_F8:
    mapp[variab.getNode_select()].z--;
    break;
  }
}

void mouseButton(int button, int state, int x, int y) {

  // only start motion if the left button is pressed
  if (button == GLUT_LEFT_BUTTON) {

    // when the button is released
    if (state == GLUT_UP) {
      angles += deltaAngle;
      xOrigin = -1;
    }
    else  {// state = GLUT_DOWN
      xOrigin = x;
    }
  }
}

void mouseMove(int x, int y) {

  // this will only be true when the left button is down
  if (xOrigin >= 0) {

    // update deltaAngle
    deltaAngle = (x - xOrigin) * 0.001f;

    // update camera's direction
    lx = sin(angles + deltaAngle);
    lz = -cos(angles + deltaAngle);
  }
}

float distanceDeuxPts(pos a, pos b){
  return sqrt(pow(b.x-a.x,2)+pow(b.y-a.y,2)+pow(b.z-a.z,2));
}

void
selectFont(int newfont)
{
  font = fonts[newfont];
  glutPostRedisplay();
}

void
output(int x, int y,int z, char *string)
{
  int len, i;

  glRasterPos3f(x, y,z);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}


int main(int argc, char **argv) {
  //  srand(time(NULL));
  srand(0);
  int i=0;
  mapp[i].x =  (rand()%50) -10;
  mapp[i].y = 0;
  mapp[i].z = rand()%20;
  variab.setNode_select(0);
  variab.setEdge_select(0);
  variab.setNb_Edge(0);
  variab.setNb_Node(0);
  

  voyage();
  
  for (ListGraph::NodeIt a(g ); a!= INVALID; ++a)	  
    {
      variab.setNb_Node(variab.getNb_Node()+1);
    }
  
  for (ListGraph::EdgeIt a(g ); a!= INVALID; ++a)	  
    {
      variab.setNb_Edge(variab.getNb_Edge()+1);
      printf("edge id  =  %d\n", g.id(a));

      
    }

  for(i = 1; i < variab.getNb_Node(); i++)
    {
      for(int j = 0; j < i;j++)
	{
	  do{
	    mapp[j].x = (rand()%50) -10;
	    mapp[j].y = 0;
	    mapp[j].z = rand()%20;
	  }while((distanceDeuxPts(mapp[i],mapp[j]) < 25) );
	}
      
      
    }


  int j, z;
  
  i = variab.getNb_Node() -2;
  j= variab.getNb_Node() -1;
  
  for (ListGraph::EdgeIt a(g ); a!= INVALID; ++a)	  
    {
      map_distance[a] = (int)distanceDeuxPts(mapp[i],mapp[j]);
      printf(" i %d   j %d   distance %d edge id  =  %d\n", i, j ,  (int)distanceDeuxPts(mapp[i],mapp[j]) , g.id(a));

      if(j-1 == i){	 
	i--;
	j=variab.getNb_Node() -1;
	continue;
      }
       j--; 
    }
  //  printf(" \nvariab.getNb_Node()*2   %d\n\n",  variab.getNb_Node()*2);

  /*
  i = variab.getNb_Node()-1;
  j = variab.getNb_Node()-2;
  
    for (ListGraph::EdgeIt a(g ); a!= INVALID; ++a)	  
    {
        for (ListGraph::EdgeIt a(g ); a!= INVALID; ++a)	  
	  {
      
	  }
      
    }
  */

  
  for(i = 0; i < variab.getNb_Node()*2 ; i+=2)
    {

      tab_fourmi[i].insert_city(i/2);
      tab_fourmi[i+1].insert_city(i/2);
      
      printf("Test go  %d!!!!!\n\n" , i);


    }
      printf("Test go  %d!!!!!\n\n" , i);

  for(i = 0; i < variab.getNb_Node()*2; i+=2)
    {
         cout << "Length of line : " << tab_fourmi[i].get_city() <<endl;
         cout << "Length of line : " << tab_fourmi[i+1].get_city()<<endl;

      
     

    }

      printf("Test go !!!!!\n\n");


  // init GLUT and create window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(500,200);
  glutInitWindowSize(1000,500);
  glutCreateWindow("ALgo");

  // register callbacks
  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutIdleFunc(renderScene);

  // here are the new entries
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(processSpecialKeys);
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMove);
  // OpenGL init
  glEnable(GL_DEPTH_TEST);
  // enter GLUT event processing cycle
  glutMainLoop();

  return 1;
}
