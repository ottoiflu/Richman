// src/main.c - Rich 大富翁程序主入口（TDD框架版）
#include "common.h"

int main(int argc, char* argv[]) {
    // 初始化命令注册系统
    command_registry_init();
    
    // 初始化游戏状态
    game_init(get_game_state());
    
    // 初始化各模块并注册命令
    player_module_init();  // 张弛的Player模块
    
    // 处理命令行参数
    CommandResult result = process_cli_command(argc, argv);
    
    switch (result) {
        case CMD_SUCCESS:
            // 没有CLI命令，进入交互模式
            process_interactive_mode();
            break;
        case CMD_EXIT:
            // CLI命令执行完毕，正常退出
            break;
        case CMD_ERROR:
        case CMD_UNKNOWN:
            // 错误情况，返回错误码
            return 1;
    }
    
    return 0;
}