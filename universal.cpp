﻿//D3D11 base (w2s finder)
//compile in release mode

#pragma once
#include <Windows.h>
#include <vector>
#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h> //generateshader
#pragma comment(lib, "D3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib") //timeGetTime
#include "MinHook/include/MinHook.h" //detour x86&x64
#include "d3dx11tex.h"

//imgui
#include "ImGui\imgui.h"
#include "imgui\imgui_impl_win32.h"
#include "ImGui\imgui_impl_dx11.h"
#include <windows.h>

#define MOVE_MOUSE_DOWN(x)
#define WIN32_LEAN_AND_MEAN


ImDrawList* draw;
int red = 0;
int green = 255;
int blue = 255;
int segments = 50; 
bool invisible = false;
int
g_width,
g_height,
g_pid
;
bool particles = false;
ImFont* m_pFont;
int tabb = 1;

//dx sdk dir
//#include <d3d9.h>
//#include "DXSDK\d3dx9.h"
//#if defined _M_X64
//#pragma comment(lib, "DXSDK/x64/d3dx9.lib") 
//#elif defined _M_IX86
//#pragma comment(lib, "DXSDK/x86/d3dx9.lib")
//#endif

//DX Includes
#include <DirectXMath.h>

using namespace DirectX;


#pragma warning( disable : 4244 )





