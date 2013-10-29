del ..\UnityBulletTest\BulletInterface*.dll
del ..\UnityBulletTest\Assets\Plugins\BulletDotNet.dll

mklink ..\UnityBulletTest\BulletInterfaceDebug.dll Binaries\BulletInterfaceDebug.dll
mklink ..\UnityBulletTest\BulletInterfaceRelease.dll Binaries\BulletInterfaceRelease.dll
mklink ..\UnityBulletTest\Assets\Plugins\BulletDotNet.dll Binaries\BulletDotNet.dll
