# Game World GIS Map Package

This package contains a fictional GIS-style map for the game world.

## Files

- `regions.geojson` — region polygons.
- `landmarks.geojson` — hub, landmark, gate, and sublocation points.
- `entities.geojson` — NPC, enemy, boss, and faction points.
- `links.geojson` — relationship/counter/variant/intrusion lines.
- `game_world_combined.geojson` — all features in one file.
- `leaflet_game_world_map.html` — standalone Leaflet viewer with inline data.
- `qgis_layer_notes.md` — QGIS import and styling notes.

## Coordinate system

This is a fictional local coordinate system, not Earth geography. In Leaflet it uses `L.CRS.Simple`. In QGIS, load it as local/no-CRS concept-map data.
