//d3d11 w2s base for some games by n7




#define WIN32_LEAN_AND_MEAN

//globals
bool showmenu = false;
bool initonce = false;
bool nazi2 = false;
bool espline = true;



#define M_PI 3.14159265358979323846264338327950288419716939937510




float BOG_TO_GRD(float BOG) {
	return (180 / M_PI) * BOG;
}

float GRD_TO_BOG(float GRD) {
	return (M_PI / 180) * GRD;
}

//item states
bool wallhack = 0;
bool chams = 0;
bool esp = 0;
bool watermark = 1;//autoshoot
bool aimhelper = 0;
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#define WIN32_LEAN_AND_MEAN //to exclude some of the less frequently used APIs 


bool targetfound = true;






struct {
	// Basic colors: ========================================================
	float Black[3];
	float RGBRed[3] = { 1.0f, 0.0f, 0.0f };
	float RGBYelllow[3] = { 1.0f, 1.0f, 0.0f };
	float RGBGreen[3] = { 0.0f, 1.0f, 0.0f };
	float RGBBlue[3] = { 0.0f, 0.0f, 1.0f };
	float CMYKRed[3] = { 0.92f, 0.10f, 0.14f };
	float CMYKYellow[3] = { 1.0f, 0.94f, 0.0f };
	float CMYKGreen[3] = { 0.0f, 0.65f, 3.17f };
	float CMYKBlue[3] = { 0.18f, 0.19f, 0.57f };
	float PastelRed[3] = { 0.96f, 0.58f, 0.47f };
	float PastelRedOrange[3] = { 0.97f, 0.67f, 0.50f };
	float PastelYellowOrange[3] = { 0.99f, 0.77f, 0.53f };
	float PastelYellow[3] = { 1.0f, 0.96f, 0.6f };
	float PastelPeaGreen[3] = { 0.76f, 0.87f, 0.60f };
	float PastelYellowGreen[3] = { 0.63f, 0.82f, 0.61f };
	float PastelGreen[3] = { 0.50f, 0.79f, 0.61f };
	float PastelGreenCyan[3] = { 0.47f, 0.8f, 0.78f };
	float PastelCyan[3] = { 0.42f, 0.81f, 0.96f };
	float PastelCyanBlue[3] = { 0.49f, 0.65f, 0.85f };
	float PastelBlue[3] = { 0.51f, 0.57f, 0.79f };
	float PastelBlueViolet[3] = { 0.52f, 0.50f, 0.74f };
	float PastelViolet[3] = { 0.63f, 0.52f, 0.74f };
	float PastelVioletMagenta[3] = { 0.74f, 0.54f, 0.74f };
	float PastelMagenta[3] = { 0.95f, 0.60f, 0.75f };
	float PastelMagentaRed[3] = { 0.96f, 0.59f, 0.61f };
	float LightRed[3] = { 0.94f, 0.42f, 0.30f };
	float LightRedOrange[3] = { 0.96f, 0.55f, 0.33f };
	float LightYellowOrange[3] = { 0.98f, 0.68f, 0.36f };
	float LightYellow[3] = { 1.0f, 0.96f, 0.40f };
	float LightPeaGreen[3] = { 0.67f, 0.82f, 0.45f };
	float LightYellowGreen[3] = { 0.48f, 0.77f, 0.46f };
	float LightGreen[3] = { 0.23f, 0.72f, 0.47f };
	float LightGreenCyan[3] = { 0.10f, 0.73f, 0.70f };
	float LightCyan[3] = { 0.0f, 0.74f, 0.95f };
	float LightCyanBlue[3] = { 0.26f, 0.54f, 0.79f };
	float LightBlue[3] = { 0.33f, 0.45f, 0.72f };
	float LightBlueViolet[3] = { 0.37f, 0.36f, 0.65f };
	float LightViolet[3] = { 0.52f, 0.37f, 0.65f };
	float LightVioletMagenta[3] = { 0.65f, 0.39f, 0.65f };
	float LightMagenta[3] = { 0.94f, 0.43f, 0.66f };
	float LightMagentaRed[3] = { 0.94f, 0.42f, 0.49f };
	float Red[3] = { 0.92f, 0.10f, 0.14f };
	float RedOrange[3] = { 0.94f, 0.39f, 0.13f };
	float YellowOrange[3] = { 0.96f, 0.58f, 0.11f };
	float Yellow[3] = { 1.0f, 0.94f, 0.0f };
	float PeaGreen[3] = { 0.55f, 0.77f, 0.24f };
	float YellowGreen[3] = { 0.22f, 0.70f, 0.29f };
	float Green[3] = { 0.0f, 0.65f, 0.31f };
	float GreenCyan[3] = { 0.0f, 0.66f, 0.61f };
	float Cyan[3] = { 0.0f, 0.68f, 0.93f };
	float CyanBlue[3] = { 0.0f, 0.44f, 0.34f };
	float Blue[3] = { 0.0f, 0.32f, 0.65f };
	float BlueViolet[3] = { 0.19f, 0.19f, 0.57f };
	float Violet[3] = { 0.18f, 0.19f, 0.57f };
	float VioletMagenta[3] = { 0.57f, 0.15f, 5.63f };
	float Magenta[3] = { 0.92f, 0.0f, 0.54f };
	float MagentaRed[3] = { 0.92f, 0.07f, 0.35f };
	float DarkRed[3] = { 0.61f, 0.04f, 0.05f };
	float DarkROrange[3] = { 0.62f, 0.25f, 0.05f };
	float DarkYellowOrange[3] = { 0.53f, 0.38f, 0.03f };
	float DarkYellow[3] = { 0.67f, 0.62f, 0.0f };
	float DarkPeaGreen[3] = { 0.34f, 0.52f, 0.15f };
	float DarkYellowGreen[3] = { 0.09f, 0.48f, 0.18f };
	float DarkGreen[3] = { 0.0f, 0.44f, 0.21f };
	float DarkGreenCyan[3] = { 0.0f, 0.45f, 0.41f };
	float DarkCyan[3] = { 0.0f, 0.46f, 0.63f };
	float DarkCyanBlue[3] = { 0.0f, 0.29f, 0.50f };
	float DarkBlue[3] = { 0.0f, 0.20f, 0.44f };
	float DarkBlueViolet[3] = { 0.10f, 0.07f, 0.39f };
	float DarkViolet[3] = { 0.26f, 0.05f, 0.38f };
	float DarkVioletMagenta[3] = { 0.38f, 0.01f, 0.37f };
	float DarkMagenta[3] = { 0.61f, 0.0f, 0.36f };
	float DarkMagentaRed[3] = { 0.61f, 0.0f, 0.22f };
	float DarkerRed[3] = { 0.47f, 0.0f, 0.0f };
	float DarkerROrange[3] = { 0.48f, 0.18f, 0.0f };
	float DarkerYellowOrange[3] = { 0.49f, 0.28f, 0.0f };
	float DarkerYellow[3] = { 0.50f, 0.48f, 0.0f };
	float DarkerPeaGreen[3] = { 0.25f, 0.4f, 0.09f };
	float DarkerYellowGreen[3] = { 0.0f, 0.36f, 0.12f };
	float DarkerGreen[3] = { 0.0f, 0.34f, 0.14f };
	float DarkerGreenCyan[3] = { 0.0f, 0.34f, 0.32f };
	float DarkerCyan[3] = { 0.0f, 0.35f, 0.49f };
	float DarkerCyanBlue[3] = { 0.0f, 0.21f, 0.38f };
	float DarkerBlue[3] = { 0.0f, 0.12f, 0.34f };
	float DarkerBlueViolet[3] = { 0.05f, 0.0f, 0.29f };
	float DarkerViolet[3] = { 0.19f, 0.0f, 0.29f };
	float DarkerVioletMagenta[3] = { 0.29f, 0.0f, 0.28f };
	float DarkerMagenta[3] = { 0.48f, 0.0f, 0.27f };
	float DarkerMagentaRed[3] = { 0.47f, 0.27f, 0.14f };
	float PaleCoolBrown[3] = { 0.78f, 0.69f, 0.61f };
	float LightCoolBrown[3] = { 0.6f, 0.52f, 0.45f };
	float MiumCoolBrown[3] = { 0.45f, 0.38f, 0.34f };
	float DarkCoolBrown[3] = { 0.32f, 0.27f, 0.25f };
	float DarkerCoolBrown[3] = { 0.21f, 0.18f, 0.17f };
	float PaleWarmBrown[3] = { 0.77f, 0.61f, 0.43f };
	float LightWarmBrown[3] = { 0.65f, 0.48f, 0.32f };
	float MiumWarmBrown[3] = { 0.54f, 0.38f, 0.22f };
	float DarkWarmBrown[3] = { 0.45f, 0.29f, 0.14f };
	float DarkerWarmBrown[3] = { 0.37f, 0.22f, 0.07f };
	float purple[3] = { 144.00f, 0.00f, 255.00f };
	float white[3] = { 3.00f, 3.00f, 3.00f };
} color;


