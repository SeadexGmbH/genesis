#!/bin/bash

echo off

export directoryToUse=$1

echo Generate PDF file...

# Generate PDF file using asciidoctor-pdf gem of ruby.
asciidoctor -r asciidoctor-pdf -b pdf -d book -a rouge-style=monokai -a compress -a allow-uri-read -a cache-uri -a pdf-theme=$directoryToUse/themes/basic-theme.yml $directoryToUse/index.adoc

echo Done.
