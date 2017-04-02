#include<systemc>
#include "Initiator_R.h"

void Initiator_R::thread() {
  std::cout<<"GLOBAL Quantum R"<<m_qk.get_global_quantum()<<std::endl;
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_core::sc_time delay = sc_core::SC_ZERO_TIME;

  sc_core::wait(1,sc_core::SC_NS);
  unsigned int data = 0;
  for(unsigned int i=0; i<5000; i++) {
    trans->set_command(tlm::TLM_READ_COMMAND);
    trans->set_address(i);
    data = i*2;
    trans->set_data_ptr(reinterpret_cast<unsigned char*>(&data));  
    trans->set_data_length(4);
    trans->set_streaming_width(4);
    trans->set_byte_enable_ptr(0);
    trans->set_dmi_allowed(false);
    trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
 
    delay = m_qk.get_local_time();

    i_sckt->b_transport(*trans,delay);
    std::cout<<sc_core::sc_time_stamp()<<"@READ from Address = "<<i<<" Data = "<<data<<" delay = "<<delay<<std::endl;
 
  m_qk.set(delay);     // Update local time of quantum keeper(initiator)
  m_qk.inc(sc_core::sc_time(100,sc_core::SC_NS));
  if(m_qk.need_sync()) // Check if current time > next sync point
    m_qk.sync();       // Wait for wait(local_time) and calculate next sync point
  }
}
void Initiator_R::start_of_simulation() {
  m_qk.reset();
}
