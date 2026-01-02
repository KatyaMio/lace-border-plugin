#pragma once  
#include <hyprland/src/render/decorations/IHyprWindowDecoration.hpp>  
#include <hyprland/src/render/Texture.hpp>
  
class CLaceBorderDecoration : public IHyprWindowDecoration {  
public:  
    CLaceBorderDecoration(PHLWINDOW pWindow);  
    virtual ~CLaceBorderDecoration() = default;  
      
    virtual SDecorationPositioningInfo getPositioningInfo() override;  
    virtual void onPositioningReply(const SDecorationPositioningReply& reply) override;  
    virtual void draw(PHLMONITOR pMonitor, float const& a) override;  
    virtual eDecorationType getDecorationType() override;  
    virtual void updateWindow(PHLWINDOW) override;  
    virtual void damageEntire() override;  
    virtual eDecorationLayer getDecorationLayer() override;  
    virtual uint64_t getDecorationFlags() override;  
    virtual std::string getDisplayName() override;  
  
private:  
    SBoxExtents m_extents;  
    PHLWINDOWREF m_window;  
    CBox m_assignedGeometry = {0};  
    SP<CTexture> m_laceTexture;  
      
    void loadLaceTexture();  
    CBox assignedBoxGlobal();  
};
