#include<systemc>
#include<tlm.h>
#include<tlm_utils/tlm_quantumkeeper.h>
#include "Initiator.h"
#include "Initiator_R.h"
#include "Target.h"

class Top : public sc_core::sc_module {
  public:
    //tlm_utils::tlm_quantumkeeper m_qk;
    Initiator *initiator;
    Initiator_R *initiator_r;
    Target *target;
    Target *target_r;
    Top(sc_core::sc_module_name name): sc_core::sc_module(name) {
      tlm::tlm_global_quantum::instance().set(sc_core::sc_time(1,sc_core::SC_US));
      initiator = new Initiator("Initiator_WRITE");
      initiator_r = new Initiator_R("Initiator_READ");
      target = new Target("Target");
      target_r = new Target("Target_R");

      initiator->i_sckt.bind(target->t_sckt);
      initiator_r->i_sckt.bind(target_r->t_sckt);
    }
};

int sc_main(int argc, char* argv[])
{
  Top top("TOP");
  sc_core::sc_start();
  return 0;
}