typedef HRESULT(__stdcall *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef HRESULT(__stdcall *D3D11ResizeBuffersHook) (IDXGISwapChain *pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

typedef void(__stdcall *D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
typedef void(__stdcall *D3D11DrawIndexedInstancedHook) (ID3D11DeviceContext* pContext, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation);
typedef void(__stdcall *D3D11DrawHook) (ID3D11DeviceContext* pContext, UINT VertexCount, UINT StartVertexLocation);

typedef void(__stdcall* D3D11PSSetShaderResourcesHook) (ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews);
typedef void(__stdcall *D3D11VSSetConstantBuffersHook) (ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers);


D3D11PresentHook phookD3D11Present = NULL;
D3D11ResizeBuffersHook phookD3D11ResizeBuffers = NULL;

D3D11DrawIndexedHook phookD3D11DrawIndexed = NULL;
D3D11DrawIndexedInstancedHook phookD3D11DrawIndexedInstanced = NULL;
D3D11DrawHook phookD3D11Draw = NULL;

D3D11PSSetShaderResourcesHook phookD3D11PSSetShaderResources = NULL;
D3D11VSSetConstantBuffersHook phookD3D11VSSetConstantBuffers = NULL;


ID3D11Device *pDevice = NULL;
ID3D11DeviceContext *pContext = NULL;

DWORD_PTR* pSwapChainVtable = NULL;
DWORD_PTR* pContextVTable = NULL;
DWORD_PTR* pDeviceVTable = NULL;

bool radar = true;
bool rect_radar = false;
float radar_position_x{ 84.494f };
float radar_position_y{ 77.841f };
float radar_size{ 150.f };
float RadarDistance = { 700.f };

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <filesystem>
#include <Windows.h>
#include <vector>

#include <d3d11.h>
#include <dxgi.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include <D3Dcompiler.h>
#pragma comment(lib, "D3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "winmm.lib")
#include <d3dcommon.h>
#include "MinHook/include/MinHook.h"
#include <DirectXMath.h>
#pragma warning( disable : 4244 )
#include <string>
#include <stdio.h>
#include <memoryapi.h>
#include <stdint.h>
#include <TlHelp32.h>
#include <Psapi.h>
#include <ntstatus.h>
#include <assert.h>
#include <cstdint>
#include <type_traits>
#include <winternl.h>
#include <map>
#include <wtypes.h>
#include <mutex>
#include <charconv>
#include <random>
#include "image.h"


typedef void(__stdcall* D3D11DrawIndexedInstancedIndirectHook) (ID3D11DeviceContext* pContext, ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs);



D3D11DrawIndexedInstancedIndirectHook phookD3D11DrawIndexedInstancedIndirect = NULL;
#define SAFE_RELEASE(x) if (x) { x->Release(); x = NULL; }

typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;

bool wireframe22 = false;
bool wireframered = true;

//create texture
ID3D11Texture2D* texGreen = nullptr;
ID3D11Texture2D* texRed = nullptr;

//create shaderresourcevew
ID3D11ShaderResourceView* texSRVg;
ID3D11ShaderResourceView* texSRVr;

//create samplerstate
ID3D11SamplerState* pSamplerState;

class Model {
private:
	UINT ModelStride;
	UINT ModelvscWidth;
	UINT ModelpscWidth;
	UINT ModelpsDescrFORMAT;
public:
	Model(UINT Stride, UINT vscWidth, UINT pscWidth, UINT psDescrFORMAT) { ModelStride = Stride; ModelvscWidth = vscWidth; ModelpscWidth = pscWidth; ModelpsDescrFORMAT = psDescrFORMAT; };

	bool IsModel(UINT Stride, UINT vscWidth, UINT pscWidth) { if (Stride == ModelStride && vscWidth == ModelvscWidth && pscWidth == ModelpscWidth)return true; else return false; };
	bool IsModel(UINT Stride, UINT vscWidth, UINT pscWidth, UINT psDescrFORMAT) { if (Stride == ModelStride && vscWidth == ModelvscWidth && pscWidth == ModelpscWidth && psDescrFORMAT == ModelpsDescrFORMAT)return true; else return false; };
};
float aimbotsmooth;

namespace Models {
	Model Sky(8, 11, 11, 95);

	Model Eyes(8, 60, 4, 71);
	Model Arms(8, 60, 4, 77);
	Model Body1(8, 60, 12, NULL);
	Model Body2(8, 60, 14, NULL);

	Model DroneWorldOverlay(8, 49, 3, NULL);
	Model Barricades(8, 49, 16, 0);
	Model WorldOverlay1(8, 49, 4, NULL);
	Model WorldOverlay2(8, 49, 12, NULL);
	Model WorldOverlay3(8, 49, 14, NULL);
	Model WorldOverlay4(8, 49, 49, NULL);
	Model Scope(8, 49, 49, 0);
}
bool fillesp;

#pragma comment(lib, "D3DX11.lib")
#include "main.h" //helper funcs
#include "imgui/imgui_internal.h"
#include "image.h"
using namespace ImGui;













//==========================================================================================================================

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
HWND window = NULL;
WNDPROC oWndProc;

void InitImGuiD3D11()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	ImGui::StyleColorsClassic();

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) {
		return true;
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

//==========================================================================================================================

HRESULT __stdcall hookD3D11ResizeBuffers(IDXGISwapChain *pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
{
	ImGui_ImplDX11_InvalidateDeviceObjects();
	if (nullptr != mainRenderTargetViewD3D11) { mainRenderTargetViewD3D11->Release(); mainRenderTargetViewD3D11 = nullptr; }

	HRESULT toReturn = phookD3D11ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

	ImGui_ImplDX11_CreateDeviceObjects();

	return phookD3D11ResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
}

//==========================================================================================================================
 float col12 { 0xff00ff00 };

bool ColorPicker3U32(const char* label, ImU32* color) {
	float col12[3];
	col12[0] = (float)((*color >> 0) & 0xFF) / 255.0f;
	col12[1] = (float)((*color >> 8) & 0xFF) / 255.0f;
	col12[2] = (float)((*color >> 16) & 0xFF) / 255.0f;

	bool result = ColorPicker3(label, col12);

	*color = ((ImU32)(col12[0] * 255.0f)) |
		((ImU32)(col12[1] * 255.0f) << 8) |
		((ImU32)(col12[2] * 255.0f) << 16);

	return result;
}

void __stdcall hookD3D11DrawIndexedInstancedIndirect(ID3D11DeviceContext* pContext, ID3D11Buffer* pBufferForArgs, UINT AlignedByteOffsetForArgs)
{
	ID3D11Buffer* veBuffer;
	UINT veWidth;
	UINT Stride;
	UINT veBufferOffset;
	D3D11_BUFFER_DESC veDesc;

	static ID3D11RasterizerState* PlayerState = NULL;
	static ID3D11RasterizerState* BarricadeState = NULL;

	ID3D11Device* Device;
	pContext->GetDevice(&Device);

	if (texRed == nullptr) {
		//sample state
		D3D11_SAMPLER_DESC sampDesc;
		ZeroMemory(&sampDesc, sizeof(sampDesc));
		sampDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		Device->CreateSamplerState(&sampDesc, &pSamplerState);

		//create green texture//0xffffffff white, 0xff00ff00 green, 0xffff0000 blue, 0xff0000ff red, 0x00000000
		DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; //format
		const float red =  0xff00ff00 ;
		D3D11_SUBRESOURCE_DATA initData = { &red, sizeof(uint32_t), 0 };
		D3D11_TEXTURE2D_DESC desc;
		memset(&desc, 0, sizeof(desc));
		desc.Width = desc.Height = desc.MipLevels = desc.ArraySize = 1;
		desc.Format = format;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;// D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;// D3D11_BIND_SHADER_RESOURCE;
		Device->CreateTexture2D(&desc, &initData, &texGreen);

		

		//create red texture
		static const uint32_t s_pixelr = 0xff0000ff;//0xffffffff white, 0xff00ff00 green, 0xffff0000 blue, 0xff0000ff red, 0x00000000
		D3D11_SUBRESOURCE_DATA initDatar = { &s_pixelr, sizeof(uint32_t), 0 };
		D3D11_TEXTURE2D_DESC descr;
		memset(&descr, 0, sizeof(descr));
		descr.Width = descr.Height = descr.MipLevels = descr.ArraySize = 1;
		descr.Format = format;
		descr.SampleDesc.Count = 1;
		descr.Usage = D3D11_USAGE_DEFAULT;// D3D11_USAGE_IMMUTABLE;
		descr.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;// D3D11_BIND_SHADER_RESOURCE;
		Device->CreateTexture2D(&descr, &initDatar, &texRed);

		//create green shaderresourceview
		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
		memset(&SRVDesc, 0, sizeof(SRVDesc));
		SRVDesc.Format = format;
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVDesc.Texture2D.MipLevels = 1;
		Device->CreateShaderResourceView(texGreen, &SRVDesc, &texSRVg);
		

		texGreen->Release();

		//create red shaderresourceview
		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDescr;
		memset(&SRVDescr, 0, sizeof(SRVDescr));
		SRVDescr.Format = format;
		SRVDescr.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		SRVDescr.Texture2D.MipLevels = 1;
		Device->CreateShaderResourceView(texRed, &SRVDescr, &texSRVr);


		texRed->Release();



	}

	

	//get models
	pContext->IAGetVertexBuffers(0, 1, &veBuffer, &Stride, &veBufferOffset);
	if (veBuffer) {
		veBuffer->GetDesc(&veDesc);
		veWidth = veDesc.ByteWidth;
	}
	if (NULL != veBuffer) {
		veBuffer->Release();
		veBuffer = NULL;
	}

	ID3D11Buffer* pscBuffer;
	UINT pscWidth;
	D3D11_BUFFER_DESC pscdesc;

	//get pscdesc.ByteWidth
	pContext->PSGetConstantBuffers(0, 1, &pscBuffer);
	if (pscBuffer) {
		pscBuffer->GetDesc(&pscdesc);
		pscWidth = pscdesc.ByteWidth;
	}
	if (NULL != pscBuffer) {
		pscBuffer->Release();
		pscBuffer = NULL;
	}

	ID3D11Buffer* vscBuffer;
	UINT vscWidth;
	D3D11_BUFFER_DESC vscdesc;

	pContext->VSGetConstantBuffers(0, 1, &vscBuffer);
	if (vscBuffer) {
		vscBuffer->GetDesc(&vscdesc);
		vscWidth = vscdesc.ByteWidth;
	}
	if (NULL != vscBuffer) {
		vscBuffer->Release();
		vscBuffer = NULL;
	}

	ID3D11ShaderResourceView* psShaderResourceView1;
	D3D11_SHADER_RESOURCE_VIEW_DESC psDescr;
	pContext->PSGetShaderResources(1, 1, &psShaderResourceView1);
	if (psShaderResourceView1)
	{
		psShaderResourceView1->GetDesc(&psDescr);
	}

	if (Models::Eyes.IsModel(Stride, (vscWidth / 10), (pscWidth / 10), psDescr.Format) ||
		Models::Arms.IsModel(Stride, (vscWidth / 10), (pscWidth / 10), psDescr.Format) ||
		Models::Body1.IsModel(Stride, (vscWidth / 10), (pscWidth / 10)) ||
		(Models::Body2.IsModel(Stride, (vscWidth / 10), (pscWidth / 10)) && (39 != psDescr.Format)))
	{

		if (texRed)
		{
			ID3D11RasterizerState* OldState;
			pContext->RSGetState(&OldState);
			if (PlayerState == NULL) {
				D3D11_RASTERIZER_DESC CustomStateDesc;
				OldState->GetDesc(&CustomStateDesc);
				//CustomStateDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
				CustomStateDesc.ScissorEnable = FALSE;
				CustomStateDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
				CustomStateDesc.DepthBias = INT_MAX;
				CustomStateDesc.DepthClipEnable = TRUE;



				Device->CreateRasterizerState(&CustomStateDesc, &PlayerState);
			}

			pContext->RSSetState(PlayerState);
			phookD3D11DrawIndexedInstancedIndirect(pContext, pBufferForArgs, AlignedByteOffsetForArgs);
			pContext->RSSetState(OldState);
			for (int x1 = 0; x1 <= 10; x1++)
			{
				pContext->PSSetShaderResources(x1, 1, &texSRVr);
			}
		}
		
		if (fillesp)
		{


			if (texRed)
			{
				ID3D11RasterizerState* OldState;
				pContext->RSGetState(&OldState);
				if (PlayerState == NULL) {
					D3D11_RASTERIZER_DESC CustomStateDesc;
					OldState->GetDesc(&CustomStateDesc);
					CustomStateDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
					CustomStateDesc.ScissorEnable = FALSE;
					//CustomStateDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
					CustomStateDesc.DepthBias = INT_MAX;
					CustomStateDesc.DepthClipEnable = TRUE;



					Device->CreateRasterizerState(&CustomStateDesc, &PlayerState);
				}

				pContext->RSSetState(PlayerState);
				phookD3D11DrawIndexedInstancedIndirect(pContext, pBufferForArgs, AlignedByteOffsetForArgs);
				pContext->RSSetState(OldState);
				for (int x1 = 0; x1 <= 10; x1++)
				{
					pContext->PSSetShaderResources(x1, 1, &texSRVr);
				}
			}




		}
	
		


		if (invisible)
		{

			
			texRed = false;
			texGreen = false;

			ID3D11RasterizerState* OldState;
			pContext->RSGetState(&OldState);
			if (PlayerState == NULL) {
				D3D11_RASTERIZER_DESC CustomStateDesc;
				OldState->GetDesc(&CustomStateDesc);
				CustomStateDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
				CustomStateDesc.ScissorEnable = TRUE;
				//CustomStateDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
				CustomStateDesc.DepthBias = INT_MIN;
				CustomStateDesc.DepthClipEnable = FALSE;




				Device->CreateRasterizerState(&CustomStateDesc, &PlayerState);

				
			}

			pContext->RSSetState(PlayerState);
			phookD3D11DrawIndexedInstancedIndirect(pContext, pBufferForArgs, AlignedByteOffsetForArgs);
			pContext->RSSetState(OldState);

				
			
		}




		

		
		



		



		if (visbcheck)
		{

			if (texGreen)
			{


				ID3D11RasterizerState* OldState;
				pContext->RSGetState(&OldState);
				if (PlayerState == NULL) {
					D3D11_RASTERIZER_DESC CustomStateDesc;
					OldState->GetDesc(&CustomStateDesc);
					//CustomStateDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
					CustomStateDesc.ScissorEnable = FALSE;
					//CustomStateDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
					CustomStateDesc.DepthBias = INT_MAX;
					CustomStateDesc.DepthClipEnable = TRUE;



					

					Device->CreateRasterizerState(&CustomStateDesc, &PlayerState);
					
					
					
				
				}

				pContext->RSSetState(PlayerState);
				phookD3D11DrawIndexedInstancedIndirect(pContext, pBufferForArgs, AlignedByteOffsetForArgs);
				pContext->RSSetState(OldState);
				for (int x1 = 0; x1 <= 10; x1++)
				{
					pContext->PSSetShaderResources(x1, 1, &texSRVg);
				}



			}
		}
		pContext->PSSetSamplers(0, 1, &pSamplerState);
		return phookD3D11DrawIndexedInstancedIndirect(pContext, pBufferForArgs, AlignedByteOffsetForArgs);

		return;
	}
	else if (Models::Barricades.IsModel(Stride, (vscWidth / 10), (pscWidth / 10))) {
		ID3D11RasterizerState* OldState;
		pContext->RSGetState(&OldState);
		if (BarricadeState == NULL) {
			D3D11_RASTERIZER_DESC CustomStateDesc;
			OldState->GetDesc(&CustomStateDesc);
			CustomStateDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
			CustomStateDesc.ScissorEnable = FALSE;
			CustomStateDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
			Device->CreateRasterizerState(&CustomStateDesc, &BarricadeState);
		}
		pContext->RSSetState(BarricadeState);
		phookD3D11DrawIndexedInstancedIndirect(pContext, pBufferForArgs, AlignedByteOffsetForArgs);
		pContext->RSSetState(OldState);
		return;
	}
	else if (Models::DroneWorldOverlay.IsModel(Stride, (vscWidth / 10), (pscWidth / 10)) ||
		Models::WorldOverlay1.IsModel(Stride, (vscWidth / 10), (pscWidth / 10)) ||
		Models::WorldOverlay2.IsModel(Stride, (vscWidth / 10), (pscWidth / 10)) ||
		Models::WorldOverlay3.IsModel(Stride, (vscWidth / 10), (pscWidth / 10)) ||
		(Models::WorldOverlay4.IsModel(Stride, (vscWidth / 10), (pscWidth / 10)) && !Models::Scope.IsModel(Stride, (vscWidth / 10), (pscWidth / 10), psDescr.Format)))
	{
		return;
	}

	return phookD3D11DrawIndexedInstancedIndirect(pContext, pBufferForArgs, AlignedByteOffsetForArgs);
}


HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!initonce)
	{
		if(SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetViewD3D11);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGuiD3D11();

			// Create depthstencil state
			D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
			depthStencilDesc.DepthEnable = TRUE;
			depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			depthStencilDesc.DepthFunc = D3D11_COMPARISON_ALWAYS;
			depthStencilDesc.StencilEnable = FALSE;
			depthStencilDesc.StencilReadMask = 0xF;
			depthStencilDesc.StencilWriteMask = 0xFF;
			// Stencil operations if pixel is front-facing
			depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			// Stencil operations if pixel is back-facing
			depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			pDevice->CreateDepthStencilState(&depthStencilDesc, &DepthStencilState_FALSE);

			GenerateTexture(0xffff0000, DXGI_FORMAT_R32G32B32A32_FLOAT); //DXGI_FORMAT_R32G32B32A32_FLOAT); //DXGI_FORMAT_R8G8B8A8_UNORM; 

			

			initonce = true;
		}
		else
			return phookD3D11Present(pSwapChain, SyncInterval, Flags); 
	}

	//create shaders
	if (texRed)
		GenerateShader(pDevice, &sGreen, 0.0f, 1.0f, 0.0f); //green

	


	


	//recreate rendertarget on reset
	if (mainRenderTargetViewD3D11 == NULL)
	{
		ID3D11Texture2D* pBackBuffer = NULL;
		pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetViewD3D11);
		pBackBuffer->Release();
	}

	//get imgui displaysize
	ImGuiIO io = ImGui::GetIO();
	ViewportWidth = io.DisplaySize.x;
	ViewportHeight = io.DisplaySize.y;
	ScreenCenterX = ViewportWidth / 2.0f;
	ScreenCenterY = ViewportHeight / 2.0f;

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		showmenu = !showmenu;
	}

	auto& Style = ImGui::GetStyle();

	Style.WindowPadding = ImVec2(20.000f, 20.000f);
	Style.WindowRounding = 10.000f;
	Style.ChildRounding = 10.000f;
	Style.FramePadding = ImVec2(20.000f, 5.000f);
	Style.FrameRounding = 8.000f;
	Style.FrameBorderSize = 0.000f;
	Style.TabBorderSize = 8.000f;

	Style.Colors[ImGuiCol_WindowBg] = ImColor(64, 64, 64);
	Style.Colors[ImGuiCol_Border] = ImColor(30, 30, 30, 255);
	Style.Colors[ImGuiCol_FrameBg] = ImColor(255, 255, 255);
	Style.Colors[ImGuiCol_FrameBgHovered] = ImColor(50, 50, 50, 255);
	Style.Colors[ImGuiCol_FrameBgActive] = ImColor(90, 90, 90, 255);
	Style.Colors[ImGuiCol_CheckMark] = ImColor(89, 3, 247, 255);
	Style.Colors[ImGuiCol_SliderGrab] = ImColor(89, 3, 247, 255);
	Style.Colors[ImGuiCol_SliderGrabActive] = ImColor(89, 3, 247, 255);
	Style.Colors[ImGuiCol_Button] = ImColor(50, 50, 50, 255);
	Style.Colors[ImGuiCol_ButtonHovered] = ImColor(70, 70, 70, 255);
	Style.Colors[ImGuiCol_ButtonActive] = ImColor(90, 90, 90, 255);
	Style.Colors[ImGuiCol_Separator] = ImColor(89, 3, 247, 255);


	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();



	if (showmenu) {



		
		

		if (particles)
		{
			static float f = 0.2f;
			static int counter = 0;
			int screenSize = 1920 / 1080;


			//things you need for the background part
			ImGuiStyle& style = ImGui::GetStyle();

			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::SetNextWindowSize(ImVec2(3000, 3000));
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.5f));
			ImGui::Begin("##bg", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoTitleBar);
			{
				//proper draw call
				draw = ImGui::GetWindowDrawList();

				ImVec2 screenSize = ImGui::GetIO().DisplaySize;
				ImGui::Particles(draw, screenSize); // it's important to define this in imgui_widgets.cpp otherwise it wouldn't work properly

			}ImGui::End();
			ImGui::PopStyleColor();
		}

		


		//background part end
		ImGuiStyle& style = ImGui::GetStyle();

		style.WindowRounding = 1;
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(ImColor(31, 31, 31, 255)));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.1f, 0.1f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.1f, 0.1f, 0.1f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.118f, 0.118f, 0.118f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.118f, 0.118f, 0.118f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.118f, 0.118f, 0.118f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(ImColor(red, green, blue)));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(24, 24, 24, 255)));
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(ImColor(red, green, blue)));
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(ImColor(red, green, blue)));








		ImGui::SetNextWindowSize(ImVec2(650, 450.000f), ImGuiCond_Once);
		ImGui::Begin("your name", NULL, 11);
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(255, 0, 24, 0)));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(255, 0, 24, 255)));

		//ImGui::Text("Flux [INSERT]");
		ImGui::SameLine();
		ImGui::SetCursorPosX(625);
		ImGui::SetCursorPosY(5);
		if (ImGui::Button("", ImVec2(20, 20)))
		{
			ExitProcess(0);
		}
		ImGui::PopStyleColor(2);
		ImGui::SetCursorPos(ImVec2(0, 30));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(ImColor(27, 27, 27, 255)));
		ImGui::BeginChild("##Undertitlebar", ImVec2(650, 415), false);
		ImGui::PopStyleColor();
		ImGui::SetCursorPos(ImVec2(0, 0));
		ImGui::BeginChild("##categories", ImVec2(170, 405), false);

		if (ImGui::Button("Aimbot", ImVec2(165, 40)))
		{
			tabb = 1;
		}

		if (ImGui::Button("Visuals", ImVec2(165, 40)))
		{
			tabb = 2;
		}

		if (ImGui::Button("Exploits", ImVec2(165, 40)))
		{
			tabb = 3;
		}

		if (ImGui::Button("Settings", ImVec2(165, 40)))
		{
			tabb = 4;
		}

		ImGui::SetCursorPosY(370);
		ImGui::SetCursorPosX(60);
		ImGui::TextColored(ImGui::ColorConvertU32ToFloat4(ImColor(red, green, blue)), ("your name"));


		if (tabb == 1)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));


			ImGui::SetCursorPos(ImVec2(2, 0));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));


			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		// BOTTOM BAR BELOW TAB BUTTONS

		if (tabb == 2)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));

			ImGui::SetCursorPos(ImVec2(2, 45));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));

			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
		// BOTTOM BAR BELOW TAB BUTTONS

		if (tabb == 3)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));

			ImGui::SetCursorPos(ImVec2(2, 90));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(0, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));

			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}

		// BOTTOM BAR BELOW TAB BUTTONS

		if (tabb == 4)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(red, green, blue, 255)));

			ImGui::SetCursorPos(ImVec2(2, 130));
			ImGui::Button(" ", ImVec2(3, 40));


			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();

		}
		else
		{

			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(ImColor(30, 30, 30, 0)));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(ImColor(30, 30, 30, 0)));

			ImGui::SameLine();
			ImGui::Button(" ", ImVec2(3, 40));

			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
			ImGui::PopStyleColor();
		}
		// BOTTOM BAR BELOW TAB BUTTONS


		ImGui::EndChild();


		if (tabb == 1)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);
			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##leftside", ImVec2(460, 400), false);
			ImGui::SetCursorPosX(80);
			ImGui::Text("Aimbot");
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();	
			ImGui::Spacing();
			ImGui::Spacing();
			
			ImGui::PopStyleColor();


			

			

		}


		if (tabb == 2)
		{

			ImGui::SameLine();
			ImGui::SetCursorPosY(10);
			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##leftside", ImVec2(460, 400), false);
			ImGui::SetCursorPosX(80);

			ImGui::Text("Visuals", 1, true);
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing(); 
		
			ImGui::Checkbox("Vis check", &visbcheck);
			ImGui::Spacing();
			ImGui::Checkbox("Aimhelper", &aimhelper);
			ImGui::Spacing();
			ImGui::Checkbox("Fill wireframe", &fillesp);
			ImGui::Checkbox("Chams", &chams);
			ImGui::Checkbox("ESP", &esp);
			ImGui::Checkbox("wallhack", &wallhack);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Crosshair", &nazi2);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
		
			ImGui::Spacing();
			ImGui::Spacing();
			


		}




		if (tabb == 3)
		{

			ImGui::SameLine();
			ImGui::SetCursorPosY(10);
			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##leftside", ImVec2(460, 400), false);
			ImGui::SetCursorPosX(80);

			ImGui::Text("Exploits", 1, true);
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Checkbox("Invisible", &invisible);
			ImGui::Spacing();
			ImGui::Spacing();

			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Text("Colors");
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::ColorPicker3("chams color", &col12);;
			
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();



		}
		


		if (tabb == 4)
		{
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);
			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##leftside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(80);

			ImGui::Text("Settings", 1, true);
			ImGui::Separator();
			ImGui::Checkbox("BackGroud Particles", &particles);
			ImGui::PopStyleColor();

			ImGui::EndChild();
			ImGui::SameLine();
			ImGui::SetCursorPosY(10);

			ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(ImColor(red, green, blue, 255)));
			ImGui::BeginChild("##rightside", ImVec2(230, 400), false);
			ImGui::SetCursorPosX(55);
			ImGui::Text("Color Settings", 1, true);
			ImGui::Separator();
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Red", &red, 0, 255);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Green", &green, 0, 255);
			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::SetCursorPosX(10);
			ImGui::SliderInt("Blue", &blue, 0, 255);

			ImGui::EndChild();
			ImGui::PopStyleColor();

		}




		ImGui::EndChild();
		ImGui::End();
	}
	


	targetfound = false;
	//do esp
	if (esp == 1)
	{
		ImGui::Begin("Transparent", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoBackground);
		ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(io.DisplaySize.x, io.DisplaySize.y), ImGuiCond_Always);

		if (AimEspInfo.size() != NULL)
		{
			for (unsigned int i = 0; i < AimEspInfo.size(); i++)
			{
				if (AimEspInfo[i].vOutX > 1 && AimEspInfo[i].vOutY > 1 && AimEspInfo[i].vOutX < ViewportWidth && AimEspInfo[i].vOutY < ViewportHeight)
				{
					//text esp
					ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize(), ImVec2(AimEspInfo[i].vOutX, AimEspInfo[i].vOutY), ImColor(255, 255, 255, 255), "Model", 0, 0.0f, 0); //draw text
				}
			}
		}
		ImGui::End();
	}
	
	AimEspInfo.clear();

	float deltaTime = 0.0f;
	float currentTime = 0.0f;


	if (watermark)
	{

		// Get frames per second (FPS)
		deltaTime = ImGui::GetIO().DeltaTime;
		float fps = 1.0f / deltaTime;

		// Get current date and time
		time_t now = time(nullptr);
		tm* timeinfo = localtime(&now);
		char dateTimeStr[64];
		strftime(dateTimeStr, sizeof(dateTimeStr), "%Y-%m-%d %H:%M:%S", timeinfo);

		// Calculate the time running
		currentTime += deltaTime;
		char timeRunningStr[64];
		snprintf(timeRunningStr, sizeof(timeRunningStr), "Time Running: %.1f s", currentTime);

		// Create the watermark string
		char watermarkStr[128];
		snprintf(watermarkStr, sizeof(watermarkStr), " | Wiz Multitool | %s | FPS: %.2f |", dateTimeStr, fps);

		// Display the watermark
		ImGui::GetOverlayDrawList()->AddText(ImVec2(22, 24), ImColor(255, 255, 255), watermarkStr);

	}


	if (aimhelper)
	{


		float ScreenCenterX = (Width / 2);
		float ScreenCenterY = (Height / 2);
		int AimSpeed = AimSpeed;
		float TargetX = 0;
		float TargetY = 0;

		if (ScreenCenterX != 0)
		{
			if (ScreenCenterX > ScreenCenterX)
			{
				TargetX = -(ScreenCenterX - ScreenCenterX);
				TargetX /= AimSpeed;
				if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
			}

			if (ScreenCenterX < ScreenCenterX)
			{
				TargetX = ScreenCenterX - ScreenCenterX;
				TargetX /= AimSpeed;
				if (TargetX + ScreenCenterX < 0) TargetX = 0;
			}
		}

		if (ScreenCenterY != 0)
		{
			if (ScreenCenterY > ScreenCenterY)
			{
				TargetY = -(ScreenCenterY - ScreenCenterY);
				TargetY /= AimSpeed;
				if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
			}

			if (ScreenCenterY < ScreenCenterY)
			{
				TargetY = ScreenCenterY - ScreenCenterY;
				TargetY /= AimSpeed;
				if (TargetY + ScreenCenterY < 0) TargetY = 0;
			}
		}

		mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), NULL, NULL);
		




	}


	if (espline)
	{

		
		

	}

	if (nazi2)   //nazi crosshair
	{

		POINT Screen;
		Screen.x = GetSystemMetrics(SM_CXSCREEN);
		Screen.y = GetSystemMetrics(SM_CYSCREEN);

		POINT Middle;
		Middle.x = Screen.x / 2;
		Middle.y = Screen.y / 2;

		ImU32 lineColor = IM_COL32(255, 0, 0, 255); // Red color
		ImVec2 p0 = ImVec2(Middle.x - 10, Middle.y);
		ImVec2 p1 = ImVec2(Middle.x + 10, Middle.y);
		ImVec2 p2 = ImVec2(Middle.x, Middle.y - 10);
		ImVec2 p3 = ImVec2(Middle.x, Middle.y + 10);

		ImGui::GetOverlayDrawList()->AddLine(p0, p1, lineColor, 1.0f); // Horizontal line
		ImGui::GetOverlayDrawList()->AddLine(p2, p3, lineColor, 1.0f);
		
	}


	//ImGui::EndFrame();
	ImGui::Render();
	pContext->OMSetRenderTargets(1, &mainRenderTargetViewD3D11, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	return phookD3D11Present(pSwapChain, SyncInterval, Flags);
}
//==========================================================================================================================



