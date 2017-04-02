#include<systemc>
#include "Initiator.h"

void Initiator::thread() {
  std::cout<<"GLOBAL Quantum"<<m_qk.get_global_quantum()<<std::endl;  
  tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
  sc_core::sc_time delay;
  unsigned int data = 0;
  for(unsigned int i=0; i<5000; i++) {
    delay = m_qk.get_local_time();
    trans->set_command(tlm::TLM_WRITE_COMMAND);
    trans->set_address(i);
    data = i*2;
    trans->set_data_ptr(reinterpret_cast<unsigned char*>(&data));  
    trans->set_data_length(4);
    trans->set_streaming_width(4);
    trans->set_byte_enable_ptr(0);
    trans->set_dmi_allowed(false);
    trans->set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);

    i_sckt->b_transport(*trans,delay);
    std::cout<<sc_core::sc_time_stamp()<<"@Write at Address = "<<i<<" Data = "<<data<<" delay = "<<delay<<std::endl;
  
  m_qk.set(delay);     // Update local time of quantum keeper(initiator)
  m_qk.inc(sc_core::sc_time(100,sc_core::SC_NS));
  if(m_qk.need_sync()) // Check if current time > next sync point
    m_qk.sync();       // Wait for wait(local_time) and calculate next sync point
  }
}
void Initiator::start_of_simulation() {
  m_qk.reset();
}
