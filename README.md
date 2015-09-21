# Description
Life Is Complex is a program for visualizing GML data, in this case the city of Hamburg, by using various data sets.
If you would like to add more buildings, please look at the *sources* section.

# Sources
This project mainly uses data sets from "Transparenzportal Hamburg", a website by the city of Hamburg that provides various information and statistics about it.

The XML files in `bin/resources/xmldata` have to be from the following ZIP file: `http://daten-hamburg.de/geographie_geologie_geobasisdaten/3D_Stadtmodell/LoD1_HH_2015-03-25.zip` (main page: `http://suche.transparenz.hamburg.de/dataset/3d-stadtmodell-hamburg`).

The noise data in `bin/resources/maps/noise.png` is a rendered WMS map created by using the following URL: `(will be added later)` (main page: `http://suche.transparenz.hamburg.de/dataset/larmkarten-hamburg-47c-blmschg`).

The tree data in `bin/resources/maps/trees.xml` is a XML file created by a PHP script using the GML file from the following ZIP file: `http://daten-hamburg.de/umwelt_klima/strassenbaumkataster/Strassenbaumkataster_HH_2014-02-17_GML.zip` (main page: `http://suche.transparenz.hamburg.de/dataset/strassenbaumkataster-hamburg`).

# To do
* Do not have a flat pixel map below the buidings which only consists of a huge single PNG file (currently `bin/resources/maps/bg.png`) but either a vector map (which will have to be rendered by OpenGL) or a map that consists of chunks. It also should represent the terrain in 3D (hills, valleys, rivers, sea). It could be also possible for the map chunks to become loaded dynamically from the internet (e.g. by using OpenStreetMap).
* The possibility for rendering polygon shapes. Currently, the program only renders quadrilateral shapes and ignores polygons completely, because it doesn't know an algorithm for subdividing them into triangles yet.
* Some nice visual effects like shadows, a sun, clouds...
* A method that prevents many buildings from eating up gigabytes of RAM. For example, if the program loads 800 MB buildings XML data (see *Sources*) it needs ~1.5GB memory and ~1 minute to load.
* A platform independent Makefile or something similar.
* A directory that contains all external libraries for making it unnecessary to install them all manually (SDL, SDL_ttf, SFML, Boost, GLEW, GLM, RapidXML).
