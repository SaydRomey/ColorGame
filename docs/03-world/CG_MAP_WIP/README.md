# Map Side-Project

## Files in the `zip` folder

`index.html` self-contained interactive top-down map with zoom/pan, layer
toggles, clickable regions, cities, landmarks, and causeways.

`shattered_realm_prototype.geojson` exported vector data for future use in
Leaflet, QGIS, MapLibre, or Tiled.

`README.md` basic usage notes.

Open `index.html` in a browser.

---

Use a **tile-based interactive map**, not image generation.

Best option for this project: **Leaflet + custom map tiles + GeoJSON/SVG
overlays**.  
Leaflet is built for interactive zoomable maps with tile layers, markers,
popups, vector polygons, GeoJSON, pan/zoom, layer controls, and scale
controls.  
It is lightweight and open source. ([Leaflet][1])

The workflow would be:

Create a real top-down “world coordinate system” for your map, probably an
artificial square coordinate plane rather than real latitude/longitude.

Trace the seven region shapes from your reference image as vector polygons:
Myrrala, Huevale, Iriseld, Nullshade, Luxeran, Vireya, Auralith.

Add layers for terrain: roads, borders, rivers/channels, mountain ranges,
forests, swamps, lava flows, dunes, ruins, gates, towns, landmarks.

Export the base terrain as map tiles at multiple zoom levels, like a real web
map.

Use Leaflet to make an expandable HTML map where users can zoom, pan, click
landmarks, toggle layers, and later add more detail without repainting the whole
thing.

For editing the actual map data, the best companion tools are:

**QGIS** if you want a serious cartographic workflow. It can draw/edit points,
lines, polygons, and map layers with precision, then export large-format maps or
web-ready data. It is free/open source and designed for map production and layer
editing. ([QGIS][2])

**Tiled Map Editor** if you want it to behave more like a game-world/level map.
Tiled supports orthogonal, isometric, and hex maps, multi-layer tile editing,
object layers, infinite maps that grow as needed, and export formats including
JSON. ([Tiled][3])

**MapLibre GL JS** if you want something more advanced than Leaflet, especially
vector tiles, dynamic styling, smooth zooming, 3D terrain/building-style
effects, or heavier web-map behavior. It supports GeoJSON, raster tiles, vector
tile sources, markers, popups, navigation controls, scale controls, and
terrain-related examples. ([MapLibre][4])

For your stated goal, I would not use DALL·E/image generation as the main tool.
It is useful for mood art, but it will distort labels, invent details, and fail
at consistent cartography. The better structure is:

**Design source:** QGIS or Tiled **Data format:** GeoJSON / JSON / SVG layers
**Viewer:** Leaflet **Output:** an offline HTML folder you can open in a
browser, with zoomable regions and clickable lore markers

I can build a first prototype as a downloadable local HTML map: black-and-white
top-down layout, zoom/pan, region polygons, clickable labels, and a layer toggle
for towns, landmarks, biomes, and gates.

[1]:
  https://leafletjs.com/
  "Leaflet - a JavaScript library for interactive maps"
[2]: https://qgis.org/ "Spatial without Compromise · QGIS"
[3]: https://www.mapeditor.org/ "Tiled | Flexible level editor"
[4]: https://maplibre.org/maplibre-gl-js/docs/ "Introduction - MapLibre GL JS"

---

Use this stack:

**Core stack: QGIS → GeoJSON → Leaflet**

Use **QGIS** as the map-authoring tool. This is where you should draw and refine
region polygons, roads, borders, rivers/channels, biome areas, gates, town
points, landmark points, and label positions. QGIS supports vector formats
including GeoJSON, GeoPackage, KML, shapefiles, DXF, and many raster formats, so
it is a good master-editing environment for map data. ([QGIS Documentation][1])

Use **GeoJSON** as the main data format. Store every map object as a feature:
region polygons, causeway lines, town points, landmark points, biome zones,
dungeon entrances, faction zones, and quest gates. Leaflet directly supports
GeoJSON layers and can style points, lines, and polygons, bind popups, filter
features, and attach per-feature behavior. ([Leaflet][2])

Use **Leaflet** as the viewer. It gives you pan, zoom, draggable maps, layers,
popups, tooltips, markers, vector layers, tile layers, layer controls, and scale
controls. For your fictional world, use Leaflet with `CRS.Simple`, meaning the
map uses your own fantasy pixel/grid coordinates instead of real-world
latitude/longitude. Leaflet’s API is built around map creation, zooming,
panning, layers, controls, markers, popups, tooltips, tile layers, vectors, and
GeoJSON. ([Leaflet][2])

Use **SVG or raster tiles** for the base map. In the early version, keep it pure
vector: GeoJSON polygons and lines rendered directly in Leaflet. Later, when the
base terrain gets complex, export a black-and-white base map from QGIS/Inkscape
as image tiles, then keep labels and clickable markers as live Leaflet overlays.

Use **Inkscape** for icon and symbol design. Make monochrome SVG symbols for
city, shrine, ruin, dungeon, gate, forest, swamp, mountain, cave, lava, desert,
port, and archive icons. These can become Leaflet marker icons or embedded SVG
overlays.

Use **GitHub** for versioning, and deploy the viewer as a static site. You do
not need a backend at first. The project can be a folder of HTML/CSS/JS plus
`/data/*.geojson`.

The practical stack would look like this:

```text
map-project/
  index.html
  src/
    main.js
    mapStyle.js
    popups.js
    layers.js
  data/
    regions.geojson
    towns.geojson
    landmarks.geojson
    roads.geojson
    biomes.geojson
    gates.geojson
  assets/
    icons/
      city.svg
      shrine.svg
      ruin.svg
      gate.svg
      forest.svg
      mountain.svg
    tiles/
      z0/
      z1/
      z2/
  qgis/
    shattered-realm.qgz
  exports/
    print-map.svg
    print-map.pdf
```

