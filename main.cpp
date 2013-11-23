#include <iostream>
#include <chrono>
#include <thread>
#include "lusb0_usb.h"

namespace totto8492
{

enum ERROR_REASON
{
    USB_NO_ERROR,
    USB_BUS_NOT_FOUND,
    USB_DEVICE_NOT_FOUND
};

} // totto8492

int main()
{
    using namespace std;
    using namespace totto8492;

    cout << "This software uses libusb-win32." << endl;

    usb_init();
    if(!usb_find_busses())
        return USB_BUS_NOT_FOUND;

    if(!usb_find_devices())
        return USB_DEVICE_NOT_FOUND;

    struct usb_bus *bus = usb_get_busses();
    while(bus)
    {
        struct usb_device *device = bus->devices;
        while(device)
        {
            if(device->descriptor.idVendor == 0x054c && device->descriptor.idProduct == 0x0268)
            {
                cout << "Found ! it's SIXAXIS !" << endl;
                cout << "bus: " << bus->dirname << endl;
                cout << "dev: " << device->filename << endl;
                usb_dev_handle * handle = usb_open(device);
                char zero[17] = { };
                usb_control_msg(handle, 0xa1, 1, 0x03f2, device->config->interface->altsetting->bInterfaceNumber, zero, sizeof(zero), 1000);
                usb_close(handle);
            }
            device = device->next;
        }
        bus = bus->next;
    }
    this_thread::sleep_for(chrono::milliseconds(1000));
    return 0;
}
