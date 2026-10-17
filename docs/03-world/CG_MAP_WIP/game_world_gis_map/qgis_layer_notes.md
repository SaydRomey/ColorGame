# QGIS Layer Notes

Open QGIS and add these vector layers in order:

1. `regions.geojson`
2. `links.geojson`
3. `landmarks.geojson`
4. `entities.geojson`

Use categorized styling:

- Regions by `name` or `hue`.
- Entities by `feature_type` (`NPC`, `Enemy`, `Boss`, `Faction`).
- Links by `feature_type` (`contains`, `hosts_npc`, `hosts_enemy`, `counter`, `variant`, `intrusion`, `prism_gate_route`, `history`, `conceptual`).

Useful filters:

```qgis
"region" = 'Huevale'
```

```qgis
"feature_type" IN ('Enemy', 'Boss')
```

```qgis
"canonical_status" IN ('strong_fit', 'candidate', 'candidate_or_secondary')
```
