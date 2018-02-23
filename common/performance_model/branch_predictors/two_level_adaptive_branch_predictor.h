#include "branch_predictor.h"
#include "saturating_predictor.h"
#include <boost/scoped_array.hpp>

class TwoLevelAdaptiveBranchPredictor : public BranchPredictor
{
public:
   TwoLevelAdaptiveBranchPredictor(String name, core_id_t core_id, UInt32 entries);
   ~TwoLevelAdaptiveBranchPredictor();

   bool predict(IntPtr ip, IntPtr target);
   void update(bool predicted, bool actual, IntPtr ip, IntPtr target);

private:

   template<typename Addr>
   Addr ilog2(Addr n)
   {
      Addr i;
      for(i=0;n>0;n>>=1,i++) {}
      return i-1;
   }

   void reset()
   {
      for (unsigned int i = 0 ; i < m_num_entries ; i++) {
         m_table[i].reset();
      }
   }


private:

   UInt32 m_bhr; 
   IntPtr m_mask;
   //entries= pow(2, k) = pow(2, 20) = 1048576
   UInt32 m_num_entries;
   std::vector<SaturatingPredictor<2>> m_table;
};
