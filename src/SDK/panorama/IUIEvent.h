#pragma once
#include "IUIPanel.h"
//#include <v8.h>
namespace panorama
{
    class IUIEvent
    {
    public:
        virtual void DESTROY() = 0;
        virtual void DESTROY2() = 0;
        virtual panorama::PanelHandle_t* GetTargetPanel(void); // 0xC
        virtual void SetTargetPanel(IUIPanel const *);
        virtual CPanoramaSymbol BROKEN_GetEventType(void);
        virtual bool CanBubble(void);
        virtual void Dispatch(CUtlAbstractDelegate);
        virtual void Copy(void);
        virtual void GetJavaScriptArgs(int *);//,v8::Handle<v8::Value> value);

        CPanoramaSymbol GetEventType(void)
        {
            return *( CPanoramaSymbol* )( ((uintptr_t)this) + 0xA );
        }
    };
}