bool modelrecfinder = 1;
int modelfindmode = 1;
int countStride = -1;
int countIndexCount = -1;
int countveWidth = -1;
int Width;
int Height;




bool freezegame = false;


int countpscWidth = -1;
bool dumpshader = 0;
bool wtsfinder = 1;

int check_draw_result=0;
int check_drawindexed_result = 0;
int check_drawindexedinstanced_result = 0;

//rendertarget
ID3D11RenderTargetView* mainRenderTargetViewD3D11;

//wh
ID3D11DepthStencilState* DepthStencilState_TRUE = NULL; //depth off
ID3D11DepthStencilState* DepthStencilState_FALSE = NULL; //depth off
ID3D11DepthStencilState* DepthStencilState_ORIG = NULL; //depth on

//shader
ID3D11PixelShader* sGreen = NULL;
ID3D11PixelShader* sMagenta = NULL;

//pssetshaderresources
//D3D11_SHADER_RESOURCE_VIEW_DESC  Descr;
//D3D11_TEXTURE2D_DESC texdesc;

//Viewport
float ViewportWidth;
float ViewportHeight;
float ScreenCenterX;
float ScreenCenterY;
bool visbcheck;


int countnum = -1;
int g_dwLastAction = 0;
int vscStartSlot = 0;
int validvscStartSlot = 0;




