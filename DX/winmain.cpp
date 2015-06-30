//The code is based on Matt Guerette DirectX 11 Tutorial
//URL: https://goo.gl/EAGuQ3

#include <windows.h>
#include "DXApp.h"

class TestApp : public DXApp
{
public:
    TestApp( HINSTANCE hInstance );
    ~TestApp();

    bool Init() override;
    void Update( float dt ) override;
    void Render( float dt ) override;


};

TestApp::TestApp( HINSTANCE hInstance ) : DXApp( hInstance )
{

}

TestApp::~TestApp()
{

}

bool TestApp::Init()
{
    return DXApp::Init( );
}

void TestApp::Update( float dt )
{

}

void TestApp::Render( float dt )
{
    m_pImmediateContext->ClearRenderTargetView( m_pRenderTargetView, DirectX::Colors::SkyBlue );
    m_pSwapChain->Present(0, 0);
}

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
    //MessageBox( NULL, "Test", "Hello, World", NULL );

    TestApp tApp( hInstance );
    if( !tApp.Init() ) return 1;

    return tApp.Run();
}