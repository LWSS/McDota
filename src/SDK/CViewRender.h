#pragma once

class CViewSetup;
struct SceneFogParams_t;

/* not sure if accurate for source2 */
struct vrect_t
{
    int				x,y,width,height;
    vrect_t			*pnext;
};

//xref "screenfademinsize" to the constructor of this class. The Vtable should be the first off_xxxxx pointer in the section.
// Warning: not at the top, the caller is inlined.
class CViewRender
{
public:
    // SETUP
    // Initialize view renderer
    virtual void Init(void);
    // Clear any systems between levels
	virtual void LevelInit(void);
	virtual void LevelShutdown(void);
    // Shutdown
	virtual void Shutdown(void);

    // RENDERING
    // Called right before simulation. It must setup the view model origins and angles here so
    // the correct attachment points can be used during simulation.
	virtual void OnRenderStart(void);
    virtual void unk();

    // Called to render the entire scene
	virtual void Render(vrect_t *);
    // Called to render just a particular setup ( for timerefresh and envmap creation )
	virtual void RenderView(CViewSetup const&,CViewSetup const&,int clearFlags,int whatToDraw); // 7
	virtual const CViewSetup* GetPlayerViewSetup(int CSplitScreenSlot);
	virtual void CullBox();//VectorAligned const&,VectorAligned const&,CSplitScreenSlot);
	virtual const CViewSetup* GetViewSetup(void);
	virtual void RestoreLastViewSetups(void);
	virtual void DisableVis(void);
	virtual void SetScreenOverlayMaterial();//CWeakHandle<InfoForResourceTypeIMaterial2>);
	virtual void* GetScreenOverlayMaterial(void);
	virtual void GetScreenFadeDistances(float *min,float *max); // 15
	virtual bool AllowScreenspaceFade(void);
	virtual void InitFadeData(void);
	virtual void ComputeViewSetupForPlayer(int CSplitScreenSlot);
	virtual void GetFogStart(SceneFogParams_t *);
	virtual void GetFogEnd(SceneFogParams_t *); // 20
	virtual float GetZNear(void);
	virtual float GetZFar(void);
	virtual float GetLODOverride(void);
    virtual bool unk2();
	virtual void DESTROY1();
	virtual void DESTROY2();
	virtual void Render2DEffectsPreHUD(CViewSetup const&);
	virtual void Render2DEffectsPostHUD(CViewSetup const&);
	virtual void ShouldForceNoVis(void);
	virtual void PreViewDrawScene(CViewSetup const&);
	virtual void PostViewDrawScene(CViewSetup const&);
	// couple more empty funcs..
};