//==========================================================================================================================

//get dir
using namespace std;
#include <fstream>

// getdir & log
char dlldir[320];
char* GetDirFile(char* name)
{
	static char pldir[320];
	strcpy_s(pldir, dlldir);
	strcat_s(pldir, name);
	return pldir;
}




//log
void Log(const char* fmt, ...)
{
	if (!fmt)	return;

	char		text[4096];
	va_list		ap;
	va_start(ap, fmt);
	vsprintf_s(text, fmt, ap);
	va_end(ap);

	ofstream logfile((PCHAR)"log.txt", ios::app);
	if (logfile.is_open() && text)	logfile << text << endl;
	logfile.close();
}

void SendKeyStroke(DWORD key)
{
	INPUT ip;

	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;

	ip.ki.wVk = key;
	ip.ki.dwFlags = 0;
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));
}



DWORD WalkKeys[4] = { 0x57, 0x41, 0x53, 0x44 };

namespace Utils
{
	extern void WelcomeMessage();
	extern void SendKeyStroke(DWORD key);
	extern DWORD FindProcessId(const std::wstring& processName);
	extern int random(int min, int max);
}

void KeyEvent(WORD key, bool press) {
	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.wVk = key;
	if (press) {
		//For key press Flag=0
		ip.ki.dwFlags = 0;
	}
	else {
		ip.ki.dwFlags = KEYEVENTF_KEYUP;
	}
	SendInput(1, &ip, sizeof(INPUT));
}

int random(int min, int max) //range : [min, max]
{
	static bool first = true;
	if (first)
	{
		srand((unsigned int)(time(NULL))); //seeding for the first time only!
		first = false;
	}
	return min + rand() % (max + 1 - min);
}

void MouseMove() {
	INPUT ip;
	ip.type = INPUT_MOUSE;

	ip.mi.mouseData = 0;
	ip.mi.time = 1;
	ip.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &ip, sizeof(INPUT));
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

constexpr auto VK_KEY_W = 0x57;
constexpr auto VK_KEY_A = 0x41;
constexpr auto VK_KEY_S = 0x53;
constexpr auto VK_KEY_D = 0x44;

