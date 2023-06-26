#include "Pch.h"
#include "Launcher.h"


int main()
{
    Launcher launcher;

    if (launcher.UpdatesAvailable())
    {
        // Show UI feedback indicating updates are being downloaded
        launcher.DownloadUpdatesAsync([&](bool success) {
            if (success)
            {
                // Show UI feedback indicating updates were successfully downloaded
                launcher.StartGameLoop();
            }
            else
            {
                // Handle download errors and display appropriate UI feedback
            }
            });
    }
    else
    {
        launcher.StartGameLoop();
    }

	return 0;
}