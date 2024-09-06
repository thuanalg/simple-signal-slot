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
#include "simple_signal_slot.h"
#ifdef __cplusplus
extern "C" {
#endif
/*https://cplusplus.com/reference/Vector/Vector/*/
#include <vector>
using namespace std;
/*-----------------------------------------------------------------------------------------*/

typedef struct __ZZZZZZ__{
	void* target;
	generic_data_obj_st* evt;
} ZZZZZZ;

class simple_implement_signal_slot: public simple_signal_slot{
public:
	simple_implement_signal_slot();
	virtual ~simple_implement_signal_slot();
	int signal_event(simple_signal_slot*, generic_data_obj_st*);
	int event_slot(generic_data_obj_st*);
	void GetClassName(std::string& str);
protected:
private:
	std::vector<ZZZZZZ> m_eventList;
	static int wait_for_event_loop(simple_signal_slot*, generic_data_obj_st*);
};

/*-----------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#endif