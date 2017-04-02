#include<systemc>
#include "Interconnect_1.h"
#include "Initiator.h"
#include "Target.h"
SC_MODULE(Top) {

 Initiator *initiator;
 Interconnect_1 *interconnect_1;
 Interconnect_1 *interconnect_2;
 Target *target;

 SC_CTOR(Top) {
   initiator = new Initiator("initiator");
   interconnect_1 = new Interconnect_1("interconnect_1");
   interconnect_2 = new Interconnect_1("interconnect_2");
   target = new Target("target");

  initiator->i_sckt.bind(interconnect_1->t_sckt);
  interconnect_1->i_sckt.bind(interconnect_2->t_sckt);
  interconnect_2->i_sckt.bind(target->t_sckt);
 }
};

int sc_main(int argc, char* argv[]) {

  Top top("top");
  sc_core::sc_start();
  return 0;
}
