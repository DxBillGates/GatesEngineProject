#pragma once
//COMオブジェクトを解放しnullptrに設定するマクロ
#define COM_RELEASE(p){if((p))p->Release();(p)=nullptr;}