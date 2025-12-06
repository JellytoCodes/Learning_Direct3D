
#pragma once

#include "d3dUtil.h"
#include "GameTimer.h"

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

class D3DApp
{
protected :

	D3DApp(HINSTANCE hInstance);
	D3DApp(const D3DApp& rhs) = delete;
	D3DApp& operator=(const D3DApp& rhs) = delete;

	/**
	 *	D3DApp가 획득한 COM 인터페이스들을 해제하고, 명령 대기열을 비운다.
	 *	소멸자에서 명령 대기열을 비우는 이유는, GPU가 참조하는 자원들을 안전하게 파괴하려면
	 *	GPU가 명령 대기열에 있는 명령들의 처리를 마칠 때까지 기다려야하기 때문이다.
	 *	그렇게 하지 않으면 응용 프로그램 종료 시 GPU 가 충돌(Crash)할 수 있다.
	 */
	virtual ~D3DApp();

public :
	static D3DApp* GetApp();

	/**
	 *	AppInst					: 응용 프로그램 인스턴스 핸들의 복사본을 돌려주는 자명한 접근 함수
	 *	MainWnd					: 주 창 핸들의 복사본을 돌려주는 자명한 접근 함수.
	 *	AspectRatio				: 후면 버퍼의 종횡비(aspect ratio), 즉 높이에 대한 너비의 비율을 돌려준다.
	 */
	HINSTANCE	AppInst() const;
	HWND		MainWnd() const;
	float		AspectRatio() const;

	/**
	 *	Get4xMsaaState			: 4X MSAA가 활성화되어 있으면 true, 그렇지 않으면 false 반환한다.
	 *  Set4xMsaaState			: 4X MSAA를 활성화 또는 비활성화한다.
	 */
	bool Get4xMsaaState() const;
	void Set4xMsaaState(bool value);

	/**
	 *	응용 프로그램 메시지 루프를 감싼 메서드이다.
	 *	Windows 메시지가 전혀 없을 때에도 게임의 논리(Logic)를 처리할 수 있도록,
	 *	이 메서드는 Win32 PeekMessage 함수를 사용한다.
	 */
	int Run();

	/**
	 *	Initialize				: 자원 할당, 장면 물체 초기화, 광원 설정 등 응용 프로그램 고유의 초기화 코드
	 *	MsgProc					: 응용 프로그램 주 창의 메시지 처리부를 넣는다.
	 */
	virtual bool Initialize();
	virtual LRESULT MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected :
	/**
	 *	CreateRtvAndDsvDescriptorHeaps	: RTV 서술자와 DSV 서술자를 응용 프로그램에 맞게 생성하는 데 쓰이는 가상 함수이다.
	 *	OnResize						: 후면 버퍼와 깊이·스텐실 버퍼의 크기 갱신에 쓰이는 가상 함수이다.
	 *	Update							: 시간의 흐름에 따른 응용 프로그램 갱신을 위해 매 프레임 호출되는 함수이다.
	 *	Draw							: 현재 프레임을 후면 버퍼에 실제로 그리기 위한 렌더링 명령들을 제출하는 작업을 수행하기 위해 매 프레임 호출되는 함수이다.
	 */
	virtual void CreateRtvAndDsvDescriptorHeaps();
	virtual void OnResize();
	virtual void Update(const GameTimer& gt)=0;
	virtual void Draw(const GameTimer& gt)=0;

	// 마우스 입력 처리를 위한 가상 함수들
	virtual void OnMouseDown(WPARAM btnState, int x, int y) { }
	virtual void OnMouseUp(WPARAM btnState, int x, int y) { }
	virtual void OnMouseMove(WPARAM btnState, int x, int y) { }

protected :
	/**
	 *	InitMainWindow			: 응용 프로그램의 주 창을 초기화한다.
	 *	InitDirect3D			: Direct3D를 초기화한다.
	 *	CreateCommandObjects	: 명령 대기열 하나와 명령 목록 할당자 하나, 명령 목록 하나를 생성한다.
	 */
	bool InitMainWindow();
	bool InitDirect3D();
	void CreateCommandObjects();

