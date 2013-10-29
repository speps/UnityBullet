del ..\UnityBulletTest\BulletInterface*.dll
del ..\UnityBulletTest\Assets\Plugins\BulletDotNet.dll

copy Binaries\BulletInterface*.dll ..\UnityBulletTest
md ..\UnityBulletTest\Assets\Plugins
copy Binaries\BulletDotNet.dll ..\UnityBulletTest\Assets\Plugins
