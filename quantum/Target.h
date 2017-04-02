#include<systemc>
#include<tlm.h>
#include<tlm_utils/simple_target_socket.h>

class Target : public sc_core::sc_module {
  public:
    static unsigned int mem[5000];
    tlm_utils::simple_target_socket<Target> t_sckt;

   Target(sc_core::sc_module_name name): sc_core::sc_module(name) {
     t_sckt.register_b_transport(this,&Target::b_transport);
   }
   virtual void b_transport(tlm::tlm_generic_payload &trans,sc_core::sc_time &delay);
};


