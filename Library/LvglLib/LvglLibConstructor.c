#include <lvgl/lvgl.h>
#include <Uefi.h>

EFI_STATUS
EFIAPI
LvglLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable)
{
	lv_uefi_init(ImageHandle, SystemTable);
    lv_init();
	
    if(!lv_is_initialized()) return EFI_NOT_READY;
	
	return EFI_SUCCESS;
}