#include <D3Dcompiler.h> //generateshader
#pragma comment(lib, "D3dcompiler.lib")
//generate shader func
HRESULT GenerateShader(ID3D11Device * pDevice, ID3D11PixelShader * *pShader, float r, float g, float b)
{
	char szCast[] = "struct VS_OUT"
		"{"
		" float4 Position : SV_Position;"
		" float4 Color : COLOR0;"
		"};"

		"float4 main( VS_OUT input ) : SV_Target"
		"{"
		" float4 col;"
		" col.a = 1.0f;"
		" col.r = %f;"
		" col.g = %f;"
		" col.b = %f;"
		" return col;"
		"}";

	ID3D10Blob* pBlob;
	char szPixelShader[1000];

	sprintf_s(szPixelShader, szCast, r, g, b);

	ID3DBlob* error;

	HRESULT hr = D3DCompile(szPixelShader, sizeof(szPixelShader), "shader", NULL, NULL, "main", "ps_4_0", NULL, NULL, &pBlob, &error);

	if (FAILED(hr))
		return hr;

	hr = pDevice->CreatePixelShader((DWORD*)pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, pShader);

	if (FAILED(hr))
		return hr;

	return S_OK;
}

ID3D11Texture2D* texc = nullptr;
ID3D11ShaderResourceView* textureColor;
void GenerateTexture(uint32_t pixelcolor, DXGI_FORMAT format)//DXGI_FORMAT_R32G32B32A32_FLOAT DXGI_FORMAT_R8G8B8A8_UNORM
{
	//static const uint32_t pixelcolor = 0xff00ff00; //0xff00ff00 green, 0xffff0000 blue, 0xff0000ff red
	D3D11_SUBRESOURCE_DATA initData = { &pixelcolor, sizeof(uint32_t), 0 };

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = 1;
	desc.Height = 1;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	pDevice->CreateTexture2D(&desc, &initData, &texc);

	D3D11_SHADER_RESOURCE_VIEW_DESC srdes;
	memset(&srdes, 0, sizeof(srdes));
	srdes.Format = format;
	srdes.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srdes.Texture2D.MostDetailedMip = 0;
	srdes.Texture2D.MipLevels = 1;
	pDevice->CreateShaderResourceView(texc, &srdes, &textureColor);
}



void MapBuffer(ID3D11Buffer * pStageBuffer, void** ppData, UINT * pByteWidth)
{
	D3D11_MAPPED_SUBRESOURCE subRes;
	HRESULT res = pContext->Map(pStageBuffer, 0, D3D11_MAP_READ, 0, &subRes);

	D3D11_BUFFER_DESC desc;
	pStageBuffer->GetDesc(&desc);

	if (FAILED(res))
	{
		//Log("Map stage buffer failed {%d} {%d} {%d} {%d} {%d}", (void*)pStageBuffer, desc.ByteWidth, desc.BindFlags, desc.CPUAccessFlags, desc.Usage);
		SAFE_RELEASE(pStageBuffer); return;
	}
	
	*ppData = subRes.pData;
	
	if (pByteWidth)
		*pByteWidth = desc.ByteWidth;
}

void UnmapBuffer(ID3D11Buffer * pStageBuffer)
{
	pContext->Unmap(pStageBuffer, 0);
}

ID3D11Buffer* pStageBufferA = NULL;
ID3D11Buffer* CopyBufferToCpuA(ID3D11Buffer * pBufferA)
{
	D3D11_BUFFER_DESC CBDescA;
	pBufferA->GetDesc(&CBDescA);

	if (pStageBufferA == NULL)
	{
		//Log("onceA");
		// create buffer
		D3D11_BUFFER_DESC descA;
		descA.BindFlags = 0;
		descA.ByteWidth = CBDescA.ByteWidth;
		descA.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		descA.MiscFlags = 0;
		descA.StructureByteStride = 0;
		descA.Usage = D3D11_USAGE_STAGING;

		if (FAILED(pDevice->CreateBuffer(&descA, NULL, &pStageBufferA)))
		{
			//Log("CreateBuffer failed when CopyBufferToCpuA {}");
		}
	}

	if (pStageBufferA != NULL)
		pContext->CopyResource(pStageBufferA, pBufferA);

	return pStageBufferA;
}

ID3D11Buffer* pStageBufferB = NULL;
ID3D11Buffer* CopyBufferToCpuB(ID3D11Buffer * pBufferB)
{
	D3D11_BUFFER_DESC CBDescB;
	pBufferB->GetDesc(&CBDescB);

	if (pStageBufferB == NULL)
	{
		//Log("onceB");
		// create buffer
		D3D11_BUFFER_DESC descB;
		descB.BindFlags = 0;
		descB.ByteWidth = CBDescB.ByteWidth;
		descB.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		descB.MiscFlags = 0;
		descB.StructureByteStride = 0;
		descB.Usage = D3D11_USAGE_STAGING;

		if (FAILED(pDevice->CreateBuffer(&descB, NULL, &pStageBufferB)))
		{
			//Log("CreateBuffer failed when CopyBufferToCpuB {}");
		}
	}

	if (pStageBufferB != NULL)
		pContext->CopyResource(pStageBufferB, pBufferB);

	return pStageBufferB;
}

