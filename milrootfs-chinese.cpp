#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

class MilRootFS {
public:
    MilRootFS() {}

    // 掛載映像檔作為根檔案系統
    bool mountRootFS(const std::string& imgFile, const std::string& mountPoint) {
        std::cout << "掛載映像檔 " << imgFile << " 到 " << mountPoint << " ..." << std::endl;
        
        // 使用 mount 命令掛載映像檔
        std::string mountCommand = "sudo mount -o loop " + imgFile + " " + mountPoint;
        int result = system(mountCommand.c_str());

        // 檢查掛載是否成功
        if (result != 0) {
            std::cerr << "掛載映像檔失敗！" << std::endl;
            return false;
        }
        return true;
    }

    // 登入根檔案系統（這裡模擬進入一個 shell）
    void loginToRootFS(const std::string& mountPoint) {
        std::cout << "根檔案系統掛載成功，進入登入過程..." << std::endl;
        
        // 模擬進入根檔案系統的 shell
        std::string chrootCommand = "sudo chroot " + mountPoint + " /bin/bash";
        system(chrootCommand.c_str());  // 使用 chroot 進入新的根檔案系統並啟動 bash
    }

    // 卸載根檔案系統
    bool unmountRootFS(const std::string& mountPoint) {
        std::cout << "卸載根檔案系統 " << mountPoint << " ..." << std::endl;

        // 使用 umount 命令卸載掛載點
        std::string unmountCommand = "sudo umount " + mountPoint;
        int result = system(unmountCommand.c_str());

        // 檢查卸載是否成功
        if (result != 0) {
            std::cerr << "卸載根檔案系統失敗！" << std::endl;
            return false;
        }
        return true;
    }

    // 顯示幫助訊息
    void showHelp() {
        std::cout << "使用方法：" << std::endl;
        std::cout << "milrootfs mount <imgFile> <mountPoint> - 掛載映像檔到指定目錄" << std::endl;
        std::cout << "milrootfs login <mountPoint>           - 進入掛載的根檔案系統並啟動登入" << std::endl;
        std::cout << "milrootfs unmount <mountPoint>         - 卸載根檔案系統" << std::endl;
        std::cout << "milrootfs help                        - 顯示此幫助訊息" << std::endl;
    }
};

int main(int argc, char* argv[]) {
    MilRootFS milrootfs;

    if (argc < 2) {
        std::cerr << "錯誤：未提供足夠的參數！" << std::endl;
        milrootfs.showHelp();
        return 1;
    }

    std::string command = argv[1];

    if (command == "mount") {
        if (argc != 4) {
            std::cerr << "錯誤：用法應為 milrootfs mount <imgFile> <mountPoint>" << std::endl;
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
            std::cerr << "錯誤：用法應為 milrootfs login <mountPoint>" << std::endl;
            return 1;
        }
        std::string mountPoint = argv[2];
        milrootfs.loginToRootFS(mountPoint);
    }
    else if (command == "unmount") {
        if (argc != 3) {
            std::cerr << "錯誤：用法應為 milrootfs unmount <mountPoint>" << std::endl;
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
        std::cerr << "錯誤：未知的命令 " << command << std::endl;
        milrootfs.showHelp();
        return 1;
    }

    return 0;
}

