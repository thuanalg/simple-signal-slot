#include "simple_implement_signal_slot.h"
#include <stdio.h>

/*===============================================================================================================*/
/* Email:
*		<nguyenthaithuanalg@gmail.com> - Nguyễn Thái Thuận
* Mobile:
*		<+084.799.324.179>
* Skype:
*		<nguyenthaithuanalg>
* Date:
*		<2024-Sep-04>
* The lasted modified date:
*		<2024-Sep-05>
* Decription:
*		TODO
*/
/*===============================================================================================================*/

static void* spl_signal_slot_create_sem();
static void* spl_signal_slot_create_mutex();
void* spl_signal_slot_create_sem() {
	void* ret = 0;
	return ret;
}
void* spl_signal_slot_create_mutex() {
	void* ret = 0;
	return ret;
}
simple_implement_signal_slot::simple_implement_signal_slot()
{
	m_eventList.clear();
	fprintf(stdout, "---\n");
}

simple_implement_signal_slot::~simple_implement_signal_slot()
{
	m_eventList.clear();
	fprintf(stdout, "===========\n");
}

int simple_implement_signal_slot::signal_event(simple_signal_slot *target, generic_data_obj_st * evennt)
{
	int ret = 0;
	ZZZZZZ obj = { 0, 0 };
	obj.target = target;
	obj.evt = evennt;
	return ret;
}

int simple_implement_signal_slot::wait_for_event_loop(simple_signal_slot* target, generic_data_obj_st* evvt)
{
	int ret = 0;
	while (1)
	{

	}
	return ret;
}

int simple_implement_signal_slot::event_slot(generic_data_obj_st * evvt)
{
	int ret = 0;

	return ret;
}

void simple_implement_signal_slot::GetClassName(std::string& str)
{
	str.clear();
	str = "simple_implement_signal_slot";
}