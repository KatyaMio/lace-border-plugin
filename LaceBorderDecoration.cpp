#include "LaceBorderDecoration.hpp"  
#include <../hyprland/src/render/Texture.hpp>  
#include <../hyprland/src/config/ConfigValue.hpp>  
#include <../hyprland/src/plugins/PluginAPI.hpp>  
#include <../hyprland/src/render/OpenGL.hpp>

static HANDLE PHANDLE = nullptr;  
  
CLaceBorderDecoration::CLaceBorderDecoration(PHLWINDOW pWindow)   
    : IHyprWindowDecoration(pWindow), m_window(pWindow) {  
    loadLaceTexture();  
}  
  
void CLaceBorderDecoration::loadLaceTexture() {  
    static auto PIMAGEPATH = HyprlandAPI::getConfigValue(PHANDLE, "plugin:lace_border:image_path");  
    const std::string imagePath = std::any_cast<Hyprlang::STRING>(PIMAGEPATH->getValue());        
   
    // Use Hyprland's asset loading system  
    m_laceTexture = g_pHyprOpenGL->loadAsset(imagePath);  
      
    if (!m_laceTexture || !m_laceTexture->m_texID) {  
        // Fallback to a simple colored texture if loading fails  
        m_laceTexture = makeShared<CTexture>();  
        m_laceTexture->allocate();  
        m_laceTexture->m_size = {64, 64};  
          
        // Create a simple pattern as fallback  
        std::vector<uint32_t> pixels(64 * 64, 0xFF6B6BFF); // Red color  
        m_laceTexture->bind();  
        m_laceTexture->setTexParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
        m_laceTexture->setTexParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());  
    }  
}

SDecorationPositioningInfo CLaceBorderDecoration::getPositioningInfo() {  
    static auto PBORDERWIDTH = HyprlandAPI::getConfigValue(PHANDLE, "plugin:lace_border:border_width");  
    const int borderSize = std::any_cast<Hyprlang::INT>(PBORDERWIDTH->getValue());        
    m_extents = {{borderSize, borderSize}, {borderSize, borderSize}};  
      
    SDecorationPositioningInfo info;  
    info.policy = DECORATION_POSITION_STICKY;  
    info.desiredExtents = m_extents;  
    info.reserved = true;  
    info.edges = DECORATION_EDGE_BOTTOM | DECORATION_EDGE_LEFT |   
                 DECORATION_EDGE_RIGHT | DECORATION_EDGE_TOP;  
    return info;  
}  
  
void CLaceBorderDecoration::draw(PHLMONITOR pMonitor, float const& a) {  
    if (!m_laceTexture || !m_laceTexture->m_texID)  
        return;  
          
    const auto borderBox = assignedBoxGlobal();  
CHyprOpenGLImpl::STextureRenderData renderData;
    renderData.a = a;  
    renderData.damage = &g_pHyprOpenGL->m_renderData.damage;  
      
    g_pHyprOpenGL->renderTexture(m_laceTexture, borderBox, renderData);      
}
