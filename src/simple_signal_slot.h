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
#ifndef ___SIMPLE_SINGNAL_SLOT__
#define ___SIMPLE_SINGNAL_SLOT__

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------------------*/
#ifndef  UNIX_LINUX
	#ifndef __SIMPLE_SINGNAL_SLOT_STATIC_LOG__
		#ifdef EXPORT_DLL_API_SIMPLE_SINGNAL_SLOT
			#define DLL_API_SIMPLE_SINGNAL_SLOT		__declspec(dllexport)
		#else
			#define DLL_API_SIMPLE_SINGNAL_SLOT		__declspec(dllimport)
		#endif
	#else
	#define DLL_API_SIMPLE_SINGNAL_SLOT
	#endif
#else
	#define DLL_API_SIMPLE_SINGNAL_SLOT
#endif /*! UNIX_LINUX */ 
/*-----------------------------------------------------------------------------------------*/
class DLL_API_SIMPLE_SINGNAL_SLOT simple_signal_slot {
public:
	simple_signal_slot();
	virtual ~simple_signal_slot();
protected:
private:
};

/*-----------------------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
#endif