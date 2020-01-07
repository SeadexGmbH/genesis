#!/bin/bash

cd $PWD/docs

node asciidoc_base_generator/toHtml.js sources
echo Done generating the HTML files.

# Generate the PDF file using ruby and asciidoctor-pdf gem.
chmod +rx ./asciidoc_base_generator/toPdf.sh
./asciidoc_base_generator/toPdf.sh ./sources

if [ ! -d "release" ]; then
	mkdir release
fi

cp -rf sources/index.pdf release
cp -rf sources/index.html release

if [ ! -d "release/.images" ]; then
	mkdir -p release/.images
fi

cp -rf sources/.images/*.* release/.images/

rm -rf sources/index.pdf
rm -rf sources/index.html

echo DONE.