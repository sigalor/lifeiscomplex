# Description
Life Is Complex is a program for visualizing GML data, in this case the city of Hamburg, by using various data sets.
If you would like to add more buildings, please look at the *sources* section.

# Sources
This project mainly uses data sets from "Transparenzportal Hamburg", a website by the city of Hamburg that provides various information and statistics about it.

The XML files in `bin/resources/xmldata` have to be from the following ZIP file: `http://daten-hamburg.de/geographie_geologie_geobasisdaten/3D_Stadtmodell/LoD1_HH_2015-03-25.zip` (main page: `http://suche.transparenz.hamburg.de/dataset/3d-stadtmodell-hamburg`).

The noise data in `bin/resources/maps/noise.png` is a rendered WMS map created by using the following URL: `(will be added later)` (main page: `http://suche.transparenz.hamburg.de/dataset/larmkarten-hamburg-47c-blmschg`).

The tree data in `bin/resources/maps/trees.xml` is a XML file created by a PHP script using the GML file from the following ZIP file: `http://daten-hamburg.de/umwelt_klima/strassenbaumkataster/Strassenbaumkataster_HH_2014-02-17_GML.zip` (main page: `http://suche.transparenz.hamburg.de/dataset/strassenbaumkataster-hamburg`).
