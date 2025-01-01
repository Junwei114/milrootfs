#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

class MilRootFS {
public:
    MilRootFS() {}

    bool mountRootFS(const std::string& imgFile, const std::string& mountPoint) {
        std::cout << "mount image" << imgFile << " to " << mountPoint << " ..." << std::endl;
        
        std::string mountCommand = "sudo mount -o loop " + imgFile + " " + mountPoint;
        int result = system(mountCommand.c_str());

        if (result != 0) {
            std::cerr << "Failed to mount image file！" << std::endl;
            return false;
        }
        return true;
    }

    void loginToRootFS(const std::string& mountPoint) {
        std::cout << "Root file system mounted successfully" << std::endl;
        
        std::string chrootCommand = "sudo chroot " + mountPoint + " /bin/bash";
        system(chrootCommand.c_str());  
    }

    bool unmountRootFS(const std::string& mountPoint) {
        std::cout << "Uninstall the root file system" << mountPoint << " ..." << std::endl;

        std::string unmountCommand = "sudo umount " + mountPoint;
        int result = system(unmountCommand.c_str());

        if (result != 0) {
            std::cerr << "Unmounting root file system failed！" << std::endl;
            return false;
        }
        return true;
    }

  void showHelp() {
        std::cout << "using:" << std::endl;
        std::cout << "milrootfs mount <imgFile> <mountPoint> - Mount the image file to the specified directory" << std::endl;
        std::cout << "milrootfs login <mountPoint> - Enter the mounted root file system and initiate login" << std::endl;
        std::cout << "milrootfs unmount <mountPoint> - Unmount the root file system" << std::endl;
        std::cout << "milrootfs help - display this help message" << std::endl;
  }
};

int main(int argc, char* argv[]) {
    MilRootFS milrootfs;

    if (argc < 2) {
        std::cerr << "Error: Not enough arguments provided！" << std::endl;
        milrootfs.showHelp();
        return 1;
    }

    std::string command = argv[1];

    if (command == "mount") {
        if (argc != 4) {
            std::cerr << "Error: Usage should be milrootfs mount <imgFile> <mountPoint>" << std::endl;
            return 1;
        }
        std::string imgFile = argv[2];
        std::string mountPoint = argv[3];
        
        if (!milrootfs.mountRootFS(imgFile, mountPoint)) {
            return 1;
        }
    }
    else if (command == "login") {
        if (argc != 3) {
            std::cerr << Error: Usage should be milrootfs login <mountPoint>" << std::endl;
            return 1;
        }
        std::string mountPoint = argv[2];
        milrootfs.loginToRootFS(mountPoint);
    }
    else if (command == "unmount") {
        if (argc != 3) {
            std::cerr << "Error: Usage should be milrootfs unmount <mountPoint>" << std::endl;
            return 1;
        }
        std::string mountPoint = argv[2];
        
        if (!milrootfs.unmountRootFS(mountPoint)) {
            return 1;
        }
    }
    else if (command == "help") {
        milrootfs.showHelp();
    }
    else {
        std::cerr << "Error: unknown command " << command << std::endl;
        milrootfs.showHelp();
        return 1;
    }

    return 0;
}
