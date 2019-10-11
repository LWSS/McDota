#pragma once

#include "types.h"

// xref "CPanel2D::BSetProperty" to BSetProperty (libclient)
namespace panorama
{
    class CPanel2D
    {
    public:
        virtual panorama::IUIPanel* UIPanel(void) = 0;
        virtual void OnDeletePanel(void) = 0;
        virtual panorama::CPanoramaSymbol GetPanelType(void) = 0;
        virtual void Paint(void) = 0;
        virtual void sub_4554560() = 0;
        virtual void sub_4554570() = 0;
        virtual void OnContentSizeTraverse(float *, float *, float, float, bool) = 0;
        virtual void OnLayoutTraverse(float, float) = 0;
        virtual void OnKeyDown(panorama::KeyData_t const &) = 0;
        virtual void OnKeyUp(panorama::KeyData_t const &) = 0;
        virtual void OnKeyTyped(panorama::KeyData_t const &) = 0;
        virtual void OnGamePadDown(panorama::GamePadData_t const &) = 0;
        virtual void OnGamePadUp(panorama::GamePadData_t const &) = 0;
        virtual void OnGamePadAnalog(panorama::GamePadData_t const &) = 0;
        virtual void OnMouseButtonDown(panorama::MouseData_t const &) = 0;
        virtual void OnMouseButtonUp(panorama::MouseData_t const &) = 0;
        virtual void OnMouseButtonDoubleClick(panorama::MouseData_t const &) = 0;
        virtual void OnMouseButtonTripleClick(panorama::MouseData_t const &) = 0;
        virtual void OnMouseWheel(panorama::MouseData_t const &) = 0;
        virtual void OnMouseMove(float, float) = 0;
        virtual void OnClick(panorama::IUIPanel *panel, panorama::MouseData_t const &) = 0;
        virtual void sub_23BF260() = 0;
        virtual bool BIsClientPanelEvent(panorama::CPanoramaSymbol) = 0;
        virtual bool sub_3BC94E0() = 0;
        virtual void sub_4555580() = 0;
        virtual bool BSetProperty(panorama::CPanoramaSymbol, const char *) = 0;
        virtual bool BIsDelayedProperty(panorama::CPanoramaSymbol) = 0;
        virtual void OnBeforeChildrenChanged(void) = 0;
        virtual void OnRemoveChild(panorama::IUIPanel* child) = 0;
        virtual void OnAfterChildrenChanged(void) = 0;
        virtual void OnInitializedFromLayout(void) = 0;
        virtual void OnStylesChanged(void) = 0;
        virtual void OnChildStylesChanged(void) = 0;
        virtual void OnVisibilityChanged(void) = 0;
        virtual void OnSetFocusToNextPanel(int, panorama::EFocusMoveDirection, bool, float, float, float, float ,float) = 0;
        virtual void* GetLocalizationParent(void) = 0;
        virtual bool BRequiresContentClipLayer(void) = 0;
        virtual void OnCallBeforeStyleAndLayout(void) = 0;
        virtual void OnPanelEventSet(panorama::CPanoramaSymbol event) = 0;
        virtual void* GetMouseCursor(void) = 0;
        virtual void OnUIScaleFactorChanged(float scaleFactor) = 0;
        virtual void SetupJavascriptObjectTemplate(void) = 0;
        virtual void CreateNewVerticalScrollBar(float) = 0;
        virtual void CreateNewHorizontalScrollBar(float) = 0;
        virtual void HideTooltip(void) = 0;
        virtual void GetDefaultInputFocus(void) = 0;
        virtual void GetPositionWithinAncestor(panorama::CPanel2D* ancestor, float *x, float *y) = 0;
        virtual void sub_23BF380() = 0;
        virtual void sub_23BF390() = 0; // These are in these 6 somewhere
        virtual void sub_23BF3A0() = 0; // panorama::CPanel2D::BCanCustomScrollUp(void)
        virtual void sub_23BF3B0() = 0; // panorama::CPanel2D::BCanCustomScrollDown(void)
        virtual void sub_23BF3C0() = 0; // panorama::CPanel2D::BCanCustomScrollLeft(void)
        virtual void sub_23BF3D0() = 0; // panorama::CPanel2D::BCanCustomScrollRight(void)
        virtual void UnloadImages(void) = 0;
        virtual void ReloadImages(void) = 0;
        virtual void DESTROY1() = 0;
        virtual void DESTROY2() = 0;
        virtual void GetContextUIBounds(float *x1, float *y1, float *x2, float *y2) = 0;
        virtual void ScrollToXPercent(float value) = 0;
        virtual void ScrollToYPercent(float value) = 0;
        virtual void OnMoveUp(int) = 0;
        virtual void OnMoveDown(int) = 0;
        virtual void OnMoveLeft(int) = 0;
        virtual void OnMoveRight(int) = 0;
        virtual void OnTabForward(int) = 0;
        virtual void OnTabBackward(int) = 0;
        virtual void sub_23BF270() = 0;
        virtual void sub_23BF290() = 0;
        virtual void sub_4554580() = 0;
        virtual bool IsClonable() = 0;
        virtual panorama::CPanel2D* Clone(void) = 0;
        virtual void ReSortChild(bool (*)(panorama::IUIPanelClient * const&,panorama::IUIPanelClient * const&),panorama::CPanel2D*) = 0;
        virtual bool HasBeenLayedOut(void) = 0;
        virtual void* AccessRenderingEngine(void) = 0;
        virtual void sub_23BF420() = 0;
        virtual void InitClonedPanel(panorama::CPanel2D* ) = 0;
        virtual void AddDisabledFlagToChildren(void) = 0;
        virtual void RemoveDisabledFlagFromChildren(void) = 0;
        virtual void FireGameEvent(void* IGameEvent) = 0;
        virtual void OnDOTAGameUIStateChange(int DotaGameUIStateOld, int DotaGameUIStateNew) = 0;
    };
}