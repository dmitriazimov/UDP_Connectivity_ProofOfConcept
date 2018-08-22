#include "Sender.h"
#include "TransferableData.h"
#include "Misc/DateTime.h"
#include "TimerManager.h"

ASender::ASender()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	sender_socket = NULL;
	count = 0;
}

void ASender::BeginPlay()
{
	Super::BeginPlay();
	StartUDPSender(FString("sender_socket"), FString("127.0.0.1"), 8890, false);
}
void ASender::SendString()
{
	if (!sender_socket) 
	{ 
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Green, TEXT("bad socket"));
	}

	int32 bytes_sent = 0;

	FTransferableData data;
	data.count = ++count;
	data.time_stamp = "Time stamp: " + (FDateTime::Now().GetTimeOfDay()).ToString() + " ";

	FArrayWriter writer;

	writer << data;

	sender_socket->SendTo(writer.GetData(), writer.Num(), bytes_sent, *remote_address);

	if (bytes_sent <= 0) 
	{ 
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, TEXT("nothing sent"));
	}
}

bool ASender::StartUDPSender(const FString & socket_name, const FString& ip, const int32 port, bool UDP)
{
	remote_address = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	bool ip_is_valid; 
	remote_address->SetIp(*ip, ip_is_valid); 
	remote_address->SetPort(port);

	if (!ip_is_valid)
	{ 
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Red, TEXT("Invalid sender IP"));
		return false;
	}

	sender_socket = FUdpSocketBuilder(*socket_name).AsReusable().WithBroadcast();

	check(sender_socket->GetSocketType() == SOCKTYPE_Datagram);

	int32 send_size = 2*1024*1024; 
	sender_socket->SetSendBufferSize(send_size, send_size); 
	sender_socket->SetReceiveBufferSize(send_size, send_size);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Green, TEXT("Sender initialized"));

	GetWorldTimerManager().SetTimer(send_timer, this, &ASender::SendString, 1.0f, true, 1.0f);

	return true;
}

void ASender::EndPlay(const EEndPlayReason::Type reason)
{
	if (sender_socket)
	{ 
		sender_socket->Close(); ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(sender_socket);
	}
}
