#pragma once

// abstract class
class IPCStrategy
{
public:
	virtual void* GetIndexData() = 0;
	virtual void* GetInputData() = 0;
	virtual void* GetOutputData() = 0;
};

enum IPCTypeEnum
{
	kUnkownType = 0,
	kFileMappingType = 1,
	kCopyDataType = 2,
	kIPCTypeCount = 3
};

class IPCStrategyFactory
{
public:
	static IPCStrategy* GetIPCStrategy(IPCTypeEnum eIPCType);
	static IPCStrategy* GetActiveIPCStrategy();

private:
	static IPCStrategy* IPCStrategies[kIPCTypeCount];

};