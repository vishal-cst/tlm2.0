/**********************************************************************************************************
* How to implement loosely-timed methodology using b_transport callback interface with temporal decoupling*
*                                                                                                         *
*********************************************************************************************************/


#include<systemc>
#include<tlm.h>
#include<tlm_utils/simple_target_socket.h>

class Target : public sc_core::sc_module {
  public:
    tlm_utils::simple_target_socket<Target> t_sckt;
    SC_HAS_PROCESS(Target);
    Target(sc_core::sc_module_name name):sc_core::sc_module(name) {
      t_sckt.register_b_transport(this,&Target::b_transport);
    }

    virtual void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay) {
      tlm::tlm_command cmd = trans.get_command();
      sc_dt::uint64    adr = trans.get_address();
      unsigned char*   ptr = trans.get_data_ptr();
      unsigned int     len = trans.get_data_length();
      unsigned char*   byt = trans.get_byte_enable_ptr();
      unsigned int     wid = trans.get_streaming_width();
      unsigned int temp;
      memcpy(&temp,ptr,len);
      std::cout<<"Inside Target::"<<"Address = "<<adr<<" Data = "<<temp<<std::endl;
      
      //wait(delay);
      trans.set_response_status(tlm::TLM_OK_RESPONSE);
    }
};
