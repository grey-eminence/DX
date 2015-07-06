//The code is based on Matt Guerette DirectX 11 Tutorial
//URL: https://goo.gl/EAGuQ3

#include <windows.h>
#include "DXApp.h"
#include "dxerr.h"
#include <d3dcompiler.h>

#pragma comment(lib,"d3dcompiler.lib")

using namespace std;
#ifdef _DEBUG
#ifndef HR
#define HR(x)\
{\
    HRESULT hr = x; \
if( FAILED( hr ) )\
{\
    DXTraceW( __FILEW__, __LINE__, hr, L#x, TRUE ); \
}\
}
#endif
#ifndef HR
#define HR(x) x;
#endif
#endif

struct MyVertex
{
    float Position[2];
    unsigned Color;
};

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
    return DXApp::Init();
}

void TestApp::Update( float dt )
{

}

void TestApp::Render( float dt )
{
    m_pImmediateContext->ClearRenderTargetView( m_pRenderTargetView, DirectX::Colors::SkyBlue );


    MyVertex myVertices[] = {
        { 0.0f, 0.5f, 0xFF0000FF },
        { 0.5f, -0.5f, 0xFF00FF00 },
        { -0.5f, -0.5f, 0xFFFF0000 },
    };

    D3D11_BUFFER_DESC bufDesc;
    ZeroMemory( &bufDesc, sizeof( bufDesc ) );
    bufDesc.ByteWidth = sizeof( MyVertex ) * _countof( myVertices );
    bufDesc.Usage = D3D11_USAGE_IMMUTABLE;
    bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA bufData;
    ZeroMemory( &bufData, sizeof( bufData ) );
    bufData.pSysMem = myVertices;

    ID3D11Buffer *g_VertexBuffer;
    ID3D10Blob *g_VertexShaderCode, *g_PixelShaderCode;
    ID3D11VertexShader *g_VertexShader;
    ID3D11PixelShader *g_PixelShader;
    ID3D11InputLayout *g_InputLayout;

    HR( m_pDevice->CreateBuffer( &bufDesc, &bufData, &g_VertexBuffer ) );

    ID3D10Blob * err = NULL;

    D3DCompileFromFile( L"Shaders.fx", nullptr, nullptr, "VSMain", "vs_4_0", 0, 0, &g_VertexShaderCode, &err );   
    m_pDevice->CreateVertexShader( g_VertexShaderCode->GetBufferPointer( ), g_VertexShaderCode->GetBufferSize( ), 0, &g_VertexShader );
    if( err ) err->Release( );
 
    D3DCompileFromFile( L"Shaders.fx", nullptr, nullptr, "PSMain", "ps_4_0", 0, 0, &g_PixelShaderCode, &err );
    m_pDevice->CreatePixelShader( g_PixelShaderCode->GetBufferPointer( ), g_PixelShaderCode->GetBufferSize( ), 0, &g_PixelShader );
    if( err ) err->Release();

    D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    m_pDevice->CreateInputLayout( inputDesc, _countof( inputDesc ), g_VertexShaderCode->GetBufferPointer( ), g_VertexShaderCode->GetBufferSize( ), &g_InputLayout );


    UINT vbStride = sizeof( MyVertex ), vbOffset = 0;
    m_pImmediateContext->IASetVertexBuffers( 0, 1, &g_VertexBuffer, &vbStride, &vbOffset );
    m_pImmediateContext->IASetInputLayout( g_InputLayout );
    m_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
    m_pImmediateContext->VSSetShader( g_VertexShader, 0, 0 );
    m_pImmediateContext->PSSetShader( g_PixelShader, 0, 0 );

    m_pImmediateContext->Draw( 3, 0 );

    HR( m_pSwapChain->Present( 0, 0 ) );
}

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
    //MessageBox( NULL, "Test", "Hello, World", NULL );

    TestApp tApp( hInstance );
    if( !tApp.Init() ) return 1;

    return tApp.Run();
}