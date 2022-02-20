# export QMAKE=/opt/qt/6.2.2/gcc_64/bin/qmake
# export SRC_PATH=/home/rom/dev/qt/boxes-server
# export LD_LIBRARY_PATH=/lib/x86_64-linux-gnu:/opt/qt/6.2.2/gcc_64/lib
mkdir build
cd build
$QMAKE ..
make -j$(nproc)
make install INSTALL_ROOT=AppDir
wget https://github.com/linuxdeploy/linuxdeploy-plugin-qt/releases/download/continuous/linuxdeploy-plugin-qt-x86_64.AppImage
wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
chmod +x linuxdeploy*.AppImage

./linuxdeploy-x86_64.AppImage --appdir AppDir -e boxes-server -i $SRC_PATH/ic_app.png -d $SRC_PATH/boxes-server.desktop --plugin qt --output appimage
