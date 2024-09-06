#include "simple_signal_slot.h"
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

simple_signal_slot::simple_signal_slot()
{
	m_implement = 0;
	fprintf(stdout, "---\n");
}

simple_signal_slot::~simple_signal_slot()
{
	if (m_implement) {
		delete(m_implement);
		m_implement = 0;
	}
	fprintf(stdout, "===========\n");
}

int simple_signal_slot::signal_event(simple_signal_slot *target, generic_data_obj_st *evvt)
{
	int ret = 0;
	fprintf(stdout, "===========\n");
	if (m_implement) {
		ret = m_implement->signal_event(target, evvt);
	}
	return ret;
}

int simple_signal_slot::event_slot(generic_data_obj_st * evvt)
{
	int ret = 0;
	fprintf(stdout, "===========\n");
	if (m_implement) {
		ret = m_implement->event_slot(evvt);
	}
	return ret;
	return 0;
}

void simple_signal_slot::GetClassCurrentName(std::string& str)
{
	str.clear();
	str = "simple_signal_slot";
}