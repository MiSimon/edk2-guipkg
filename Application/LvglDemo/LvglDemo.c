#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <lvgl/lvgl.h>
#include <lvgl/demos/lv_demos.h>

EFI_STATUS EFIAPI UefiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE * SystemTable)
{
    EFI_HANDLE handle = NULL;
    lv_display_t* display = NULL;
    lv_indev_t* indev = NULL;
    lv_group_t* group = NULL;
    lv_obj_t* cursor = NULL;
    // used to get out of the main loop
    size_t counter;

    // Init the display
    handle = lv_uefi_display_get_active();
    if(handle == NULL) {
        handle = lv_uefi_display_get_any();
    }
    if(handle == NULL) {
        lv_deinit();
        return EFI_UNSUPPORTED;
    }

    display = lv_uefi_display_create(handle); 
    lv_display_set_default(display);

    // Create the group
    group = lv_group_create();
    lv_group_set_default(group);

    // Create an image that can be used as cursor
    cursor = lv_image_create(lv_layer_top());
    lv_image_set_src(cursor, "E:cursor.png");

    // Create the input devices
    indev = lv_uefi_simple_text_input_indev_create(); 
    lv_indev_set_group(indev, lv_group_get_default());
    lv_uefi_simple_text_input_indev_add_all(indev);

    indev = lv_uefi_simple_pointer_indev_create(NULL); 
    lv_uefi_simple_pointer_indev_add_all(indev);
    lv_indev_set_cursor(indev, cursor);

    indev = lv_uefi_absolute_pointer_indev_create(NULL);
    lv_uefi_absolute_pointer_indev_add_all(indev); 

    lv_demo_widgets();

    // Run main loop for ~ 10 seconds
    counter = 0;
    while(counter < 10000) {
        counter ++;
        gBS->Stall(1000);
        lv_tick_inc(1);
        lv_timer_handler();
    }

    return EFI_SUCCESS;
}