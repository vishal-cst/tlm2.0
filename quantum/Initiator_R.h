#include<systemc>
#include<tlm.h>
#include<tlm_utils/tlm_quantumkeeper.h>

class Initiator_R : public sc_core::sc_module,tlm::tlm_bw_transport_if<> {
  public:
    tlm::tlm_initiator_socket<32> i_sckt;
    tlm_utils::tlm_quantumkeeper m_qk;
    SC_HAS_PROCESS(Initiator_R);
    Initiator_R(sc_core::sc_module_name name) : sc_core::sc_module(name), i_sckt("Initiator Socket") {
      SC_THREAD(thread);
      i_sckt.bind(*this);
    }
    void thread();
    void start_of_simulation();
   virtual tlm::tlm_sync_enum nb_transport_bw(
    tlm::tlm_generic_payload& trans,
    tlm::tlm_phase& phase,
    sc_core::sc_time& t) {
    return tlm::TLM_COMPLETED;
  }
  // Dummy implementation
  virtual void invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range)
  { }
};
