/**********************************************************************************************************
* How to implement loosely-timed methodology using b_transport callback interface with temporal decoupling*
*                                                                                                         *
*********************************************************************************************************/


#include<systemc>
#include<tlm.h>
#include<tlm_utils/simple_initiator_socket.h>
#include<tlm_utils/simple_target_socket.h>

class Interconnect_2 : public sc_core::sc_module {
  public:
    tlm_utils::simple_initiator_socket<Initiator> i_sckt;
    tlm_utils::simple_target_socket<Initiator> t_sckt;
    SC_HAS_PROCESS(Interconnect_2);
    Interconnect_2(sc_module_name name):sc_module(name) {
      t_sckt.register_b_transport(this,&Interconnect_2::b_transport);
    }

    virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {
      i_sckt->b_transport(trans,delay);
    }
};
