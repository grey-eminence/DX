//The code is based on Matt Guerette DirectX 11 Tutorial
//URL: https://goo.gl/EAGuQ3

#pragma once
#include <d3d11.h>
#include <DirectXColors.h>

#pragma comment(lib, "d3d11.lib")

namespace Memory
{
    template <class T> void SafeDelete( T& t )
    {
        if( t )
        {
            delete t;
            t = nullptr;
        }
    }

    template <class T> void SafeDeleteArr( T& t )
    {
        if( t )
        {
            delete[] t;
            t = nullptr;
        }
    }

    template <class T> void SafeRelease( T& t )
    {
        if( t )
        {
            t->Release();
            t = nullptr;
        }
    }
}