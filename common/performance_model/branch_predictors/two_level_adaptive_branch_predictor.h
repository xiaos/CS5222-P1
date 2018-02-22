#include "branch_predictor.h"

#include <vector>

class TwoLevelAdaptiveBranchPredictor : public BranchPredictor
{
public:
   TwoLevelAdaptiveBranchPredictor(String name, core_id_t core_id);
   ~TwoLevelAdaptiveBranchPredictor();

   bool predict(IntPtr ip, IntPtr target);
   void update(bool predicted, bool actual, IntPtr ip, IntPtr target);

private:
   //k=20

   UInt32 BHR; 
};