//get distance
float GetDst(float Xx, float Yy, float xX, float yY)
{
	return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
}

struct AimEspInfo_t
{
	float vOutX, vOutY, vOutZ;
	float CrosshairDst;
};
std::vector<AimEspInfo_t>AimEspInfo;


//w2s
int WorldViewCBnum = 2; //2
int ProjCBnum = 1;//1
int matProjnum = 16;//16

ID3D11Buffer* pWorldViewCB = nullptr;
ID3D11Buffer* pProjCB = nullptr;

ID3D11Buffer* m_pCurWorldViewCB = NULL;
ID3D11Buffer* m_pCurProjCB = NULL;

float matWorldView[4][4];
float matProj[4][4];

float* worldview;
float* proj;

void AddModel(ID3D11DeviceContext * pContext)
{
	pContext->VSGetConstantBuffers(WorldViewCBnum, 1, &pWorldViewCB);	//WorldViewCBnum
	pContext->VSGetConstantBuffers(ProjCBnum, 1, &pProjCB);				//ProjCBnum

	if (pWorldViewCB == nullptr)
	{
		SAFE_RELEASE(pWorldViewCB); return;
	}
	if (pProjCB == nullptr)
	{
		SAFE_RELEASE(pProjCB); return;
	}

	if (pWorldViewCB != nullptr && pProjCB != nullptr)
	{
		m_pCurWorldViewCB = CopyBufferToCpuA(pWorldViewCB);
		m_pCurProjCB = CopyBufferToCpuB(pProjCB);
	}

	if (m_pCurWorldViewCB == nullptr)
	{
		SAFE_RELEASE(m_pCurWorldViewCB); return;
	}
	if (m_pCurProjCB == nullptr)
	{
		SAFE_RELEASE(m_pCurProjCB); return;
	}
	
	if (m_pCurWorldViewCB != nullptr && m_pCurProjCB != nullptr)
	{
		MapBuffer(m_pCurWorldViewCB, (void**)&worldview, NULL);
		memcpy(matWorldView, &worldview[0], sizeof(matWorldView));
		UnmapBuffer(m_pCurWorldViewCB);
		MapBuffer(m_pCurProjCB, (void**)&proj, NULL);
		memcpy(matProj, &proj[matProjnum], sizeof(matProj));			//matProjnum
		UnmapBuffer(m_pCurProjCB);
	}

}

#define CHECK_FATAL(cond, msg) do { if (!(cond)) { MessageBoxA(NULL, msg, "FATAL ERROR", 0); ExitProcess(1); } } while (0)
#define COUNTOF(arr) (sizeof(arr)/sizeof(0[arr]))


#include <d3dcommon.h>
#include "imgui/imgui.h"






static uint64_t FNV1a(const uint8_t* data, size_t size)
{
	uint64_t hash = 14695981039346656037ULL;
	for (size_t i = 0; i < size; i++)
	{
		hash ^= data[i];
		hash *= 1099511628211ULL;
	}
	return hash;
}

