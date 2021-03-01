#include "SystemUtil.h"
#include "SystemCallCodes.h"

uint32_t  getControllerStatus(){
	return SystemCall(CONTROLLERSTATUS);
}