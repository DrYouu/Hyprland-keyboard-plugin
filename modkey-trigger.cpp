
#include </home/yoel/Hyprland-keybord-plugin/Hyprland/src/plugins/PluginAPI.hpp>
#include </home/yoel/Hyprland-keybord-plugin/Hyprland/src/managers/HookSystemManager.hpp>
#include <linux/input-event-codes.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

static constexpr int MOD_KEY_CODE = KEY_LEFTMETA; // Super/Windows key
static bool modKeyPressed = false;

static std::string onPressCommand = "openrgb --profile mod_pressed";
static std::string onReleaseCommand = "openrgb --profile default";

void runCommand(const std::string& command) {
    if (command.empty()) return;
    pid_t pid = fork();
    if (pid == 0) {
        setsid();
        execl("/bin/sh", "sh", "-c", command.c_str(), (char*)nullptr);
        _exit(127);
    }
}

HOOK_CALLBACK(handleKeyEvent, void, SKeyEvent* event) {
    if (event->code != MOD_KEY_CODE)
        RETURN_HOOK();

    if (event->pressed && !modKeyPressed) {
        modKeyPressed = true;
        runCommand(onPressCommand);
    } else if (!event->pressed && modKeyPressed) {
        modKeyPressed = false;
        runCommand(onReleaseCommand);
    }

    RETURN_HOOK();
}

extern "C" PLUGIN_EXPORT void PLUGIN_INIT(HANDLE pluginHandle) {
    HyprlandAPI::registerPlugin(pluginHandle, "ModKey Trigger", "Runs commands on Super key press/release", "chatgpt", "1.0");
    HyprlandAPI::addHook(HOOK_TYPE::KEYBOARD_KEY, (void*)handleKeyEvent, pluginHandle);
}

extern "C" PLUGIN_EXPORT void PLUGIN_EXIT() {
    // Future cleanup logic if needed
}
