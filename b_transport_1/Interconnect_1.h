/**********************************************************************************************************
* How to implement loosely-timed methodology using b_transport callback interface with temporal decoupling*
*                                                                                                         *
*********************************************************************************************************/


#include<systemc>
#include<tlm.h>
#include<tlm_utils/simple_initiator_socket.h>
#include<tlm_utils/simple_target_socket.h>

class Interconnect_1 : public sc_core::sc_module {
  public:
    static unsigned int count;
    tlm_utils::simple_initiator_socket<Interconnect_1> i_sckt;
    tlm_utils::simple_target_socket<Interconnect_1> t_sckt;
    SC_HAS_PROCESS(Interconnect_1);
    Interconnect_1(sc_core::sc_module_name name):sc_core::sc_module(name) {
      t_sckt.register_b_transport(this,&Interconnect_1::b_transport);
    }

    virtual void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay) {
      unsigned char* ptr = trans.get_data_ptr();
      unsigned int len = trans.get_data_length();
      unsigned int temp;
      memcpy(&temp,ptr,len);
      std::cout<<"Inside Interconnect_"<<count++<<" Data = "<<temp<<std::endl;
      unsigned int data = 5;
      trans.set_address(0x1235);
      //trans.set_data_ptr(reinterpret_cast<unsigned char*>(&data));
      i_sckt->b_transport(trans,delay);
    }
};

unsigned int Interconnect_1::count = 0;
