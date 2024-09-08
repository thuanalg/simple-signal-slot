/*===============================================================================================================*/
/* Email:
*		<nguyenthaithuanalg@gmail.com> - Nguyễn Thái Thuận
* Mobile:
*		<+084.799.324.179>
* Skype:
*		<nguyenthaithuanalg>
* Date:
*		<2024-Sep-05>
* The lasted modified date:
*		<2024-Sep-05>
* Decription:
*		TODO
*/
/*===============================================================================================================*/

#ifndef ___SIMPLE_IMPLEMENT_SIGNAL_SLOT__
#define ___SIMPLE_IMPLEMENT_SIGNAL_SLOT__
#include <vector>
using namespace std;
#include "simple_signal_slot.h"
#ifdef __cplusplus
extern "C" {
#endif
/*https://cplusplus.com/reference/Vector/Vector/*/

/*-----------------------------------------------------------------------------------------*/

typedef struct __ZZZZZZ__{
	void* target;
	generic_data_obj_st* evt;
} ZZZZZZ;

class simple_implement_signal_slot: public simple_signal_slot{
public:
	simple_implement_signal_slot();
	simple_implement_signal_slot(simple_signal_slot *);
	virtual ~simple_implement_signal_slot();
	int signal_event(simple_signal_slot*, generic_data_obj_st*);
	int event_slot(generic_data_obj_st*);
	void GetClassCurrentName(std::string& str);
	std::vector<ZZZZZZ> m_eventList;
	void* m_sem;
	void* m_mutex;
	simple_implement_signal_slot* m_looper = 0;
protected:
private:
	int generate_event_thread(void*);
	
};

/*-----------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#endif