#include "curl/curl.h"
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qmainwindow.h>
#include "mp4decrypt/decryption_processor.h"
#include "sdl/sdl_init.h"

extern "C" {
#include "libavformat/avformat.h"
#include "libxml/parser.h"
#include "libxml/tree.h"
}

using namespace std;


int main(int argc, char *argv[]) {

	const char* a = avformat_license();
	
	xmlDocPtr doc;
	xmlNodePtr cur;

	curl_version_info_data * vinfo = curl_version_info(CURLVERSION_NOW);
	if (vinfo->features & CURL_VERSION_SSL) {
		// SSL support enabled
	}
	else {
		return -1;
	}

	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		return -1;
	}

    DecryptionProcessor processor = DecryptionProcessor();
    
	QApplication* app = new QApplication(argc, argv);
	QMainWindow mainWindow = QMainWindow();
	mainWindow.setFixedSize(1920, 1080);

	mainWindow.show();

	return app->exec();
}
