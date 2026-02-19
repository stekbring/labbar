#include "Simulator.h"
#include<vector>
#include <iostream>
#include <string>




/*void sim(std::vector<Component*>v,int a,int b,double t)
{
   for(int j{0};j<v.size();j++)
    {
      std::cout << v.at(j)->name<<"     ";
    }

   std::cout<<std::endl; 
  for(int i{0};i<b;i++)
  {
    for(int j{0};j<v.size();j++)
    {
      v.at(j)->update();
      std::cout << v.at(j)->get_voltage()<<"     ";
    }
    std::cout << std::endl;
  }
  
}*/

int main(int argc, char *argv[])
{
  if (argc == 5)
    {
      int iterations{};
      int rows{};
      double tick{};
      double volt{};
 
     
      try{
	iterations = std::stoi(argv[1]);
	rows = std::stoi(argv[2]);
	tick = std::stod(argv[3]);
	volt = std::stod(argv[4]);
      }
      catch(std::invalid_argument& e)
	{
	  std::cerr << "Fel antal argument" << std::endl;
	  exit(0);
	}
  
      if(iterations <= 0 || rows <= 0 || tick <= 0 || volt <= 0)
	{
	  throw std::out_of_range{"Negativa värden"};
	}


      std::vector<Component*> net1;
  
      std::cout << "Krets 1:" << std::endl;
      Connection P1, N1, Q124, Q23;
      net1.push_back(new Battery("Bat", volt, P1, N1));
      net1.push_back(new Resistor("R1", 6.0, P1, Q124));
      net1.push_back(new Resistor("R2", 4.0, Q124, Q23));
      net1.push_back(new Resistor("R3", 8.0, Q23, N1));
      net1.push_back(new Resistor("R4", 12.0, Q124, N1));
      simulate(net1, iterations, rows, tick);

      std::vector<Component*> net2;
      std::cout << "Krets 2:" << std::endl;
      Connection P2, N2, L2, R2;
      net2.push_back(new Battery("Bat", volt, P2, N2));
      net2.push_back(new Resistor("R1", 150.0, P2, L2));
      net2.push_back(new Resistor("R2", 50.0, P2, R2));
      net2.push_back(new Resistor("R3", 100.0, L2, R2));
      net2.push_back(new Resistor("R4", 300.0, L2, N2));
      net2.push_back(new Resistor("R5", 250.0, R2, N2));
      simulate(net2, iterations, rows, tick);

      std::vector<Component*> net3;
      std::cout << "Krets 3:" << std::endl;
      Connection P3, N3, L3, R3;
      net3.push_back(new Battery("Bat", volt, P3, N3));
      net3.push_back(new Resistor("R1", 150.0, P3, L3));
      net3.push_back(new Resistor("R2", 50.0, P3, R3));
      net3.push_back(new Capacitance("C3", 1.0, L3, R3));
      net3.push_back(new Resistor("R4", 300.0, L3, N3));
      net3.push_back(new Capacitance("C5", 0.75, R3, N3));
      simulate(net3, iterations, rows, tick);
    }
  else
    {
      std::cerr << "Fel antal argument" << std::endl;
    }
}



/*int main()
{
  std::vector<Component*>v;
  Connection P,Q124,Q23,N;
 
  v.push_back(new Battery(N,P,"Bat",24.0));
  v.push_back(new Resistor(P,Q124,"R1",6.0));
  v.push_back(new Resistor(Q124,Q23,"R2",4.0));
  v.push_back(new Resistor(Q23,N,"R3",8.0));
  v.push_back(new Resistor(Q124,N,"R4",12.0));

  simulate(v,10000,10,0.1);

  Connection p, n;
vector<Component*> net;
net.push_back(new Battery("Bat", 24.0, p, n));
net.push_back(new Resistor("R1", 6.0, p, n));
net.push_back(new Resistor("R2", 8.0, p, n));
simulate(net, 10000, 10, 0.1);


  for(Component* i: v )
  {
    delete i;
  }
 
  return 0;
}*/

