#include "Receiver.h"
#include "TransferableData.h"

AReceiver::AReceiver()
{
	listen_socket = NULL;
}

void AReceiver::BeginPlay()
{
	Super::BeginPlay();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10000.0f, FColor::Green, TEXT("Receiver"));
	StartReceiver(FString("listen_socket"), FString("127.0.0.1"), 8890);
}

void AReceiver::Receive(const FArrayReaderPtr & array_reader, const FIPv4Endpoint & end_point)
{
	FTransferableData data; 
	*array_reader << data;

	BPEvent_DataReceived(data);
}

bool AReceiver::StartReceiver(const FString & socket_name, const FString & ip, const int32 port)
{
	FIPv4Address address; 
	FIPv4Address::Parse(ip, address);

	FIPv4Endpoint Endpoint(address, port);

	int32 buffer_size = 2*1024*1024;

	listen_socket = FUdpSocketBuilder(*socket_name).AsNonBlocking().AsReusable().BoundToEndpoint(Endpoint).WithReceiveBufferSize(buffer_size);

	FTimespan thread_wait_time = FTimespan::FromMilliseconds(100); 
	receiver = new FUdpSocketReceiver(listen_socket, thread_wait_time, TEXT("UDP RECEIVER"));
	receiver->OnDataReceived().BindUObject(this, &AReceiver::Receive);
	receiver->Start();

	return true;
}

void AReceiver::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	receiver->Stop();
	delete receiver;
	receiver = nullptr;

	if(listen_socket)
	{ 
		listen_socket->Close(); ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(listen_socket);
	} 
}
