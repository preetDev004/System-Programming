#include <errno.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <arpa/inet.h>
#include <unistd.h>

#define NAME_SIZE 16

using namespace std;

int main()
{
    int fd;
    int ret;
    int selection;
    struct ifreq ifr;
    char if_name[NAME_SIZE];
    unsigned char *mac = NULL;

    cout << "Enter the interface name: ";
    cin >> if_name;

    size_t if_name_len = strlen(if_name);
    if (if_name_len < sizeof(ifr.ifr_name))
    {
        memcpy(ifr.ifr_name, if_name, if_name_len);
        ifr.ifr_name[if_name_len] = 0;
    }
    else
    {
        cout << "Interface name is too long!" << endl;
        return -1;
    }

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        cout << strerror(errno);
        return -1;
    }

    system("clear");
    do
    {
        cout << "Choose from the following:" << endl;
        cout << "1. Hardware address" << endl;
        cout << "2. IP address" << endl;
        cout << "3. Network mask" << endl;
        cout << "4. Broadcast address" << endl;
        cout << "0. Exit" << endl
             << endl;
        cout << "Enter your choice: ";
        cin >> selection;

        switch (selection)
        {
        case 1:
            ret = ioctl(fd, SIOCGIFHWADDR, &ifr);
            if (ret < 0)
            {
                cout << strerror(errno) << endl;
            }
            else if (ifr.ifr_hwaddr.sa_family != ARPHRD_ETHER)
            {
                cout << "Not an Ethernet interface" << endl;
            }
            else
            {
                mac = (unsigned char *)ifr.ifr_hwaddr.sa_data;
                cout << "MAC Address: " << hex << (int)mac[0] << ":" << (int)mac[1] << ":" << (int)mac[2] << ":" << (int)mac[3] << ":" << (int)mac[4] << ":" << (int)mac[5] << dec << endl;
            }
            break;
        case 2:
            ret = ioctl(fd, SIOCGIFADDR, &ifr);
            if (ret < 0)
            {
                cout << (errno == EADDRNOTAVAIL ? "No IPv4 address assigned to this interface" : strerror(errno)) << endl;
            }
            else
            {
                cout << "IP Address: " << inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr) << endl;
            }
            break;
        case 3:
            ret = ioctl(fd, SIOCGIFNETMASK, &ifr);
            if (ret < 0)
            {
                cout << (errno == EADDRNOTAVAIL ? "No network mask assigned to this interface" : strerror(errno)) << endl;
            }
            else
            {
                cout << "Network Mask: " << inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr) << endl;
            }
            break;
        case 4:
            ret = ioctl(fd, SIOCGIFBRDADDR, &ifr);
            if (ret < 0)
            {
                cout << (errno == EADDRNOTAVAIL ? "No broadcast address assigned to this interface" : strerror(errno)) << endl;
            }
            else
            {
                cout << "Broadcast Address: " << inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr) << endl;
            }
            break;
        }
        if (selection != 0)
        {
            char key;
            cout << endl;
            cout << "-----------------------------" << endl;
            cout << "Press any key to continue: ";
            cin >> key;
            system("clear");
        }
    } while (selection != 0);

    close(fd);
    return 0;
}
