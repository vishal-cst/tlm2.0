#include<systemc>
#include "Target.h"

unsigned int Target::mem[5000] ={0} ;

void Target::b_transport(tlm::tlm_generic_payload &trans,sc_core::sc_time &delay) {
  wait(delay);
  tlm::tlm_command cmd = trans.get_command();
  unsigned int    adr = trans.get_address();
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

  if (trans.get_command() == tlm::TLM_READ_COMMAND) {
    memcpy(ptr, &Target::mem[adr], len);
  }
  else if (cmd == tlm::TLM_WRITE_COMMAND) {
    memcpy(&Target::mem[adr], ptr, len);
  }

  //delay = sc_core::SC_ZERO_TIME;
  trans.set_response_status(tlm::TLM_OK_RESPONSE);
}
