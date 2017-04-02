/**********************************************************************************************************
* How to implement loosely-timed methodology using b_transport callback interface with temporal decoupling*
*                                                                                                         *
*********************************************************************************************************/


#include<systemc>
#include<tlm.h>
#include<tlm_utils/simple_initiator_socket.h>

class Initiator : public sc_core::sc_module {
  public:
    tlm_utils::simple_initiator_socket<Initiator> i_sckt;
    SC_HAS_PROCESS(Initiator);
    Initiator(sc_core::sc_module_name name):sc_core::sc_module(name) {
      SC_THREAD(call);
    }

    void call() {
      tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
      unsigned int data = 0;
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      tlm::tlm_command cmd = tlm::TLM_WRITE_COMMAND;
      if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | 0x1234;

      trans->set_command( cmd );
      trans->set_address( 0x1234 );
      trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
      trans->set_data_length( 4 );
      trans->set_streaming_width( 4 );
      trans->set_byte_enable_ptr( 0 );
      trans->set_dmi_allowed( false );
      trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );
      std::cout<<"Before::"<<"Address = "<<0x1234<<"Data = "<<data<<std::endl;
      i_sckt->b_transport(*trans,delay);
      if(tlm::TLM_OK_RESPONSE == trans->get_response_status()) {
        unsigned int temp;
        unsigned char* ptr = trans->get_data_ptr();
        memcpy(&temp,ptr,4);
        std::cout<<"After::"<<"Address = "<<0x1234<<"Data = "<<temp<<std::endl;
      }
    }
};
