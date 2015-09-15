#include "voyage.h"


using namespace std;

// Member functions definitions including constructor

 
int Fourmi::view_city(int city)
{

  int i;
  for(i = 0; i<fourmi_view.size();i++){
    if(city ==fourmi_view[i] )
      return 1;
  }
 
  return 0;
}

int Fourmi::get_city()
{
 return fourmi_view.back();
}

void Fourmi::insert_city(int city)
{
   fourmi_view.push_back(city);
}

void Fourmi::clean_city()
{
   fourmi_view.clear();
}
