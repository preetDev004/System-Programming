#include <fcntl.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

const int MAXBUF = 128;
bool isRunning = false;

void signalHandler(int sigNum);

int main(int argc, char *argv[])
{
    //       For sigaction, see http://man7.org/linux/man-pages/man2/sigaction.2.html
    struct sigaction sa;
    char interface[MAXBUF];
    char statPath[MAXBUF];
    const char logfile[] = "Network.log"; // store network data in Network.log
    int retVal = 0;

    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    retVal = sigaction(SIGUSR1, &sa, NULL);
    if(retVal != 0) {
        cout << "intfMonitor:main: sigaction SIGUSR1 failed: " << strerror(errno) << endl;
        return -1;
    }

    retVal = sigaction(SIGUSR2, &sa, NULL);
    if(retVal != 0) {
        cout << "intfMonitor:main: sigaction SIGUSR2 failed: " << strerror(errno) << endl;
        return -1;
    }

    retVal = sigaction(SIGINT, &sa, NULL);  // ctrl-C
    if(retVal != 0) {
        cout << "intfMonitor:main: sigaction SIGINT failed: " << strerror(errno) << endl;
        return -1;
    }

    retVal = sigaction(SIGTSTP, &sa, NULL); // ctrl-Z
    if(retVal != 0) {
        cout << "intfMonitor:main: sigaction SIGTSTP failed: " << strerror(errno) << endl;
        return -1;
    }

    strncpy(interface, argv[1], MAXBUF); // The interface has been passed as an argument to intfMonitor
    int fd = open(logfile, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    cout << "intfMonitor:main: interface:" << interface << ":  pid:" << getpid() << endl;

    while (!isRunning)
    {
        pause();
    }

    while (isRunning)
    {
        // gather some stats
        int tx_bytes = 0;
        int rx_bytes = 0;
        int tx_packets = 0;
        int rx_packets = 0;
        ifstream infile;
        sprintf(statPath, "/sys/class/net/%s/statistics/tx_bytes", interface);
        infile.open(statPath);
        if (infile.is_open())
        {
            infile >> tx_bytes;
            infile.close();
        }
        sprintf(statPath, "/sys/class/net/%s/statistics/rx_bytes", interface);
        infile.open(statPath);
        if (infile.is_open())
        {
            infile >> rx_bytes;
            infile.close();
        }
        sprintf(statPath, "/sys/class/net/%s/statistics/tx_packets", interface);
        infile.open(statPath);
        if (infile.is_open())
        {
            infile >> tx_packets;
            infile.close();
        }
        sprintf(statPath, "/sys/class/net/%s/statistics/rx_packets", interface);
        infile.open(statPath);
        if (infile.is_open())
        {
            infile >> rx_packets;
            infile.close();
        }
        char data[MAXBUF];
        // write the stats into Network.log
        int len = sprintf(data, "%s: tx_bytes:%d rx_bytes:%d tx_packets:%d rx_packets: %d\n", interface, tx_bytes, rx_bytes, tx_packets, rx_packets);
        write(fd, data, len);
        sleep(1);
    }
    close(fd);

    return 0;
}

void signalHandler(int sigNum)
{
    switch (sigNum)
    {
    case SIGUSR1:
        cout << "intfMonitor: starting up" << endl;
        isRunning = true;
        break;
    case SIGUSR2:
        cout << "intfMonitor: shutting down" << endl;
        isRunning = false;
        break;
    case SIGINT:
        cout << "intfMonitor: ctrl-C discarded" << endl;
        break;
    case SIGTSTP:
        cout << "intfMonitor: ctrl-Z discarded" << endl;
        break;
    default:
        cout << "intfMonitor: undefined signal" << endl;
        break;
    }
}