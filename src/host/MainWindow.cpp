#include "MainWindow.hpp"

#include "PluginDataModel.hpp"

#include <QKeySequence>
#include <QMenuBar>

#include <nodes/DataModelRegistry>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/FlowViewStyle>

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

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
	setupMenu();

	CuteHost::setStyle();

	scene_ = new QtNodes::FlowScene(registerDataModels(), this);
	setCentralWidget(new QtNodes::FlowView(scene_));
}

void MainWindow::loadWorkspace()
{
	scene_->load();
}

void MainWindow::saveWorkspace()
{
	scene_->save();
}

void MainWindow::setupMenu()
{
	auto fileMenu = new QMenu(QObject::tr("File"));
	auto loadAction = fileMenu->addAction(QObject::tr("Load workspace"), this,
	                                      &MainWindow::loadWorkspace, QKeySequence("Ctrl+O"));
	auto saveAction = fileMenu->addAction(QObject::tr("Save workspace"), this,
	                                      &MainWindow::saveWorkspace, QKeySequence("Ctrl+S"));
	auto closeAction =
	    fileMenu->addAction(QObject::tr("Exit"), this, &QMainWindow::close, QKeySequence("Ctrl+X"));
	menuBar()->addMenu(fileMenu);
}

} // namespace CuteHost
