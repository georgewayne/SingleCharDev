#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int main()
{
    int ret, fd=0;
    int choice=0;
    size_t len=1;
    char str[256];
    while (choice != 5) {
        printf("\nPlease choose operation:\n\t1: read\n\t2: write\n\t3: open\n\t4: close\n\t5: exit this program\nYour choice(1~5): ");
        scanf("%[^\n]%*c", str);
        sscanf(str, "%d", &choice);
        printf("choice: %s -> %d\n", str, choice);
        switch(choice) {
            case 1: /*read*/
                if (fd <= 0) {
                    printf("Device not open. Please first open the device\n");
                    break;
                }
                ret = read(fd, NULL, len);
                if (ret < 0) {
                    perror("Fail to read.\n");
                    return errno;
                }
                break;
            case 2: /*write*/
                if (fd <= 0) {
                    printf("Device not open. Please first open the device\n");
                    break;
                }
                ret = write(fd, NULL, len);
                if (ret < 0) {
                    perror("Fail to write.\n");
                    return errno;
                }
                break;
            case 3: /*open*/
                if (fd > 0) {
                    printf("Device already open.\n");
                    break;
                }
                fd = open("/dev/mydevname", O_RDWR);    //open with read/write
                if (fd < 0) {
                    perror("Fail to open the device...");
                    return errno;
                }
                break;
            case 4: /*close*/
                if (fd == 0) {
                    printf("Device already closed.\n");
                    break;
                }
                ret = close(fd);
                if (ret < 0) {
                    perror("Device fail to close.\n");
                    return errno;
                }
                fd = 0;
                break;
            case 5:
                return 0;
            default:
                break;
        }
    } /*while loop*/
    return 0;
}
