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
    Initiator(sc_module_name name):sc_module(name) {
      SC_THREAD(call);
    }

    void call() {
      tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
      sc_time delay = SC_ZERO_TIME;
      tlm::tlm_command cmd = static_cast(rand() % 2);
      if (cmd == tlm::TLM_WRITE_COMMAND) data = 0xFF000000 | i;

      trans->set_command( cmd );
      trans->set_address( 0x1234 );
      trans->set_data_ptr( reinterpret_cast<unsigned char*>(&data) );
      trans->set_data_length( 4 );
      trans->set_streaming_width( 4 );
      trans->set_byte_enable_ptr( 0 );
      trans->set_dmi_allowed( false );
      trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );

      i_sckt->b_transport(trans,delay);
    }
};
