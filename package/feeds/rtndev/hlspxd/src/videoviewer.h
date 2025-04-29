#ifndef VIDEOVIEWER_H
#define VIDEOVIEWER_H

#include "utils.h"
#include <list>
// ������ � m3u8 �����
struct PlayListRecord
{
	std::string Tag;					// ��� - ����������� ����
	std::vector<std::string> Attributes;	// ��������
	Uri TsUri;					// URL - ���������� ��� �������������
};

// ��� ������ ������� ���������� ������
struct StremInf
{
	int Bandwidth;				// ����������
	Uri TsUri;					// URL - ���������� ��� �������������
	StremInf() :Bandwidth(0) {}

	bool operator < (const StremInf &other) const
	{
		return Bandwidth < other.Bandwidth;
	}
};

class TsURI : public Uri
{
public:
	double	Duration;						// ����� ������ ����� (sec)
	TsURI()
		:Duration(0)
	{}
	TsURI(const std::string & uri, double Duration)
		:Uri(uri), Duration(Duration)
	{}
	TsURI(Uri uri, double Duration)
		:Uri(uri), Duration(Duration)
	{}

	TsURI(const TsURI &other)
		:Uri(other), Duration(other.Duration)
	{}
};

struct TsPacketHdr
{
	union
	{
		uint32_t Uval;
		struct
		{
			uint32_t CC : 4;
			uint32_t AFC : 2;
			uint32_t TSC : 2;
			uint32_t PID : 13;
			uint32_t TP : 1;
			uint32_t PUSI : 1;
			uint32_t TEI : 1;
			uint32_t Sync : 8;
		}Sval;
	};
	TsPacketHdr(){}

	TsPacketHdr(void *buf)
	{
		Uval = ntohl(*((uint32_t*)buf));
	}
};

#define TS_FRAME_LEN 188
#define TS_FRAMES_IN_BUF 4
#define TS_BUF_LEN TS_FRAMES_IN_BUF*TS_FRAME_LEN

class VideoViewer
{
	socketstream VideoStream;			// �������� �����
	VideoQuality SessionQuality;		// �������� ������ �����
	Uri VideoUri;						// URI ������� ����������
	HttpClient M3U8Client;				// ������ ������� ��������
	char TsBuf[TS_BUF_LEN];				// �������� �����

	// ������
	static std::regex PlRx;				//15 = file
	std::vector<PlayListRecord> PlayList;	// ���������� ��������

	int	MaxHistLen;				// ����� �������

	std::list<TsURI> TsList;			// ������ �� ������

	HttpClient tsClient;

	void ReadM3U8();

public:
	VideoViewer(SOCKET ClientSocket);
	~VideoViewer();
	void Run();
	void Stop();
};

#endif
