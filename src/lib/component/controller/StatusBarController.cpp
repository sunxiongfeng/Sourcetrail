#include "component/controller/StatusBarController.h"

#include "component/view/StatusBarView.h"

StatusBarController::StatusBarController()
	: MessageListener<MessageError>(true)
	, MessageListener<MessageFinishedParsing>(true)
	, MessageListener<MessageLoadProject>(true)
	, MessageListener<MessageLoadSource>(true)
	, MessageListener<MessageRefresh>(true)
	, MessageListener<MessageStatus>(true)
{
}

StatusBarController::~StatusBarController()
{
}

StatusBarView* StatusBarController::getView()
{
	return Controller::getView<StatusBarView>();
}

void StatusBarController::handleMessage(MessageFinishedParsing* message)
{
	setStatus("Parsing Finished");
}

void StatusBarController::handleMessage(MessageStatus* message)
{
	setStatus(message->status);
}

void StatusBarController::handleMessage(MessageError* message)
{
	setStatus(message->error, true);
}

void StatusBarController::handleMessage(MessageLoadProject* message)
{
	setStatus("Loading Project: " + message->projectSettingsFilePath);
}

void StatusBarController::handleMessage(MessageLoadSource* message)
{
	setStatus("Loading Source: " + message->sourceDirectoryPath);
}

void StatusBarController::handleMessage(MessageRefresh* message)
{
	setStatus("Refreshing Project");
}

void StatusBarController::setStatus(const std::string& status, bool isError)
{
	if (!status.empty())
	{
		getView()->showMessage(status, isError);
	}
}
