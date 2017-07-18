/*
 * Update deleter for HBL
 * Based on https://github.com/wiiudev/libwiiu/tree/master/examples/remove_update by wj44
 */

#include <easy/easy.h>
#include <stdio.h>

int Menu_Main(void)
{
	printf("This tool will try to remove the currently downloading system update.\n"
		   "It will NOT downgrade your system if your Wii U already updated.\n"
		   "Try it at your own risk; the update could also not get removed.\n\n"
		   
		   "Press 'A' to try removing the system update\n"
		   "Press 'HOME' to go back to HBL\n\n");
	
	while(1) {
		update_buttons();
		if (button_pressed(VPAD_BUTTON_A)) break;
		if (button_pressed(VPAD_BUTTON_HOME)) return 0;
	}
	
	u32 nn_ccr_handle;
	OSDynLoad_Acquire("nn_ccr.rpl", &nn_ccr_handle);
	
	void(*CCRSysDRCFWUpdateForward)();
	OSDynLoad_FindExport(nn_ccr_handle, 0, "CCRSysDRCFWUpdateForward", &CCRSysDRCFWUpdateForward);
	
	CCRSysDRCFWUpdateForward();

	printf("Done!\n");
	
	while(!button_pressed(VPAD_BUTTON_HOME))
		update_buttons();
	
	return 0;
}

