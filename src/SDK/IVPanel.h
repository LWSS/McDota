#pragma once

#include "IAppSystem.h"
#include "IVGuiPaintSurface.h"


enum RenderMode_t : unsigned char
{
	kRenderNormal = 0,
	kRenderTransColor,
	kRenderTransTexture,
	kRenderGlow,
	kRenderTransAlpha,
	kRenderTransAdd,
	kRenderEnvironmental,
	kRenderTransAddFrameBlend,
	kRenderTransAlphaAdd,
	kRenderWorldGlow,
	kRenderNone,
	kRenderDevVisualizer,
	kRenderModeCount
};

enum RenderFx_t : unsigned char
{
	kRenderFxNone = 0,
	kRenderFxPulseSlow,
	kRenderFxPulseFast,
	kRenderFxPulseSlowWide,
	kRenderFxPulseFastWide,
	kRenderFxFadeSlow,
	kRenderFxFadeFast,
	kRenderFxSolidSlow,
	kRenderFxSolidFast,
	kRenderFxStrobeSlow,
	kRenderFxStrobeFast,
	kRenderFxStrobeFaster,
	kRenderFxFlickerSlow,
	kRenderFxFlickerFast,
	kRenderFxNoDissipation,
	kRenderFxFadeOut,
	kRenderFxFadeIn,
	kRenderFxPulseFastWider,
	kRenderFxGlowShell,
	kRenderFxMax,
};

// Xref "ShutdownRequest" to CVGui::ShutdownMessage() - xref it back to vtable.
// Go down 1 vfunc, this is CVGui::AllocPanel()
// AllocPanel() will make a VPanel. First Function after operator new() is VPanel::VPanel() (vtable is inside)
class IVPanel : IAppSystem
{
public:
	virtual void Init(VPANEL panel, void *clientPanel);
	virtual void SetPos(VPANEL panel,int x,int y);
	virtual void GetPos(VPANEL panel,int &x,int &y);
	virtual void SetSize(VPANEL panel,int wide,int tall);
	virtual void SetSizeNoCallback(VPANEL panel,int wide, int tall);
	virtual void GetSize(VPANEL panel,int &wide,int &tall);
	virtual void SetMinimumSize(VPANEL panel,int wide, int tall);
	virtual void GetMinimumSize(VPANEL panel,int &wide, int &tall);
	virtual void SetZPos(VPANEL panel,int z);
	virtual int GetZPos(VPANEL panel);

	virtual void GetAbsPos(VPANEL panel,int &x,int &y);
	virtual void GetClipRect(VPANEL panel,int &x0,int &y0,int &x1 ,int &y1);
	virtual void NarrowClipRect(VPANEL panel,int &x0,int &y0,int &x1,int &y1);
	virtual void ExpandClipRect(VPANEL panel,int &x0,int &y0,int &x1,int &y1);
	virtual void SetInset(VPANEL panel,int x0,int y0,int x1,int y1);
	virtual void GetInset(VPANEL panel,int &x0,int &y0,int &x1,int &y1);

	virtual void SetVisible(VPANEL panel,bool visible);
	virtual bool IsVisible(VPANEL panel);
	virtual void SetParent(VPANEL panel,VPANEL newParent);
	virtual int GetChildCount(VPANEL panel);
	virtual VPANEL GetChild(VPANEL panel,int index);
	virtual void GetChildren(VPANEL panel); // returns a CUtlVector< VPANEL > &GetChildre
	virtual VPANEL GetParent(VPANEL panel);
	virtual void MoveToFront(VPANEL panel);
	virtual void MoveToBack(VPANEL panel);
	virtual bool HasParent(VPANEL panel,VPANEL potentialParent);
	virtual bool IsPopup(VPANEL panel);
	virtual void SetPopup(VPANEL panel,bool popup);
	virtual bool IsFullyVisible(VPANEL panel);

    // gets the scheme this panel uses
	virtual void GetScheme(VPANEL panel); // returns HScheme
	virtual void GetLayoutFile(VPANEL panel);
    // gets whether or not this panel should scale with screen resolution
	virtual bool IsProportional(VPANEL panel);
    // returns true if auto-deletion flag is set
	virtual bool IsAutoDeleteSet(VPANEL panel);
    // deletes the Panel * associated with the vpanel
	virtual void DeletePanel(VPANEL panel);

	virtual void SetKeyBoardInputEnabled(VPANEL panel,bool enabled);
	virtual void SetMouseInputEnabled(VPANEL panel,bool enabled);
	virtual bool IsKeyBoardInputEnabled(VPANEL panel);
	virtual bool IsMouseInputEnabled(VPANEL panel);

    // calculates the panels current position within the hierarchy
	virtual void Solve(VPANEL panel);

    // gets names of the object (for debugging purposes)
	virtual const char* GetName(VPANEL panel);
	virtual const char* GetClassName(VPANEL panel);

    // delivers a message to the panel
	virtual void SendMessage(VPANEL panel,void* KeyValues,VPANEL panel2);

    // these pass through to the IClientPanel
	virtual void Think(VPANEL panel);
	virtual void PerformApplySchemeSettings(VPANEL panel);
	virtual void PaintTraverse(IVGuiPaintSurface* surface, VPANEL panel, bool force_repaint, bool allow_force);
	virtual void Repaint(VPANEL panel);
	virtual VPANEL IsWithinTraverse(VPANEL panel,int x,int y,bool traversePopups);
	virtual void OnChildAdded(VPANEL panel,VPANEL panel2);
	virtual void OnSizeChanged(VPANEL panel,int newWide,int newTall);


	virtual void InternalFocusChanged(VPANEL panel,bool lost);
	virtual bool RequestInfo(VPANEL panel,void * KeyValues);
	virtual void RequestFocus(VPANEL panel,int direction = 0);
	virtual bool RequestFocusPrev(VPANEL panel,VPANEL existingPanel);
	virtual bool RequestFocusNext(VPANEL panel,VPANEL existingPanel);
	virtual VPANEL GetCurrentKeyFocus(VPANEL panel);
	virtual int GetTabPosition(VPANEL panel);

    // used by ISurface to store platform-specific data
	virtual void Plat(VPANEL panel);
	virtual void SetPlat(VPANEL panel, void* vgui__SurfacePlat);

    // returns a pointer to the vgui controls baseclass Panel *
    // destinationModule needs to be passed in to verify that the returned Panel * is from the same module
    // it must be from the same module since Panel * vtbl may be different in each module
	virtual void* GetPanel(VPANEL panel,char const* destinationModule);

	virtual bool IsEnabled(VPANEL panel);
	virtual void SetEnabled(VPANEL panel,bool enabled);

	virtual bool IsTopmostPopup(VPANEL panel);
	virtual void SetTopmostPopup(VPANEL panel,bool topMost);

	virtual void SetMessageContextId(VPANEL panel,int msgContextID);
	virtual int GetMessageContextId(VPANEL panel);
	virtual void GetUnpackStructure(VPANEL panel);
	virtual void SetSiblingPin(VPANEL panel,VPANEL panel2,unsigned char unk,unsigned char unk2);
	virtual void MoveBehindSibling(VPANEL panel,VPANEL sibling);
	virtual void Client(VPANEL panel);
	virtual const char* GetModuleName(VPANEL panel);
};