//static BOOL dump;
static WCHAR d3d11_shaders[MAX_PATH];
static void ShaderDump(const char* type, const char* ext, uint64_t id, const void* data, DWORD size)
{
	CreateDirectoryW(d3d11_shaders, NULL);

	WCHAR path[1024];
	//wsprintfW(path, L"D:\\dumpshader.hlsl", d3d11_shaders, type, id, ext);
	wsprintfW(path, L"%s\\%S_%016I64x.%S", d3d11_shaders, type, id, ext);

	HANDLE f = CreateFileW(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (f != INVALID_HANDLE_VALUE)
	{
		DWORD written;
		BOOL ok = WriteFile(f, data, size, &written, NULL);
		if (!ok || written != size)
		{
			// TODO: report error
			CHECK_FATAL(0, "Error writing to file!");
		}
		CloseHandle(f);
	}
	else
	{
		// TODO: report error
		CHECK_FATAL(0, "Error creating output file!");
	}
}

static void ShaderDisassemble(const char* type, uint64_t id, const void* bytecode, DWORD bytecode_size)
{
	UINT flags = D3D_DISASM_ENABLE_DEFAULT_VALUE_PRINTS | D3D_DISASM_ENABLE_INSTRUCTION_OFFSET;

	ID3DBlob* blob;
	HRESULT hr = D3DDisassemble(bytecode, bytecode_size, flags, "", &blob);
	if (SUCCEEDED(hr))
	{
		// ID3D10Blob is same as ID3DBlob
		//LPVOID buffer = ID3D10Blob_GetBufferPointer(blob); //C
		LPVOID buffer = (DWORD*)blob->GetBufferPointer(); //C++

		//SIZE_T buffer_size = ID3D10Blob_GetBufferSize(blob);
		SIZE_T buffer_size = blob->GetBufferSize();

		ShaderDump(type, "asm", id, buffer, (DWORD)buffer_size);

		SAFE_RELEASE(blob);
	}
}









static void ShaderHook(ID3D11Device* device, const char* type, const void** bytecode, SIZE_T* bytecode_size)
{
	//Log("1");
	//uint64_t id = FNV1a(*bytecode, *bytecode_size);
	//uint64_t id = FNV1a((uint8_t *)bytecode, *bytecode_size); //crashtown
	uint64_t id = 1; 

	//if (dump)
	//{
		//Log("2");
		ShaderDump(type, "bin", id, *bytecode, (DWORD)*bytecode_size);
		ShaderDisassemble(type, id, *bytecode, (DWORD)*bytecode_size);
	//}

	//Log("3");
	WCHAR hlsl[1024];
	//wsprintfW(hlsl, L"D:\\dumpshader.hlsl", d3d11_shaders, type, id);
	wsprintfW(hlsl, L"%s\\%S_%016I64x.hlsl", d3d11_shaders, type, id);
	//Log("4");
	if (GetFileAttributesW(hlsl) != INVALID_FILE_ATTRIBUTES)
	{
		//Log("5");
		//D3D_FEATURE_LEVEL level = ID3D11Device_GetFeatureLevel(device);
		D3D_FEATURE_LEVEL level = device->GetFeatureLevel();

		int version;
		if (level == D3D_FEATURE_LEVEL_11_1 || level == D3D_FEATURE_LEVEL_11_0)
		{
			version = 50;
		}
		else if (level == D3D_FEATURE_LEVEL_10_1)
		{
			version = 41;
		}
		else if (level == D3D_FEATURE_LEVEL_10_0)
		{
			version = 40;
		}
		else
		{
			// TODO: report error
			return;
		}
		
		char target[16];
		wsprintfA(target, "%s_%u_%u", type, version / 10, version % 10);

		ID3DBlob* code = NULL;
		ID3DBlob* error = NULL;

		HRESULT hr = D3DCompileFromFile(hlsl, NULL, NULL, "main", target, D3DCOMPILE_OPTIMIZATION_LEVEL2 | D3DCOMPILE_WARNINGS_ARE_ERRORS, 0, &code, &error);

		if (error != NULL)
		{
			WCHAR txt[1024];
			//wsprintfW(txt, L"D:\\errorhlsl.txt", d3d11_shaders, type, id);
			wsprintfW(txt, L"%s\\%S_%016I64x.hlsl.txt", d3d11_shaders, type, id);

			//const void* error_data = ID3D10Blob_GetBufferPointer(error);
			const void* error_data = (DWORD*)error->GetBufferPointer();

			//DWORD error_size = (DWORD)ID3D10Blob_GetBufferSize(error);
			DWORD error_size = error->GetBufferSize();

			HANDLE f = CreateFileW(txt, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (f != INVALID_HANDLE_VALUE)
			{
				DWORD written;
				BOOL ok = WriteFile(f, error_data, error_size, &written, NULL);
				if (!ok || written != error_size)
				{
					// TODO: report error
				}
				CloseHandle(f);
			}

			SAFE_RELEASE(error);
		}

		if (SUCCEEDED(hr) && code != NULL)
		{
			// do not release code blob, small memory "leak", but whatever
			//*bytecode = ID3D10Blob_GetBufferPointer(code);
			*bytecode = (DWORD*)code->GetBufferPointer();

			//*bytecode_size = ID3D10Blob_GetBufferSize(code);
			*bytecode_size = code->GetBufferSize();
		}
	}
}
