@echo off
cls

cd library
echo Download SFML-2.6.1
curl -LO "https://github.com/SFML/SFML/releases/download/2.6.1/SFML-2.6.1-windows-vc17-64-bit.zip"
echo Download GLM-1.0.1
curl -LO "https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.zip"

tar -xf glm-1.0.1-light.zip
tar -xf SFML-2.6.1-windows-vc17-64-bit.zip

del glm-1.0.1-light.zip
del SFML-2.6.1-windows-vc17-64-bit.zip


cd ..

cd build
cmake .
cmake --build . --target ALL_BUILD --config Release

pause