#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QSGRendererInterface>

int main(int argc, char* argv[]) {
// the default API on windows has really bad resize performance as of Qt6.4
// clang-format off
	#ifdef Q_OS_WINDOWS
	if (qEnvironmentVariableIsEmpty("QSG_RHI_BACKEND")) {
		QQuickWindow::setGraphicsApi(QSGRendererInterface::Vulkan);
	}
	#endif
	// clang-format on

	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	QObject::connect(
	    &engine,
	    &QQmlApplicationEngine::objectCreationFailed,
	    &app,
	    []() { QCoreApplication::exit(-1); },
	    Qt::QueuedConnection
	);

	engine.loadFromModule("EasyFFMPEG", "Main");

	return app.exec();
}