void __stdcall hookD3D11DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	if (IndexCount > 0)
		check_drawindexed_result = 1;

	ID3D11Buffer* veBuffer;
	UINT veWidth;
	UINT Stride;
	UINT veBufferOffset;
	D3D11_BUFFER_DESC veDesc;

	//get models
	pContext->IAGetVertexBuffers(0, 1, &veBuffer, &Stride, &veBufferOffset);
	if (veBuffer) {
		veBuffer->GetDesc(&veDesc);
		veWidth = veDesc.ByteWidth;
	}
	if (NULL != veBuffer) {
		veBuffer->Release();
		veBuffer = NULL;
	}

	ID3D11Buffer* pscBuffer;
	UINT pscWidth;
	D3D11_BUFFER_DESC pscdesc;

	//get pscdesc.ByteWidth
	pContext->PSGetConstantBuffers(0, 1, &pscBuffer);
	if (pscBuffer) {
		pscBuffer->GetDesc(&pscdesc);
		pscWidth = pscdesc.ByteWidth;
	}
	if (NULL != pscBuffer) {
		pscBuffer->Release();
		pscBuffer = NULL;
	}

	//wallhack/chams
	if (wallhack == 1 || chams == 1) //if wallhack or chams option is enabled in menu
	if( ((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCount / 10 || countveWidth == veWidth / 10 || countpscWidth == pscWidth / 10))||	//model rec (replace later with logged values) <--
		((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCount / 10 || countveWidth == veWidth / 10 || countpscWidth == pscWidth / 10))|| //model rec (replace later with logged values) <--
		((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCount / 10 || countveWidth == veWidth / 10 || countpscWidth == pscWidth / 10)) )//model rec (replace later with logged values) <--
		/*
		//unreal4 models
		if ((Stride == 32 && IndexCount == 10155) ||
			(Stride == 44 && IndexCount == 11097) ||
			(Stride == 40 && IndexCount == 11412) ||
			(Stride == 40 && IndexCount == 11487) ||
			(Stride == 44 && IndexCount == 83262) ||
			(Stride == 40 && IndexCount == 23283))
		*/
		{
			//get orig
			if (wallhack == 1)
				pContext->OMGetDepthStencilState(&DepthStencilState_ORIG, 0); //get original

			//set off
			if (wallhack == 1)
				pContext->OMSetDepthStencilState(DepthStencilState_FALSE, 0); //depthstencil off

			if (chams == 1)
				pContext->PSSetShader(sGreen, NULL, NULL);
				//pContext->PSSetShaderResources(0, 1, &textureColor); //magenta

			phookD3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation); //redraw

			if (chams == 1)
				pContext->PSSetShader(sMagenta, NULL, NULL);

			//restore orig
			if (wallhack == 1)
				pContext->OMSetDepthStencilState(DepthStencilState_ORIG, 0); //depthstencil on

			//release
			if (wallhack == 1)
				SAFE_RELEASE(DepthStencilState_ORIG); //release
		}

	//esp
	if (esp == 1) //if esp/aimbot option is enabled in menu
	if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCount / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
		((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCount / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
		((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCount / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
		/*
		//unreal4 models
		if ((Stride == 32 && IndexCount == 10155) ||
			(Stride == 44 && IndexCount == 11097) ||
			(Stride == 40 && IndexCount == 11412) ||
			(Stride == 40 && IndexCount == 11487) ||
			(Stride == 44 && IndexCount == 83262) ||
			(Stride == 40 && IndexCount == 23283))
		*/
		{
			AddModel(pContext); //w2s
			targetfound = true;
		}


	//menu logger
	if (modelrecfinder == 1)
	{
		//log selected values
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCount / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
		((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCount / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
		((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCount / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
		if (GetAsyncKeyState(VK_END) & 1) //press END to log to log.txt
			Log("Stride == %d && IndexCount == %d && veWidth == %d && pscWidth == %d", Stride, IndexCount, veWidth, pscWidth);

		//highlight selected
		if (((modelfindmode == 1) && (countStride == Stride || countIndexCount == IndexCount / 10 || countveWidth == veWidth / 100 || countpscWidth == pscWidth / 1)) ||	//model rec (replace later with logged values) <--
		((modelfindmode == 2) && (countStride == Stride || countIndexCount == IndexCount / 100 || countveWidth == veWidth / 1000 || countpscWidth == pscWidth / 10)) || //model rec (replace later with logged values) <--
		((modelfindmode == 3) && (countStride == Stride || countIndexCount == IndexCount / 1000 || countveWidth == veWidth / 10000 || countpscWidth == pscWidth / 100)))//model rec (replace later with logged values) <--
		{
			validvscStartSlot = vscStartSlot;

			//pContext->PSSetShader(sGreen, NULL, NULL);
			return; //delete selected texture
		}
	}

    return phookD3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}

//==========================================================================================================================

void __stdcall hookD3D11DrawIndexedInstanced(ID3D11DeviceContext* pContext, UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation)
{
	if (IndexCountPerInstance > 0)
		check_drawindexedinstanced_result = 1;

	return phookD3D11DrawIndexedInstanced(pContext, IndexCountPerInstance, InstanceCount, StartIndexLocation, BaseVertexLocation, StartInstanceLocation);
}

//==========================================================================================================================

void __stdcall hookD3D11Draw(ID3D11DeviceContext* pContext, UINT VertexCount, UINT StartVertexLocation)
{
	if (VertexCount > 0)
		check_draw_result = 1;

	return phookD3D11Draw(pContext, VertexCount, StartVertexLocation);
}

//==========================================================================================================================

void __stdcall hookD3D11PSSetShaderResources(ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumViews, ID3D11ShaderResourceView* const* ppShaderResourceViews)
{
	//pssrStartSlot = StartSlot;

	/*
	//texture stuff usually not needed
	for (UINT j = 0; j < NumViews; j++)
	{
		//resources loop
		ID3D11ShaderResourceView* pShaderResView = ppShaderResourceViews[j];
		if (pShaderResView)
		{
			pShaderResView->GetDesc(&Descr);

			ID3D11Resource* Resource;
			pShaderResView->GetResource(&Resource);
			ID3D11Texture2D* Texture = (ID3D11Texture2D*)Resource;
			Texture->GetDesc(&texdesc);

			SAFE_RELEASE(Resource);
			SAFE_RELEASE(Texture);
		}
	}
	*/
	return phookD3D11PSSetShaderResources(pContext, StartSlot, NumViews, ppShaderResourceViews);
}

//==========================================================================================================================

void __stdcall hookD3D11VSSetConstantBuffers(ID3D11DeviceContext* pContext, UINT StartSlot, UINT NumBuffers, ID3D11Buffer *const *ppConstantBuffers)
{
	//can tell us WorldViewCBnum & ProjCBnum
	vscStartSlot = StartSlot;

	return phookD3D11VSSetConstantBuffers(pContext, StartSlot, NumBuffers, ppConstantBuffers);
}



//==========================================================================================================================

static HRESULT(WINAPI* d3d11_CreatePixelShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11PixelShader**);
static HRESULT(WINAPI* d3d11_CreateVertexShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11VertexShader**);
static HRESULT(WINAPI* d3d11_CreateComputeShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11ComputeShader**);
static HRESULT(WINAPI* d3d11_CreateHullShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11HullShader**);
static HRESULT(WINAPI* d3d11_CreateDomainShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11DomainShader**);
static HRESULT(WINAPI* d3d11_CreateGeometryShader)(ID3D11Device*, const void*, SIZE_T, ID3D11ClassLinkage*, ID3D11GeometryShader**);
static HRESULT(WINAPI* d3d11_CreateGeometryShaderWithStreamOutput)(ID3D11Device*, const void*, SIZE_T, const D3D11_SO_DECLARATION_ENTRY*, UINT, const UINT*, UINT, UINT, ID3D11ClassLinkage*, ID3D11GeometryShader**);


static HRESULT WINAPI PixelShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11PixelShader** shader)
{
	//Log("A");
	if (shader && dumpshader)
		ShaderHook(pDevice, "ps", &bytecode, &length);
	return d3d11_CreatePixelShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI VertexShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11VertexShader** shader)
{
	//Log("B");
	if (shader && dumpshader)
		ShaderHook(pDevice, "vs", &bytecode, &length);
	return d3d11_CreateVertexShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI ComputeShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11ComputeShader** shader)
{
	if(shader)
	ShaderHook(pDevice, "cs", &bytecode, &length);
	return d3d11_CreateComputeShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI HullShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11HullShader** shader)
{
	if (shader)
	ShaderHook(pDevice, "hs", &bytecode, &length);
	return d3d11_CreateHullShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI DomainShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11DomainShader** shader)
{
	if (shader)
	ShaderHook(pDevice, "ds", &bytecode, &length);
	return d3d11_CreateDomainShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI GeometryShaderHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, ID3D11ClassLinkage* linkage, ID3D11GeometryShader** shader)
{
	if (shader)
	ShaderHook(pDevice, "gs", &bytecode, &length);
	return d3d11_CreateGeometryShader(pDevice, bytecode, length, linkage, shader);
}

static HRESULT WINAPI GeometryShaderWithStreamOutputHook(ID3D11Device* pDevice, const void* bytecode, SIZE_T length, const D3D11_SO_DECLARATION_ENTRY* entries, UINT entry_count, const UINT* strides, UINT stride_count, UINT stream, ID3D11ClassLinkage* linkage, ID3D11GeometryShader** shader)
{
	if (shader)
	ShaderHook(pDevice, "gs", &bytecode, &length);
	return d3d11_CreateGeometryShaderWithStreamOutput(pDevice, bytecode, length, entries, entry_count, strides, stride_count, stream, linkage, shader);
}

//==========================================================================================================================

const int MultisampleCount = 1; // Set to 1 to disable multisampling
LRESULT CALLBACK DXGIMsgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){ return DefWindowProc(hwnd, uMsg, wParam, lParam); }
DWORD __stdcall InitializeHook(LPVOID)
{
	HMODULE hDXGIDLL = 0;
	do
	{
		hDXGIDLL = GetModuleHandle("dxgi.dll");
		Sleep(4000);
	} while (!hDXGIDLL);
	Sleep(100);

	oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);

    IDXGISwapChain* pSwapChain;

	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DXGIMsgProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);


	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;

	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = hWnd;
	scd.SampleDesc.Count = 1;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = ((GetWindowLongPtr(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

	// LibOVR 0.4.3 requires that the width and height for the backbuffer is set even if
	// you use windowed mode, despite being optional according to the D3D11 documentation.
	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;

	UINT createFlags = 0;
#ifdef _DEBUG
	// This flag gives you some quite wonderful debug text. Not wonderful for performance, though!
	createFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createFlags,
		requestedLevels,
		sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&scd,
		&pSwapChain,
		&pDevice,
		&obtainedLevel,
		&pContext)
	))
	{
		MessageBox(hWnd, "Failed to create directX device and swapchain!", "Error", MB_ICONERROR);
		return false;
	}

	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];

	pContextVTable = (DWORD_PTR*)pContext;
	pContextVTable = (DWORD_PTR*)pContextVTable[0];

	pDeviceVTable = (DWORD_PTR*)pDevice;
	pDeviceVTable = (DWORD_PTR*)pDeviceVTable[0];

	if (MH_Initialize() != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pSwapChainVtable[8], hookD3D11Present, reinterpret_cast<void**>(&phookD3D11Present)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pSwapChainVtable[8]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pSwapChainVtable[13], hookD3D11ResizeBuffers, reinterpret_cast<void**>(&phookD3D11ResizeBuffers)) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[39], hookD3D11DrawIndexedInstancedIndirect, reinterpret_cast<void**>(&phookD3D11DrawIndexedInstancedIndirect)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[39]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[12], hookD3D11DrawIndexed, reinterpret_cast<void**>(&phookD3D11DrawIndexed)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[12]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[20], hookD3D11DrawIndexedInstanced, reinterpret_cast<void**>(&phookD3D11DrawIndexedInstanced)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[20]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[13], hookD3D11Draw, reinterpret_cast<void**>(&phookD3D11Draw)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[13]) != MH_OK) { return 1; }

	return true;
	//DrawInstanced
	//DrawInstancedIndirect
	//DrawIndexedInstancedIndirect

	//if (MH_CreateHook((DWORD_PTR*)pContextVTable[8], hookD3D11PSSetShaderResources, reinterpret_cast<void**>(&phookD3D11PSSetShaderResources)) != MH_OK) { return 1; }
	//if (MH_EnableHook((DWORD_PTR*)pContextVTable[8]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[7], hookD3D11VSSetConstantBuffers, reinterpret_cast<void**>(&phookD3D11VSSetConstantBuffers)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[7]) != MH_OK) { return 1; }

	//dump shader
	//if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[15], PixelShaderHook, reinterpret_cast<void**>(&d3d11_CreatePixelShader)) != MH_OK) { return 1; }
	//if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[15]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[12], VertexShaderHook, reinterpret_cast<void**>(&d3d11_CreateVertexShader)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[12]) != MH_OK) { return 1; }
	//if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[18], ComputeShaderHook, reinterpret_cast<void**>(&d3d11_CreateComputeShader)) != MH_OK) { return 1; }
	//if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[18]) != MH_OK) { return 1; }
	//if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[16], HullShaderHook, reinterpret_cast<void**>(&d3d11_CreateHullShader)) != MH_OK) { return 1; }
	//if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[16]) != MH_OK) { return 1; }
	//if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[17], DomainShaderHook, reinterpret_cast<void**>(&d3d11_CreateDomainShader)) != MH_OK) { return 1; }
	//if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[17]) != MH_OK) { return 1; }
	//if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[13], GeometryShaderHook, reinterpret_cast<void**>(&d3d11_CreateGeometryShader)) != MH_OK) { return 1; }
	//if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[13]) != MH_OK) { return 1; }
	//if (MH_CreateHook((DWORD_PTR*)pDeviceVTable[14], GeometryShaderWithStreamOutputHook, reinterpret_cast<void**>(&d3d11_CreateGeometryShaderWithStreamOutput)) != MH_OK) { return 1; }
	//if (MH_EnableHook((DWORD_PTR*)pDeviceVTable[14]) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)pContextVTable[39], hookD3D11DrawIndexedInstancedIndirect, reinterpret_cast<void**>(&phookD3D11DrawIndexedInstancedIndirect)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)pContextVTable[39]) != MH_OK) { return 1; }


	DWORD dwOld;
	VirtualProtect(phookD3D11Present, 2, PAGE_EXECUTE_READWRITE, &dwOld);

	while (true) {
		Sleep(10);
	}

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();

	return NULL;
}

