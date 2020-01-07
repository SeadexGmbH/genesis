@echo off
if exist asciidoc_base_generator/node_modules (
	node asciidoc_base_generator/toHtml.js sources
	)
if not exist asciidoc_base_generator/node_modules (
	echo Installing necessary software...
	cd asciidoc_base_generator
	call install_node_modules.bat
	call install_asciidoctor_gem.bat
	cd ..
	echo Done with installation.
	node asciidoc_base_generator/toHtml.js sources
)

if not exist release mkdir release
if not exist release\.images mkdir "release\.images"

REM generate the PDF file using ruby and asciidoctor-pdf gem.
call ./asciidoc_base_generator/toPdf.bat ./sources

copy "sources\index.pdf" "release" /y
copy "sources\index.html" "release" /y
copy "sources\.images\*.*" "release\.images\" /y

del /f "sources\index.pdf"
del /f "sources\index.html"

echo DONE.