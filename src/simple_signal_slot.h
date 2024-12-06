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
*		<2024-DEc-06>
* Decription:
*		TODO
*/
/*===============================================================================================================*/
#ifndef ___SIMPLE_SIGNAL_SLOT__
#define ___SIMPLE_SIGNAL_SLOT__
#include <string>
//#include "simplelog.h"
using namespace std;
#ifdef __cplusplus
extern "C" {
#endif

	typedef enum {
		SS_ERROR_OK = 0,
		SS_ERROR_MUTEX_NULL,
		SS_ERROR_MUTEX_LOCK,
		SS_ERROR_MUTEX_UNLOCK,
	} SIGNAL_SLOT_ERROR;
	typedef enum {
		SS_EVENT_STOP = 0,
	} SIGNAL_SLOT_EVENT;
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
#ifndef LLU
	#define LLU unsigned long long
#endif
typedef struct __GENERIC_DATA_OBJ__ {
	int 
		total;
		/*TODO: comment*/
	int 
		ss_event_id;
		/*TODO: comment*/
	int 
		pc;
		/*TODO: comment*/
	int 
		pl;
		/*TODO: comment*/
	char
		in_main_thread;
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

	void start_doing(simple_signal_slot*, std::string name);
	void join_event_loop(simple_signal_slot*, std::string name);
	virtual int signal_event(simple_signal_slot* src, simple_signal_slot *dest, generic_data_obj_st*);
	virtual int event_slot(generic_data_obj_st*);
	virtual void GetClassCurrentName(std::string& str);
	virtual void AccessMainThread(void *);
	void* m_implement;
	void GetName(std::string& name);
	static int raise_event(simple_signal_slot* target, generic_data_obj_st* evvt);
protected:
private:
};



/*-----------------------------------------------------------------------------------------*/
DLL_API_SIMPLE_SIGNAL_SLOT LLU	
	ss_get_threadid();
/*-----------------------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif
#endif