	/**
	 *	CreateSwapChain			: 교환 사슬을 생성한다.
	 */
	void CreateSwapChain();

	/**
	 *	FlushCommandQueue		: GPU가 명령 대기열에 있는 모든 명령의 처리를 마칠 떄까지 CPU가 기다리게 만든다.
	 */
	void FlushCommandQueue();

	/**
	 *	CurrentBackBuffer		: 교환 사슬의 현재 후면 버퍼에 대한 ID3D12Resource를 돌려준다.
	 *	CurrentBackBufferView	: 현재 후면 버퍼에 대한 RTV(렌더 대상 뷰)를 돌려준다.
	 *  DepthStencilView		: 현재 후면 버퍼에 대한 DSV(깊이·스텐실 뷰)를 돌려준다.
	 */
	ID3D12Resource* CurrentBackBuffer() const;
	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView() const;
	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView() const;
	
	/**
	 *	CalculateFrameStats		: 평균 초당 프레임 수(FPS)와 평균 프레임당 밀리초를 계산한다.
	 */
	void CalculateFrameStats();

	/**
	 *	LogAdapters				: 시스템의 모든 디스플레이 어댑터를 열거한다.
	 *	LogAdapterOutputs		: 주어진 어댑터와 연관된 모든 출력을 열거한다.
	 *	LogOutputDisplayModes	: 주어진 출력과 픽셀 형식의 조합이 지워하는 모든 디스플레이 모드를 나열한다.
	 */
	void LogAdapters();
	void LogAdapterOutputs(IDXGIAdapter* adapter);
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format);

protected :
	static D3DApp* mApp;

	/**
	 *	mhAppInst			: 응용 프로그램 인스턴스 핸들
	 *	mhMainWnd			: 주 창 핸들
	 *	mAppPaused			: 응용 프로그램 일시 정지 여부 체크
	 *	mMinimized			: 응용 프로그램 최소화 여부 체크
	 *	mMaximized			: 응용 프로그램 최대화 여부 체크
	 *	mResizing			: 사용자가 크기 조정용 테두리를 끌고 있는지 체크
	 *	mFullscreenState	: 전체화면 활성화 여부
	 */
	HINSTANCE mhAppInst = nullptr;
	HWND mhMainWnd = nullptr;
	bool mAppPaused = false;
	bool mMinimized = false;
	bool mMaximized = false;
	bool mResizing = false;
	bool mFullscreenState = false;

	/**
	 * true로 설정하면 4X MSAA가 적용된다. default = false;
	 *	m4xMSAAState		: 4X MSAA 활성화 여부
	 *	m4xMSAAQuality		: 4X MSAA 품질 수준 
	 */
	bool m4xMsaaState = false;			
	UINT m4xMsaaQuality = 0;

	// 경과 시간과 게임 전체 시간 측정
	GameTimer mTimer;

	Microsoft::WRL::ComPtr<IDXGIFactory4> mdxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> md3dDevice;

	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
	UINT64 mCurrentFence = 0;

	Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;

	static const int SwapChainBufferCount = 2;
	int mCurrBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;

	D3D12_VIEWPORT mScreenViewport;
	D3D12_RECT mScissorRect;

	UINT mRtvDescriptorSize = 0;
	UINT mDsvDescriptorSize = 0;
	UINT mCbvSrvUavDescriptorSize = 0;

	/**
	 *	파생 클래스는 자신의 생성자에서 이 멤버 변수들을
	 *	자신의 목적에 맞는 초기 값들로 설정해야 한다.
	 */
	std::wstring mMainWndCaption = L"d3d App";
	D3D_DRIVER_TYPE md3dDriverType = D3D_DRIVER_TYPE_HARDWARE;
	DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
	DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	int mClientWidth = 800;
	int mClientHeight = 600;
};