//==========================================================================================================================

BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{ 
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH: // A process is loading the DLL.
		DisableThreadLibraryCalls(hModule);
		GetModuleFileName(hModule, dlldir, 512);
		for (size_t i = strlen(dlldir); i > 0; i--) { if (dlldir[i] == '\\') { dlldir[i + 1] = 0; break; } }
		CreateThread(NULL, 0, InitializeHook, NULL, 0, NULL);
		break;

	case DLL_PROCESS_DETACH: // A process unloads the DLL.
		if (MH_Uninitialize() != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pSwapChainVtable[8]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pSwapChainVtable[13]) != MH_OK) { return 1; }

		if (MH_DisableHook((DWORD_PTR*)pContextVTable[12]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pContextVTable[20]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pContextVTable[13]) != MH_OK) { return 1; }

		//if (MH_DisableHook((DWORD_PTR*)pContextVTable[8]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pContextVTable[7]) != MH_OK) { return 1; }

		if (MH_DisableHook((DWORD_PTR*)pDeviceVTable[15]) != MH_OK) { return 1; }
		if (MH_DisableHook((DWORD_PTR*)pDeviceVTable[12]) != MH_OK) { return 1; }

		break;
	}
	return TRUE;
}

/*
// from d3d11.h. Simply walk the inheritance. In C++ the order of methods in a .h file is the order in the vtable, after the vtable of inherited
// types, so it's easy to determine what the location is without loggers.
// IUnknown
0	virtual HRESULT STDMETHODCALLTYPE QueryInterface
1	virtual ULONG STDMETHODCALLTYPE AddRef
2	virtual ULONG STDMETHODCALLTYPE Release
// ID3D11Device
3	virtual HRESULT STDMETHODCALLTYPE CreateBuffer
4	virtual HRESULT STDMETHODCALLTYPE CreateTexture1D
5	virtual HRESULT STDMETHODCALLTYPE CreateTexture2D
6	virtual HRESULT STDMETHODCALLTYPE CreateTexture3D
7	virtual HRESULT STDMETHODCALLTYPE CreateShaderResourceView
8	virtual HRESULT STDMETHODCALLTYPE CreateUnorderedAccessView
9	virtual HRESULT STDMETHODCALLTYPE CreateRenderTargetView
10	virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilView
11	virtual HRESULT STDMETHODCALLTYPE CreateInputLayout
12	virtual HRESULT STDMETHODCALLTYPE CreateVertexShader
13	virtual HRESULT STDMETHODCALLTYPE CreateGeometryShader
14	virtual HRESULT STDMETHODCALLTYPE CreateGeometryShaderWithStreamOutput
15	virtual HRESULT STDMETHODCALLTYPE CreatePixelShader
16	virtual HRESULT STDMETHODCALLTYPE CreateHullShader
17	virtual HRESULT STDMETHODCALLTYPE CreateDomainShader
18	virtual HRESULT STDMETHODCALLTYPE CreateComputeShader
19	virtual HRESULT STDMETHODCALLTYPE CreateClassLinkage
20	virtual HRESULT STDMETHODCALLTYPE CreateBlendState
21	virtual HRESULT STDMETHODCALLTYPE CreateDepthStencilState
22	virtual HRESULT STDMETHODCALLTYPE CreateRasterizerState
23	virtual HRESULT STDMETHODCALLTYPE CreateSamplerState
24	virtual HRESULT STDMETHODCALLTYPE CreateQuery
25	virtual HRESULT STDMETHODCALLTYPE CreatePredicate
26	virtual HRESULT STDMETHODCALLTYPE CreateCounter
27	virtual HRESULT STDMETHODCALLTYPE CreateDeferredContext
28	virtual HRESULT STDMETHODCALLTYPE OpenSharedResource
29	virtual HRESULT STDMETHODCALLTYPE CheckFormatSupport
30	virtual HRESULT STDMETHODCALLTYPE CheckMultisampleQualityLevels
31	virtual void STDMETHODCALLTYPE CheckCounterInfo
32	virtual HRESULT STDMETHODCALLTYPE CheckCounter
33	virtual HRESULT STDMETHODCALLTYPE CheckFeatureSupport
34	virtual HRESULT STDMETHODCALLTYPE GetPrivateData
35	virtual HRESULT STDMETHODCALLTYPE SetPrivateData
36	virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface
37	virtual D3D_FEATURE_LEVEL STDMETHODCALLTYPE GetFeatureLevel
38	virtual UINT STDMETHODCALLTYPE GetCreationFlags
39	virtual HRESULT STDMETHODCALLTYPE GetDeviceRemovedReason
40	virtual void STDMETHODCALLTYPE GetImmediateContext
41	virtual HRESULT STDMETHODCALLTYPE SetExceptionMode
42	virtual UINT STDMETHODCALLTYPE GetExceptionMode
---------------------------------------------------------------------------
// IUnknown
0	virtual HRESULT STDMETHODCALLTYPE QueryInterface
1	virtual ULONG STDMETHODCALLTYPE AddRef
2	virtual ULONG STDMETHODCALLTYPE Release
// ID3D11DeviceChild
3	virtual void STDMETHODCALLTYPE GetDevice
4	virtual HRESULT STDMETHODCALLTYPE GetPrivateData
5	virtual HRESULT STDMETHODCALLTYPE SetPrivateData
6	virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface
// ID3D11DeviceContext
7	virtual void STDMETHODCALLTYPE VSSetConstantBuffers
8	virtual void STDMETHODCALLTYPE PSSetShaderResources
9	virtual void STDMETHODCALLTYPE PSSetShader
10	virtual void STDMETHODCALLTYPE PSSetSamplers
11	virtual void STDMETHODCALLTYPE VSSetShader
12	virtual void STDMETHODCALLTYPE DrawIndexed
13	virtual void STDMETHODCALLTYPE Draw
14	virtual HRESULT STDMETHODCALLTYPE Map
15	virtual void STDMETHODCALLTYPE Unmap
16	virtual void STDMETHODCALLTYPE PSSetConstantBuffers
17	virtual void STDMETHODCALLTYPE IASetInputLayout
18	virtual void STDMETHODCALLTYPE IASetVertexBuffers
19	virtual void STDMETHODCALLTYPE IASetIndexBuffer
20	virtual void STDMETHODCALLTYPE DrawIndexedInstanced
21	virtual void STDMETHODCALLTYPE DrawInstanced
22	virtual void STDMETHODCALLTYPE GSSetConstantBuffers
23	virtual void STDMETHODCALLTYPE GSSetShader
24	virtual void STDMETHODCALLTYPE IASetPrimitiveTopology
25	virtual void STDMETHODCALLTYPE VSSetShaderResources
26	virtual void STDMETHODCALLTYPE VSSetSamplers
27	virtual void STDMETHODCALLTYPE Begin
28	virtual void STDMETHODCALLTYPE End
29	virtual HRESULT STDMETHODCALLTYPE GetData
30	virtual void STDMETHODCALLTYPE SetPredication
31	virtual void STDMETHODCALLTYPE GSSetShaderResources
32	virtual void STDMETHODCALLTYPE GSSetSamplers
33	virtual void STDMETHODCALLTYPE OMSetRenderTargets
34	virtual void STDMETHODCALLTYPE OMSetRenderTargetsAndUnorderedAccessViews
35	virtual void STDMETHODCALLTYPE OMSetBlendState
36	virtual void STDMETHODCALLTYPE OMSetDepthStencilState
37	virtual void STDMETHODCALLTYPE SOSetTargets
38	virtual void STDMETHODCALLTYPE DrawAuto
39	virtual void STDMETHODCALLTYPE DrawIndexedInstancedIndirect
40	virtual void STDMETHODCALLTYPE DrawInstancedIndirect
41	virtual void STDMETHODCALLTYPE Dispatch
42	virtual void STDMETHODCALLTYPE DispatchIndirect
43	virtual void STDMETHODCALLTYPE RSSetState
44	virtual void STDMETHODCALLTYPE RSSetViewports
45	virtual void STDMETHODCALLTYPE RSSetScissorRects
46	virtual void STDMETHODCALLTYPE CopySubresourceRegion
47	virtual void STDMETHODCALLTYPE CopyResource
48	virtual void STDMETHODCALLTYPE UpdateSubresource
49	virtual void STDMETHODCALLTYPE CopyStructureCount
50	virtual void STDMETHODCALLTYPE ClearRenderTargetView
51	virtual void STDMETHODCALLTYPE ClearUnorderedAccessViewUint
52	virtual void STDMETHODCALLTYPE ClearUnorderedAccessViewFloat
53	virtual void STDMETHODCALLTYPE ClearDepthStencilView
54	virtual void STDMETHODCALLTYPE GenerateMips
55	virtual void STDMETHODCALLTYPE SetResourceMinLOD
56	virtual FLOAT STDMETHODCALLTYPE GetResourceMinLOD
57	virtual void STDMETHODCALLTYPE ResolveSubresource
58	virtual void STDMETHODCALLTYPE ExecuteCommandList
59	virtual void STDMETHODCALLTYPE HSSetShaderResources
60	virtual void STDMETHODCALLTYPE HSSetShader
61	virtual void STDMETHODCALLTYPE HSSetSamplers
62	virtual void STDMETHODCALLTYPE HSSetConstantBuffers
63	virtual void STDMETHODCALLTYPE DSSetShaderResources
64	virtual void STDMETHODCALLTYPE DSSetShader
65	virtual void STDMETHODCALLTYPE DSSetSamplers
66	virtual void STDMETHODCALLTYPE DSSetConstantBuffers
67	virtual void STDMETHODCALLTYPE CSSetShaderResources
68	virtual void STDMETHODCALLTYPE CSSetUnorderedAccessViews
69	virtual void STDMETHODCALLTYPE CSSetShader
70	virtual void STDMETHODCALLTYPE CSSetSamplers
71	virtual void STDMETHODCALLTYPE CSSetConstantBuffers
72	virtual void STDMETHODCALLTYPE VSGetConstantBuffers
73	virtual void STDMETHODCALLTYPE PSGetShaderResources
74	virtual void STDMETHODCALLTYPE PSGetShader
75	virtual void STDMETHODCALLTYPE PSGetSamplers
76	virtual void STDMETHODCALLTYPE VSGetShader
77	virtual void STDMETHODCALLTYPE PSGetConstantBuffers
78	virtual void STDMETHODCALLTYPE IAGetInputLayout
79	virtual void STDMETHODCALLTYPE IAGetVertexBuffers
80	virtual void STDMETHODCALLTYPE IAGetIndexBuffer
81	virtual void STDMETHODCALLTYPE GSGetConstantBuffers
82	virtual void STDMETHODCALLTYPE GSGetShader
83	virtual void STDMETHODCALLTYPE IAGetPrimitiveTopology
84	virtual void STDMETHODCALLTYPE VSGetShaderResources
85	virtual void STDMETHODCALLTYPE VSGetSamplers
86	virtual void STDMETHODCALLTYPE GetPredication
87	virtual void STDMETHODCALLTYPE GSGetShaderResources
88	virtual void STDMETHODCALLTYPE GSGetSamplers
89	virtual void STDMETHODCALLTYPE OMGetRenderTargets
90	virtual void STDMETHODCALLTYPE OMGetRenderTargetsAndUnorderedAccessViews
91	virtual void STDMETHODCALLTYPE OMGetBlendState
92	virtual void STDMETHODCALLTYPE OMGetDepthStencilState
93	virtual void STDMETHODCALLTYPE SOGetTargets
94	virtual void STDMETHODCALLTYPE RSGetState
95	virtual void STDMETHODCALLTYPE RSGetViewports
96	virtual void STDMETHODCALLTYPE RSGetScissorRects
97	virtual void STDMETHODCALLTYPE HSGetShaderResources
98	virtual void STDMETHODCALLTYPE HSGetShader
99	virtual void STDMETHODCALLTYPE HSGetSamplers
100	virtual void STDMETHODCALLTYPE HSGetConstantBuffers
101	virtual void STDMETHODCALLTYPE DSGetShaderResources
102	virtual void STDMETHODCALLTYPE DSGetShader
103	virtual void STDMETHODCALLTYPE DSGetSamplers
104	virtual void STDMETHODCALLTYPE DSGetConstantBuffers
105	virtual void STDMETHODCALLTYPE CSGetShaderResources
106	virtual void STDMETHODCALLTYPE CSGetUnorderedAccessViews
107	virtual void STDMETHODCALLTYPE CSGetShader
108	virtual void STDMETHODCALLTYPE CSGetSamplers
109	virtual void STDMETHODCALLTYPE CSGetConstantBuffers
110	virtual void STDMETHODCALLTYPE ClearState
111	virtual void STDMETHODCALLTYPE Flush
112	virtual D3D11_DEVICE_CONTEXT_TYPE STDMETHODCALLTYPE GetType
113	virtual UINT STDMETHODCALLTYPE GetContextFlags
114	virtual HRESULT STDMETHODCALLTYPE FinishCommandList
-----------------------------------------------------------------------
// IUnknown
0	virtual HRESULT STDMETHODCALLTYPE QueryInterface
1	virtual ULONG STDMETHODCALLTYPE AddRef
2	virtual ULONG STDMETHODCALLTYPE Release
// IDXGIObject
3	virtual HRESULT STDMETHODCALLTYPE SetPrivateData
4	virtual HRESULT STDMETHODCALLTYPE SetPrivateDataInterface
5	virtual HRESULT STDMETHODCALLTYPE GetPrivateData
6	virtual HRESULT STDMETHODCALLTYPE GetParent
// IDXGIDeviceSubObject
7   virtual HRESULT STDMETHODCALLTYPE GetDevice
// IDXGISwapChain
8	virtual HRESULT STDMETHODCALLTYPE Present
9	virtual HRESULT STDMETHODCALLTYPE GetBuffer
10	virtual HRESULT STDMETHODCALLTYPE SetFullscreenState
11	virtual HRESULT STDMETHODCALLTYPE GetFullscreenState
12	virtual HRESULT STDMETHODCALLTYPE GetDesc
13	virtual HRESULT STDMETHODCALLTYPE ResizeBuffers
14	virtual HRESULT STDMETHODCALLTYPE ResizeTarget
15	virtual HRESULT STDMETHODCALLTYPE GetContainingOutput
16	virtual HRESULT STDMETHODCALLTYPE GetFrameStatistics
17	virtual HRESULT STDMETHODCALLTYPE GetLastPresentCount
*/
