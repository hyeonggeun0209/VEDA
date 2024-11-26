make clean
make
opensdk_packager
opensdk_install -a test_BestShot -i 172.26.1.222 -u admin -w ac-12457
RemoteDebugViewer -i 172.26.1.222 -p 80 -u admin -w ac-12457 -d 8081 -a test_BestShot
