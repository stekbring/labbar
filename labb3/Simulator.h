#ifndef Simulator_H
#define Simulator_H
#include <iostream>
#include<string>
#include <vector>

class Connection
{
//private:
  //double charge;
public:
  Connection();
  //operator double();
  //Connection operator=(double rhs);
  double volt{};
  double get_volt();
  void set_volt(double & input);

};


class Component
{

public:
  Component(std::string n, Connection & l,Connection & r);
  virtual~Component() = default;
  
  //virtual double get_voltage()const;
  virtual double get_current() = 0;
  virtual void simulate(double time) = 0;
  // Component operator-();// vet ej vilken  operator

double get_volt();
std::string get_name();

private:
std::string name;
protected:
  
  Connection& left;
  Connection& right;
};




class Resistor : public Component
{

  
private:
  double resistance;

public:
  Resistor(std::string n, double const U, Connection & l,Connection & r);
  //double get_voltage()const override{return calc_Volt();}
  double get_current() override;
  void simulate (double time_tick) override;

 // double calc_Volt()const;
  //double calc_Cur()const;
  

};

class Battery : public Component
{
public:
  Battery(std::string n,double v, Connection & l,Connection & r);
  double get_voltage();
  double get_current() override;
  void simulate(double time_tick) override;

private:
  double voltage;
};

class Capacitance : public Component
{
  public:
  Capacitance(std::string n,
	      double ch, Connection & l,
	      Connection & r);
  
  double get_current();
  void simulate(double time_tick) override;
  
private:
  double capacitance, charge{0};
  
};

void simulate(std::vector<Component*> net, int iterations, int rows, double time_tick);



#endif
