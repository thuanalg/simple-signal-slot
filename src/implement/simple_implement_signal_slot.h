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

/*-----------------------------------------------------------------------------------------*/

class simple_implement_signal_slot: public simple_signal_slot{
public:
	simple_implement_signal_slot();
	virtual ~simple_implement_signal_slot();
	virtual int signal_event(simple_signal_slot*, generic_data_obj_st*);
	virtual int event_slot(generic_data_obj_st*);
protected:
private:
};

/*-----------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#endif