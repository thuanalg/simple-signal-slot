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

typedef struct __SS_EVENT_ST__{
	void* target;
	void* src;
	generic_data_obj_st* evt;
} SS_EVENT_ST;

class simple_implement_signal_slot: public simple_signal_slot {
public:
	//simple_implement_signal_slot();
	simple_implement_signal_slot(simple_signal_slot *, std::string &name);
	virtual ~simple_implement_signal_slot();
	int signal_event(simple_signal_slot* , simple_signal_slot*, generic_data_obj_st*);
	int event_slot(generic_data_obj_st*);
	void GetClassCurrentName(std::string& str);
	std::vector<SS_EVENT_ST *> m_eventList;
	void* m_sem;
	void* m_mutex;
	simple_implement_signal_slot* m_looper = 0;
	LLU m_curentThread;
	void SetName(const std::string& name);
	void GetName(std::string& name);
	std::string m_name;
	//std::vector<simple_signal_slot*> m_listChild;

protected:
private:
	int generate_event_thread(void*);
	int initial();
	
};

/*-----------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#endif