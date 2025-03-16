#include "curl/curl.h"
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qmainwindow.h>
#include <QtWidgets/qopenglwidget.h>
#include "mp4decrypt/decryption_processor.h"
#include "SDL3/SDL_init.h"
#include <GL/glu.h>
#include <GL/gl.h>

extern "C" {
#include "libavformat/avformat.h"
#include "libxml/parser.h"
#include "libxml/tree.h"
}

class OGLWidget : public QOpenGLWidget {
 
public:
	OGLWidget(QWidget *parent = 0) : QOpenGLWidget(parent) { }
	~OGLWidget() { }

protected:
	void initializeGL() {
		glClearColor(0, 0, 0, 1);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHTING);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	}
 
	void resizeGL(int w, int h) {
		glViewport(0, 0, w, h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, (float)w / h, 0.01, 100.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
	}
 
	void paintGL() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, 0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.5, -0.5, 0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.5, 0);
		glEnd();
	}
};


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
    OGLWidget* ow = new OGLWidget(&mainWindow);
    ow->setFixedSize(1280, 720);

	mainWindow.show();

	return app->exec();
}
