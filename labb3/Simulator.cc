#include "Simulator.h"
#include<string>
#include <iomanip>

Connection::Connection()
  //:charge{0}
{

}


/*Connection Connection:: operator=(double rhs)
{
  charge = rhs;
  return *this;
}

Connection :: operator double()
{
  return charge;
}*/

Component::Component(std::string n, Connection & l,Connection & r)
  :name {n},left{l},right{r}
{

}

/*double Component:: get_voltage()const
{
  return double(left);
}
double Component:: get_current()const
{
  return 0;
}*/



/*void Component:: update()
{
  left = double(left)-get_voltage();
  right = get_voltage();
}*/

Resistor::Resistor(std::string n,double const U, Connection & l,Connection & r)
  :Component{n,l,r},resistance{U} // kan behöva lägga till component 
{

}
/*double Resistor:: calc_Volt()const
{
  return double(left)-double(right);
}
double Resistor:: calc_Cur()const
{
   return (double(left)-double(right))/resistance; // gånger tidsenhet
}*/


Battery::Battery(std::string n,double v, Connection & l,Connection & r)
  :Component{n,l,r}, voltage{v}
{

}


Capacitance::Capacitance(std::string n,
			 double const ca, Connection & l,
			 Connection & r)
  :Component{n,l,r}, capacitance{ca}, charge{0.0}
{

}
//////CONNECTION/////////
double Connection::get_volt()
{
  return volt;
}

void Connection::set_volt(double & input)
{
  volt = input;
}


///////Component////////////////

double Component::get_current()
{
  return 0.0;
}

double Component::get_volt()
{
  double volt{};

  if (left.get_volt() >= right.get_volt())
    {
      volt = left.get_volt() - right.get_volt();
    }
  else
    {
      volt = right.get_volt() - left.get_volt();
    }

  return volt;
}

std::string Component::get_name()
{
  return name;
}

//////RESISTOR///////////

double Resistor::get_current()
{
  return get_volt() / resistance;
}

void Resistor::simulate(double time_tick)
{
  double tmp = (get_volt() / resistance) * time_tick;
  if (left.volt == right.volt){
    return;
  } else if(left.volt > right.volt) {
    left.volt = left.volt - tmp;
    right.volt = right.volt + tmp;
  } else {
    left.volt = left.volt + tmp;
    right.volt = right.volt - tmp;
  }
}

////////BATTERY//////////

double Battery::get_voltage()
{
  return voltage;
}

double Battery::get_current()
{
  return 0.0;
}

void Battery::simulate(double time_tick)
{
  left.volt = get_voltage();
  right.volt = 0.0 * time_tick;
}


///////////CAPACITANCE///////////

double Capacitance::get_current()
{
  return capacitance*(get_volt() - charge);
}

void Capacitance::simulate(double time_tick)
{
  double tmp = get_current() * time_tick;
  charge = charge + tmp;

  if(left.volt >= right.volt) {
    left.volt = left.volt - tmp;
    right.volt = right.volt + tmp;
  } else {
    left.volt = left.volt + tmp;
    right.volt = right.volt - tmp;
  }
}

void simulate(std::vector<Component*> net, int iterations, int rows, double time_tick)
{
  for (int i = 0; i < static_cast<int>(net.size()); i++)
    {
      std::cout << std::setw(10) << net[i] -> get_name();
    }
  std::cout << std::endl;

  for (int i = 0; i < static_cast<int>(net.size()); i++)
    {
      std::cout << std::setw(7) << "Volt" << std::setw(7) << "Curr";
    }
  std::cout << std::endl;

  for (int i = 0; i < rows; i++)
    {
      for (int i = 0; i < iterations / rows; i++)
	{
	  for (Component* c : net)
	    {
	      c->simulate(time_tick);
	    }
	}
      for (Component* c : net)
	{
	  std::cout << std::setw(7)
	       << std::setprecision(2)
	       << std::fixed
	       << c->get_volt()
	       << std::setw(7)
	       << std::setprecision(2)
	       << c->get_current();
	}
      std::cout << std::endl;
    }
  for (int i = 0; i < static_cast<int>(net.size()); i++)
    {
      delete net[i];
    }
}


