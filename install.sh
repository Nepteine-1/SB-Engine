#!/bin/sh

# Change this env variable to change the name of the executable generated with cmake
export TITLE="SFML_App"

printb() {
    tput setaf $2
    tput bold
    echo $1
    tput sgr0
}

printb "#==== Launching installation ====#" 2
cd build
cmake .
cmake --build . --config Release
cmake --install .
rm $TITLE
cd ..

printb "#==== Installation finished ====#" 2
