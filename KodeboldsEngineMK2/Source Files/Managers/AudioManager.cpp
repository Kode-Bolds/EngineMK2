#include "AudioManager.h"

AudioManager::~AudioManager()
{
	// shut down the media foundation
	MFShutdown();

	// destroy the master voice
	masterVoice->DestroyVoice();

	// stop the engine
	dev->StopEngine();
}

std::shared_ptr<AudioManager> AudioManager::Instance()
{
	static std::shared_ptr<AudioManager> instance{ new AudioManager };
	return instance;
}

void AudioManager::Inititialise()
{
	HRESULT hr = S_OK;

	// get an interface to the main XAudio2 device
	hr = XAudio2Create(dev.GetAddressOf());
	if (FAILED(hr))
	{
		//return std::runtime_error("Critical error: Unable to create the XAudio2 engine!");
	}

	// create master voice
	hr = dev->CreateMasteringVoice(&masterVoice);
	if (FAILED(hr))
	{
		//return std::runtime_error("Critical error: Unable to create the XAudio2 mastering voice!");
	}

	// initialize media foundation
	hr = MFStartup(MF_VERSION);
	if (FAILED(hr))
	{
		//	return std::runtime_error("Critical error: Unable to start the Windows Media Foundation!");
	}

	// initialize media foundation
	hr = MFStartup(MF_VERSION);
	if (FAILED(hr))
	{
		//return std::runtime_error("Critical error: Unable to start the Windows Media Foundation!");
	}

	// set media foundation reader to low latency
	hr = MFCreateAttributes(sourceReaderConfiguration.GetAddressOf(), 1);
	if (FAILED(hr))
	{
		//return std::runtime_error("Critical error: Unable to create Media Foundation Source Reader configuration!");
	}

	hr = sourceReaderConfiguration->SetUINT32(MF_LOW_LATENCY, true);
	if (FAILED(hr))
	{
		//return std::runtime_error("Critical error: Unable to set Windows Media Foundation configuration!");
	}

}

void AudioManager::LoadAudioFile(const std::wstring& filename, std::vector<BYTE>& audioData, WAVEFORMATEX** wafeFormatEx, unsigned int& waveLength)
{
	//// handle errors
	//HRESULT hr = S_OK;

	//// stream index
	//DWORD streamIndex = (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM;

	//// create the source reader
	//Microsoft::WRL::ComPtr<IMFSourceReader> sourceReader;
	//hr = MFCreateSourceReaderFromURL(filename.c_str(), sourceReaderConfiguration.Get(), sourceReader.GetAddressOf());
	//if (FAILED(hr))
	//	//return std::runtime_error("Critical error: Unable to create source reader from URL!");

	//// select the first audio stream, and deselect all other streams
	//	hr = sourceReader->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, false);
	//if (FAILED(hr))
	//	//return std::runtime_error("Critical error: Unable to disable streams!");

	//	hr = sourceReader->SetStreamSelection(streamIndex, true);
	//if (FAILED(hr))
	//	//return std::runtime_error("Critical error: Unable to enable first audio stream!");

	//// query information about the media file
	//	Microsoft::WRL::ComPtr<IMFMediaType> nativeMediaType;
	////hr = sourceReader->GetNativeMediaType(streamIndex, 0, nativeMediaType.GetAddressOf());
	//if (FAILED(hr))
	//	//return std::runtime_error("Critical error: Unable to query media information!");

	//// make sure that this is really an audio file
	//GUID majorType{};
	//hr = nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType);
	//if (majorType != MFMediaType_Audio)
	//	//return std::runtime_error("Critical error: the requested file is not an audio file!");

	//// check whether the audio file is compressed or uncompressed
	//GUID subType{};
	//hr = nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &subType);
	//if (subType == MFAudioFormat_Float || subType == MFAudioFormat_PCM)
	//{
	//	// the audio file is uncompressed
	//}
	//else
	//{
	//	// the audio file is compressed; we have to decompress it first
	//	// to do so, we inform the SourceReader that we want uncompressed data
	//	// this causes the SourceReader to look for decoders to perform our request
	//	Microsoft::WRL::ComPtr<IMFMediaType> partialType = nullptr;
	//	hr = MFCreateMediaType(partialType.GetAddressOf());
	//	if (FAILED(hr))
	//		//return std::runtime_error("Critical error: Unable create media type!");

	//	// set the media type to "audio"
	//	hr = partialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	//	if (FAILED(hr))
	//		//return std::runtime_error("Critical error: Unable to set media type to audio!");

	//	// request uncompressed data
	//	hr = partialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
	//	if (FAILED(hr))
	//		//return std::runtime_error("Critical error: Unable to set guid of media type to uncompressed!");

	//	hr = sourceReader->SetCurrentMediaType(streamIndex, NULL, partialType.Get());
	//	if (FAILED(hr))
	//		//return std::runtime_error("Critical error: Unable to set current media type!");
	//}

	//// uncompress the data and load it into an XAudio2 Buffer
	//Microsoft::WRL::ComPtr<IMFMediaType> uncompressedAudioType = nullptr;
	//hr = sourceReader->GetCurrentMediaType(streamIndex, uncompressedAudioType.GetAddressOf());
	//if (FAILED(hr))
	//	//return std::runtime_error("Critical error: Unable to retrieve the current media type!");

	//hr = MFCreateWaveFormatExFromMFMediaType(uncompressedAudioType.Get(), waveFormatEx, &waveFormatLength);
	//if (FAILED(hr))
	//	//return std::runtime_error("Critical error: Unable to create the wave format!");

	//// ensure the stream is selected
	//hr = sourceReader->SetStreamSelection(streamIndex, true);
	//if (FAILED(hr))
	//	//return std::runtime_error("Critical error: Unable to select audio stream!");

	//// copy data into byte vector
	//Microsoft::WRL::ComPtr<IMFSample> sample = nullptr;
	//Microsoft::WRL::ComPtr<IMFMediaBuffer> buffer = nullptr;
	//BYTE* localAudioData = NULL;
	//DWORD localAudioDataLength = 0;

	//while (true)
	//{
	//	DWORD flags = 0;
	//	hr = sourceReader->ReadSample(streamIndex, 0, nullptr, &flags, nullptr, sample.GetAddressOf());
	//	if (FAILED(hr))
	//		//return std::runtime_error("Critical error: Unable to read audio sample!");

	//	// check whether the data is still valid
	//		if (flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
	//			break;

	//	// check for eof
	//	if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
	//		break;

	//	if (sample == nullptr)
	//		continue;

	//	// convert data to contiguous buffer
	//	hr = sample->ConvertToContiguousBuffer(buffer.GetAddressOf());
	//	if (FAILED(hr))
	//		//return std::runtime_error("Critical error: Unable to convert audio sample to contiguous buffer!");

	//	// lock buffer and copy data to local memory
	//		hr = buffer->Lock(&localAudioData, nullptr, &localAudioDataLength);
	//	if (FAILED(hr))
	//		//return std::runtime_error("Critical error: Unable to lock the audio buffer!");

	//	for (size_t i = 0; i < localAudioDataLength; i++)
	//			audioData.push_back(localAudioData[i]);

	//	// unlock the buffer
	//	hr = buffer->Unlock();
	//	localAudioData = nullptr;

	//	if (FAILED(hr))
	//		//return std::runtime_error("Critical error while unlocking the audio buffer!");
	//}
}