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

simple_implement_signal_slot::simple_implement_signal_slot()
{
	fprintf(stdout, "---\n");
}

simple_implement_signal_slot::~simple_implement_signal_slot()
{
	fprintf(stdout, "===========\n");
}

int simple_implement_signal_slot::signal_event(simple_signal_slot *target, generic_data_obj_st *evvt)
{
	int ret = 0;

	return ret;
}

int simple_implement_signal_slot::event_slot(generic_data_obj_st * evvt)
{
	int ret = 0;

	return ret;
}