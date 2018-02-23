#ifndef NN_BRANCH_PREDICTOR_H
#define NN_BRANCH_PREDICTOR_H

#include "branch_predictor.h"

#include <vector>

class NNBranchPredictor : public BranchPredictor
{
public:
   NNBranchPredictor(String name, core_id_t core_id);
   ~NNBranchPredictor();

   bool predict(IntPtr ip, IntPtr target); 
   void update(bool predicted, bool actual, IntPtr ip, IntPtr target);

private:

   void update_path(bool taken, IntPtr ip, IntPtr target);//update history
   UInt32 bias_hash(IntPtr ip) const; // bais index
   UInt32 index_entries(IntPtr ip, UInt32 i) const; // weights index 


   struct PathInfo {
      bool taken;
      IntPtr target;
      PathInfo(bool bt, IntPtr it): taken(bt), target(it) {}
   };

   SInt32 last_sum;
   UInt32 last_bias_index;
   std::vector<UInt32> last_indexes;
   std::vector<PathInfo> last_path;
   UInt32 last_path_index;  // last_* for temp results


   std::vector<PathInfo> path;
   UInt32 path_index; 

   UInt32 path_length; //128
   UInt32 num_entries; //512
   UInt32 num_bias_entries; // 2048
   UInt32 weight_bits; //[-128,127]

   std::vector<std::vector<SInt32> > weights; //nn weights，512*128
   std::vector<SInt32> bias_weights; //nn bias 2048

   UInt32 theta;//
   SInt64  tc;//used for updating theta
   UInt32 block_size;//weight 8 coumn = 1 table

   std::vector<double> coefficients; //
   double bias_coefficient;//

};

#endif
