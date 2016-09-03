#include <Core/core.h>
#include <iostream>

Sping::Core::Core()
{
}

Sping::Core::~Core()
{
}

int Sping::Core::init()
{
	// Initting stuff, order matters
	this->settingsManager->init(this);
	this->setupDevice();
	this->windowManager->init(this);
	this->eventManager->init(this);

	return 0;
}

bool Sping::Core::run()
{
	return this->_device->run();
}

void Sping::Core::tick()
{
	this->eventManager->tick();
}

int Sping::Core::shutdown()
{
	std::cout << "Dropping main device!\n";
	this->_device->drop();

	return 0;
}

int Sping::Core::setupDevice()
{
	auto params = irr::SIrrlichtCreationParameters();
	params.AntiAlias = this->settingsManager->get("Device", "AntiAlias").getInt();
	params.Bits = this->settingsManager->get("Device", "Bits").getInt();
	params.DeviceType = static_cast<irr::E_DEVICE_TYPE>(this->settingsManager->get("Device", "DeviceType").getInt());
	params.DisplayAdapter = this->settingsManager->get("Device", "DisplayAdapter").getInt();
	params.Doublebuffer = this->settingsManager->get("Device", "DoubleBuffer").getBool();
	params.DriverMultithreaded = this->settingsManager->get("Device", "DriverMultithreaded").getBool();
	params.DriverType = static_cast<irr::video::E_DRIVER_TYPE>(this->settingsManager->get("Device", "DriverType").getInt());
	params.EventReceiver = this->eventManager.get();
	params.Fullscreen = this->settingsManager->get("Device", "Fullscreen").getBool();
	params.HandleSRGB = this->settingsManager->get("Device", "HandleSRGB").getBool();
	params.HighPrecisionFPU = this->settingsManager->get("Device", "HighPrecisionFPU").getBool();
	params.IgnoreInput = this->settingsManager->get("Device", "IgnoreInput").getBool();
	params.LoggingLevel = static_cast<irr::ELOG_LEVEL>(this->settingsManager->get("Device", "LoggingLevel").getInt());
	params.Stencilbuffer = this->settingsManager->get("Device", "Stencilbuffer").getBool();
	params.Stereobuffer = this->settingsManager->get("Device", "Stereobuffer").getBool();
	params.UsePerformanceTimer = this->settingsManager->get("Device", "UsePerformanceTimer").getBool();
	params.Vsync = this->settingsManager->get("Device", "Vsync").getBool();
	params.WindowId = nullptr;
	params.WindowSize.set(this->settingsManager->get("Device", "WindowSizeWidth").getInt(), this->settingsManager->get("Device", "WindowSizeHeight").getInt());
	params.WithAlphaChannel = this->settingsManager->get("Device", "WithAlphaChannel").getBool();
	params.ZBufferBits = this->settingsManager->get("Device", "ZBufferBits").getInt();

		this->_device = irr::createDeviceEx(
			params
			);
}
