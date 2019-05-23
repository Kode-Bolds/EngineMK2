#pragma once
#include "AntTweakBar.h"
#include <d3d11.h>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <wrl.h>
#include "ResourceManager.h"
#include <CommonStates.h>
#include <xaudio2.h>

// Windows Media Foundation
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid")


class AudioManager
{
private:
	std::shared_ptr<ResourceManager> mResourceManager = ResourceManager::Instance();

	
	int mDeviceWidth;
	int mDeviceHeight;
	Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

	Microsoft::WRL::ComPtr<IXAudio2> dev;
	IXAudio2MasteringVoice* masterVoice;

	Microsoft::WRL::ComPtr<IMFAttributes> sourceReaderConfiguration;

	//Private constructor for singleton pattern
	AudioManager();

public:
	~AudioManager();
	

	//Singleton pattern
	//Deleted copy constructor and assignment operator so no copies of the singleton instance can be made
	AudioManager(const AudioManager& pGUIManager) = delete;
	AudioManager& operator=(AudioManager const&) = delete;

	static std::shared_ptr<AudioManager> Instance();



	// Standard GUI
	void Inititialise();
	void LoadAudioFile(const std::wstring& filename, std::vector<BYTE>& audioData, WAVEFORMATEX** wafeFormatEx, unsigned int& waveLength);

	// load sound
	// play sound
	// pause sound
	// stop sound
	// volume
	// pitch
	// speed


};