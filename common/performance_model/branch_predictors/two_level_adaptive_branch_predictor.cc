#include "simulator.h"
#include "two_level_adaptive_branch_predictor.h"


TwoLevelAdaptiveBranchPredictor::TwoLevelAdaptiveBranchPredictor(String name, core_id_t core_id, UInt32 entries)
   : BranchPredictor(name, core_id), m_num_entries(entries), m_table(entries, 0)
{
	reset();

	m_mask=0;
	m_bhr=0;

	
	for (unsigned int i = 0 ; i < ilog2(m_num_entries) ; i++)
      	{
         m_mask |= (1L<<i);
      	}

	LOG_PRINT("entries %d, m_mask %d", m_num_entries, m_mask);
	
}

TwoLevelAdaptiveBranchPredictor::~TwoLevelAdaptiveBranchPredictor()
{
}


bool TwoLevelAdaptiveBranchPredictor::predict(IntPtr ip, IntPtr target)
{
   	//get the entry using current BHR pattern.
	return (m_table[m_bhr].predict());
}

void TwoLevelAdaptiveBranchPredictor::update(bool predicted, bool actual, IntPtr ip, IntPtr target)
{
  	 updateCounters(predicted, actual);

   	//shift left the actual bit.
	m_bhr = m_bhr << 1;	
	if(actual)
	{
		m_bhr |= 1;
	}
	m_bhr &= m_mask;
	
	LOG_PRINT("actual %d, m_bhr %d", actual, m_bhr);

   	//update the entry.
	if(actual)
	{
		++m_table[m_bhr];
	}
	else
	{
		--m_table[m_bhr];
	}

}
