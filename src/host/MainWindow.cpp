#include "MainWindow.hpp"

#include "AudioPluginHost.hpp"
#include "AudioPluginLibrary.hpp"
#include "PluginDataModel.hpp"

#include <nodes/DataModelRegistry>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/FlowViewStyle>

#include <QKeySequence>
#include <QMenuBar>
#include <QMessageBox>
#include <QProgressDialog>

namespace CuteHost {

namespace {

std::shared_ptr<QtNodes::DataModelRegistry> registerDataModels()
{
	auto ret = std::make_shared<QtNodes::DataModelRegistry>();
	ret->registerModel<CuteHost::PluginDataModel>();
	return ret;
}

void setStyle()
{
	QtNodes::FlowViewStyle::setStyle(
	    R"(
  {
    "FlowViewStyle": {
      "BackgroundColor": [53, 53, 53],
      "FineGridColor": [53, 53, 53],
      "CoarseGridColor": [53, 53, 53]
    }
  }
  )");
}

} // namespace

MainWindow::MainWindow() : pluginHost_(new AudioPluginHost)
{
	setupMenu();

	scene_ = new QtNodes::FlowScene(registerDataModels(), this);

	CuteHost::setStyle();
	auto flowView = new QtNodes::FlowView(scene_);
	flowView->setContextMenuPolicy(Qt::NoContextMenu);
	setCentralWidget(flowView);
}

MainWindow::~MainWindow() = default;

void MainWindow::loadWorkspace()
{
	scene_->load();
}

void MainWindow::saveWorkspace()
{
	scene_->save();
}

void MainWindow::insertPlugin()
{
	pluginHost_->loadPlugin(QUuid());
}

void MainWindow::removePlugin()
{
	pluginHost_->unloadPlugin(QUuid());
}

void MainWindow::scanForPlugins()
{
	QProgressDialog* progressDialog =
	    new QProgressDialog(tr("Scanning for plugins..."), tr("Cancel"), 0, 100, this);
	progressDialog->setWindowModality(Qt::WindowModal);
	progressDialog->setValue(0);

	AudioPluginLibrary::instance().scan(
	    [=](float progress) { progressDialog->setValue(static_cast<int>(progress * 100)); },
	    [=]() { return progressDialog->wasCanceled(); });
}

void MainWindow::showAboutDialog()
{
	QMessageBox::about(this, tr("About"),
	                   "CuteHost version " CUTEHOST_APPLICATION_VERSION
	                   " - free VST3 host application\n\n"
	                   "Author: Kirill Kirilenko aka UltraCoder (kirill@ultracoder.org)");
}

void MainWindow::setupMenu()
{
	auto fileMenu = new QMenu(tr("File"));
	auto loadAction = fileMenu->addAction(tr("Load workspace"), this, &MainWindow::loadWorkspace,
	                                      QKeySequence("Ctrl+O"));
	auto saveAction = fileMenu->addAction(tr("Save workspace"), this, &MainWindow::saveWorkspace,
	                                      QKeySequence("Ctrl+S"));
	auto closeAction =
	    fileMenu->addAction(tr("Exit"), this, &QMainWindow::close, QKeySequence("Ctrl+X"));
	menuBar()->addMenu(fileMenu);

	auto pluginMenu = new QMenu(tr("Plugins"));
	auto insertAction = pluginMenu->addAction(tr("Add plugin"), this, &MainWindow::insertPlugin,
	                                          QKeySequence("Insert"));
	auto removeAction = pluginMenu->addAction(tr("Remove plugin"), this, &MainWindow::removePlugin,
	                                          QKeySequence("Delete"));
	auto scanAction =
	    pluginMenu->addAction(tr("Scan for plugins"), this, &MainWindow::scanForPlugins);
	menuBar()->addMenu(pluginMenu);

	auto helpMenu = new QMenu(tr("Help"));
	auto aboutAction = helpMenu->addAction(tr("About"), this, &MainWindow::showAboutDialog);
	menuBar()->addMenu(helpMenu);
}

} // namespace CuteHost
