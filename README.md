#illustrate
This program is very similar to proot, but it is not based on proot, it can mount login and unmount.
It needs to be mounted using img.



#question


Q:How to make img?


note:Please do not download Linux with a different architecture than yours.


A:


1. Download the rootfs you want
2. Enter: sudo dd if=/dev/zero of={name}.img bs=1M count={count}M status=progress
3. Enter: mount -o loop {name}.img ./{dir}
4. Unzip rootfs to ./{dir}
5. Enter: umount {name}.img



Q:how make cpp?


A:Enter:g++ milroofs.cpp -o milrootfs


note:If you don’t want to make cpp, please go to the release download.
