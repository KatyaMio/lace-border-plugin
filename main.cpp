#include "LaceBorderDecoration.hpp"  
#include <hyprland/src/plugins/PluginAPI.hpp>  
  
extern "C" EXPORT std::string pluginAPIVersion() {  
    return HYPRLAND_API_VERSION;  
}  
  
extern "C" EXPORT PLUGIN_DESCRIPTION_INFO pluginInit(HANDLE handle) {  
    // Register config values for image path, border size, etc.  
    HyprlandAPI::addConfigValue(handle, "plugin:lace_border:image_path", Hyprlang::STRING{"lace_pattern.png"});  
    HyprlandAPI::addConfigValue(handle, "plugin:lace_border:border_width", Hyprlang::INT{5});  
      
    return {"Lace Border", "Renders lace pattern image as window border", "YourName", "1.0"};  
}  
  
extern "C" EXPORT void pluginExit() {  
    // Cleanup if needed  
}
