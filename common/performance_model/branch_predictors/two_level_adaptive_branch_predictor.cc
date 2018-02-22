#include "simulator.h"
#include "two_level_adaptive_branch_predictor.h"

TwoLevelAdaptiveBranchPredictor::TwoLevelAdaptiveBranchPredictor(String name, core_id_t core_id, UInt32 size)
   : BranchPredictor(name, core_id)
{
}

TwoLevelAdaptiveBranchPredictor::~TwoLevelAdaptiveBranchPredictor()
{
}

bool TwoLevelAdaptiveBranchPredictor::predict(IntPtr ip, IntPtr target)
{

   return 1;
}

void TwoLevelAdaptiveBranchPredictor::update(bool predicted, bool actual, IntPtr ip, IntPtr target)
{
   updateCounters(predicted, actual);
  
	
}