For now, the next real step should be: **convert the prototype into a Leaflet
`CRS.Simple` map** and split the data into separate GeoJSON files. The current
prototype I made is a useful proof of concept, but it is custom SVG. Leaflet is
the better long-term base because it already handles map navigation, layers,
markers, popups, vector features, and tile layers cleanly. ([Leaflet][2])

Use **Tiled Map Editor** only if you want this to become an actual game-level
map or tile-grid world. Tiled supports orthogonal/isometric/hex map
orientations, infinite maps, layers, object groups, and JSON export, which is
useful for a game implementation but less ideal for lore-cartography and
region-scale atlas work. ([Tiled Documentation][3])

Use **MapLibre GL JS** later only if Leaflet becomes too limited. MapLibre is
better for vector tiles, more advanced rendering, large datasets, smooth dynamic
styling, and more modern map-engine behavior. Its API includes map sources and
layers, including GeoJSON source support. ([MapLibre][4])

My recommendation: continue with **QGIS + GeoJSON + Leaflet + Inkscape**. Treat
QGIS as the editor, GeoJSON as the source of truth, Leaflet as the browser
viewer, and Inkscape as the icon/base-art tool.

[1]:
  https://docs.qgis.org/3.44/en/docs/user_manual/managing_data_source/opening_data.html
  "11.1. Opening Data — QGIS Documentation  documentation"
[2]:
  https://leafletjs.com/reference.html
  "Documentation - Leaflet - a JavaScript library for interactive maps"
[3]:
  https://doc.mapeditor.org/en/stable/reference/json-map-format/
  "JSON Map Format — Tiled 1.12.2 documentation"
[4]:
  https://maplibre.org/maplibre-gl-js/docs/API/classes/Map/
  "Map - MapLibre GL JS"

---

Recommended stack:

1. **QGIS** — Main map-editing tool. Use it to draw regions, roads, rivers,
   biomes, towns, landmarks, and gates. Primary working formats: **QGZ**,
   **GeoPackage / GPKG**, **GeoJSON**.

2. **GeoJSON** — Main data format for the map. Store polygons, lines, and points
   for regions, roads, markers, landmarks, and biome zones. Format: **`.geojson`
   / `.json`**.

3. **Leaflet** — Browser-based interactive map viewer. Use it for pan, zoom,
   clickable markers, popups, layer toggles, and labels. Formats: **HTML**,
   **CSS**, **JavaScript**, **GeoJSON**, optional **PNG/SVG tiles**.

4. **Inkscape** — Icon and visual-symbol editor. Use it to make black-and-white
   map icons, labels, decorative borders, compass roses, and export clean vector
   art. Formats: **SVG**, **PDF**, **PNG**.

5. **Tile export / tiles later** — Use when the base map becomes too detailed
   for live vectors. Export the base terrain as zoomable tiles. Formats: **PNG
   tiles**, **XYZ tile folders**, optional **MBTiles**.

6. **GitHub / static hosting** — Version and publish the map as a static site.
   Formats: **HTML/CSS/JS**, **GeoJSON**, **SVG**, **PNG**.

---

Recommended stack, with formats explained:

1. **QGIS** — The main map-building/editing tool. Use it to draw the world as
   editable layers: region shapes, town points, roads, rivers, forests,
   mountains, gates, and labels. **QGZ** is the saved QGIS project file. It
   remembers your layers, styles, labels, and layout. **GPKG / GeoPackage** is a
   single database-style map file that can store many layers together. Good for
   the master editable map. **GeoJSON** is a readable text-based map data file.
   Good for exporting parts of the map to the web viewer.

2. **GeoJSON** — The main web-map data format. It stores map objects as geometry
   plus information. **Point** means one location, like a town, shrine, gate, or
   dungeon entrance. **LineString** means a path, like a road, river, border,
   bridge, or causeway. **Polygon** means an area, like a region, biome zone,
   lake, forest, desert, or crater. File extensions: **`.geojson`** or
   **`.json`**.

3. **Leaflet** — The interactive browser map tool. Use it to make the map
   zoomable, pannable, clickable, and expandable with toggled layers. **HTML**
   is the page structure. **CSS** controls visual styling. **JavaScript**
   controls interactivity. **GeoJSON** supplies the map data. **CRS.Simple** is
   Leaflet’s mode for fictional maps, where coordinates are just map pixels/grid
   units instead of real-world latitude and longitude.

4. **Inkscape** — The vector art tool. Use it to make clean black-and-white
   symbols, decorative map elements, icons, compass roses, borders, and
   hand-drawn-looking overlays. **SVG** is editable vector art; it stays sharp
   at any zoom level. Best for icons and line art. **PNG** is a normal image
   file; useful for exported symbols, textures, or map tiles. **PDF** is useful
   for printing or sharing a fixed map page.

5. **Tiles / tile export** — Use this later when the base map becomes too
   detailed to draw live in the browser. **PNG tiles** are many small square
   images, usually 256×256 or 512×512 pixels, loaded as you zoom and pan. **XYZ
   tiles** are folders arranged by zoom level and tile position, usually like
   `/z/x/y.png`. **MBTiles** is one single file that stores many map tiles
   together, useful for packaging or offline maps.

6. **GitHub / static hosting** — Use this to save versions and publish the map
   online. The web map can be a simple static project: **HTML**, **CSS**,
   **JavaScript**, **GeoJSON**, **SVG**, and **PNG**. No backend is needed at
   first.

---
