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
*		<2024-Sep-04>
* Decription:
*		TODO
*/
/*===============================================================================================================*/
#ifndef ___SIMPLE_SIGNAL_SLOT__
#define ___SIMPLE_SIGNAL_SLOT__
#include <string>
using namespace std;
#ifdef __cplusplus
extern "C" {
#endif

/*
#ifndef UNIX_LINUX
	#define UNIX_LINUX
#endif
*/

/*-----------------------------------------------------------------------------------------*/
#ifndef  UNIX_LINUX
	#ifndef __SIMPLE_SIGNAL_SLOT_STATIC_LOG__
		#ifdef EXPORT_DLL_API_SIMPLE_SIGNAL_SLOT
			#define DLL_API_SIMPLE_SIGNAL_SLOT		__declspec(dllexport)
		#else
			#define DLL_API_SIMPLE_SIGNAL_SLOT		__declspec(dllimport)
		#endif
	#else
		#define DLL_API_SIMPLE_SIGNAL_SLOT
	#endif
#else
	#define DLL_API_SIMPLE_SIGNAL_SLOT
#endif /*! UNIX_LINUX */ 
/*-----------------------------------------------------------------------------------------*/
typedef struct __GENERIC_DATA_OBJ__ {
	int 
		total;
		/*TODO: comment*/
	int 
		simple_event_id;
		/*TODO: comment*/
	int 
		pc;
		/*TODO: comment*/
	int 
		pl;
		/*TODO: comment*/
	char 
		data[0];
		/*TODO: comment*/
} GENERIC_DATA_OBJ;

#define generic_data_obj_st		GENERIC_DATA_OBJ

class DLL_API_SIMPLE_SIGNAL_SLOT simple_signal_slot {
public:
	simple_signal_slot();
	virtual ~simple_signal_slot();
	virtual int signal_event(simple_signal_slot*, generic_data_obj_st*);
	virtual int event_slot(generic_data_obj_st*);
	virtual void GetClassCurrentName(std::string& str);
	//char class_name[128];

protected:
private:
	simple_signal_slot *m_implement;	
};

/*-----------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#endif