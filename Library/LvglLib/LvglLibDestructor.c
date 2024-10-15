#include <lvgl/lvgl.h>
#include <Uefi.h>

EFI_STATUS
EFIAPI
LvglLibDestructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable) 
{
    lv_deinit();
	
	return EFI_SUCCESS;
}