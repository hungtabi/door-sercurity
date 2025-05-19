#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstring>

using namespace std;
#define DEVICE_PATH "/dev/tabi_device"

#define MY_IOCTL_MAGIC 'a'
#define WR_DOOR_STA _IOW (MY_IOCTL_MAGIC, 'a', int)
#define RD_DOOR_STA _IOR (MY_IOCTL_MAGIC, 'b', int)
#define WR_C_PASS _IOW (MY_IOCTL_MAGIC, 'd', char[6])
#define RD_C_PASS _IOR (MY_IOCTL_MAGIC, 'e', char[6])

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);
    if (fd < 0) {
        cerr << "Failed to open device file: " << DEVICE_PATH << std::endl;
        return 1;
    }
    
    int door_state;
    cout << "Door state written: ";
    cin >> door_state;
    if (ioctl(fd, WR_DOOR_STA, &door_state) < 0) {
        cerr << "Failed to write door state via ioctl" << endl;
    } else {
        cout << "Door state written: " << door_state << endl;
    }
    int read_state;
    if (ioctl(fd, RD_DOOR_STA, &read_state) < 0) {
        cerr << "Failed to read door state via ioctl" << endl;
    } else {
        cout << "Door state read: " << read_state << endl;
    }
    
    char pass[6];
    
    char read_pass[6] = {};
    cout << "Password written: " << endl;
    cin >> pass ;
    if (ioctl(fd, RD_C_PASS, &read_pass) < 0) {
        cerr << "Failed to read password" << endl;
    } else {
        cout << "pass: " << read_pass;
        if(memcmp(pass, read_pass,6) == 0)
            cout << "correct pass" << endl;
        else
            cout << "incorrect pass" << endl;
    }
    
    cout << "Password written: " << endl;
    cin >> pass ;
    if (ioctl(fd, WR_C_PASS, &pass) < 0) {
        cerr << "Failed to write password" << endl;
    } else {
        cout << "Password written: " << pass << endl;
    }
    close(fd);
    return 0;
}
