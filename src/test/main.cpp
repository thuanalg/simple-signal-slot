#include "simple_signal_slot.h"

#ifndef UNIX_LINUX
	#include "Windows.h"
#else

#endif
#include "simplelog.h"
#include <stdlib.h>
#include <string.h>
class abc : public simple_signal_slot {
public:
	abc();
	virtual ~abc();
	virtual int event_slot(GENERIC_DATA_OBJ*);
	void AccessMainThread(void* evt);
protected:
private:
};
abc::abc() {

}

abc::~abc() {

}
void abc::AccessMainThread(void* evt) {
	std::string name = "";
	this->GetName(name);
	spllog(0, "what's the hell: %s", name.c_str());
}

int abc::event_slot(GENERIC_DATA_OBJ* evt) {
	std::string name = "";
	this->GetName(name);
	spllog(0, "what's the hell: %s", name.c_str());
	return 0;
}
int main(int argc, char *argv[]) {
	spl_init_log("C:/z/simple-signal-slot/simplelog/simplelog.cfg");
	spllog(SPL_LOG_BASE, "test");
	//simple_signal_slot::InitMainthreadID();
	do {
		GENERIC_DATA_OBJ* test_01 = 0;
		GENERIC_DATA_OBJ* test_02 = 0;
		test_01 = (GENERIC_DATA_OBJ*)malloc(sizeof(GENERIC_DATA_OBJ));
		test_02 = (GENERIC_DATA_OBJ*)malloc(sizeof(GENERIC_DATA_OBJ));
		if (!test_01) {
			exit(1);
			return 1;
		}
		if (!test_02) {
			exit(1);
			return 1;
		}
		
		memset(test_01, 0, sizeof(GENERIC_DATA_OBJ));
		memset(test_02, 0, sizeof(GENERIC_DATA_OBJ));
		test_02->in_main_thread = 1;
		
		simple_signal_slot tmp0;
		tmp0.start_doing(0, "tmp0");
		
		simple_signal_slot tmp1;
		tmp1.start_doing(0, "tmp1");
		
		abc obj0;
		obj0.join_event_loop(&tmp0, "obj0");
		
		abc obj1;
		obj1.join_event_loop(&tmp1, "obj1");

		obj1.signal_event(&obj1, &obj0, test_01);
		simple_signal_slot::raise_event(&obj1, test_02);
#ifndef UNIX_LINUX
		//Sleep(5 * 1000);
#else

#endif
		spl_sleep(5 * 1000);
	} while (0);
	spl_finish_log();
	return 0;
}