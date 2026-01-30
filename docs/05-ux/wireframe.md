
<div align="right">

[◄ Go back to ](./ui.md.md)

</div>

# ✨ Wireframe Set Ideas

## HUD (Core Gameplay Screen)

- Top-left:
  - Health / Essence Shard → a prism fragment icon with cracks that spread as health drops.
  - Small pulse glow when healing.

- Bottom-center:
  - Hue Wheel (3 Slots) → three shard icons orbiting a central prism.
    - Active hue glows faintly and pulses when casting.
    - Charge bar runs beneath (segmented, tinted with hue after cast).

- Bottom-right:
  - Quick Items / Relics → small runic circles, each tied to an item slot.

---

## Dialogue Screen
- Background: semi-transparent slab of glass, faintly refracting current hue(s).
- NPC dialogue: appears in white with a subtle colored edge tied to their faction hue.
- Player choices:
  - Neutral = gray text.
  - Hue-locked = glowing border and symbol (leaf/flame/wave/sun/spiral/root).
  - Higher affinity = animated flourish (e.g., vines curl, sparks flicker).

---

## Inventory / Menu
- Layout: center-aligned, prism shard in the background.
- Tabs: shards we rotate through (Weapons, Relics, Echoes, Lore).
- Items: shown in small circular sigils, tinted with their dominant hue.
- Selected Item Panel: fades in on the right with description + faint sound chime.

---

## Echo Puzzle Screen
- Center: three floating stone obelisks (or shard slots).
- Player input: insert hues as glowing fragments.
- Solved: ripple effect, prism re-aligns.
- Failed: UI cracks and reforms with a muted glass shatter sound.

---

<!-- 
## Misc

### Prism Ui Wireframes
```typescript
import React from "react";

export default function PrismUIWireframes() {
  return (
    <div className="w-full h-screen bg-gray-900 text-white p-6 flex flex-col gap-8">
      {/* HUD Layout */}
      <section className="relative border border-gray-700 rounded-2xl p-4 shadow-lg">
        <h2 className="text-xl font-bold mb-2">HUD (Core Gameplay)</h2>
        <div className="flex justify-between items-start">
          {/* Health / Essence */}
          <div className="w-32 h-32 border-2 border-cyan-400 rounded-full flex items-center justify-center">
            <span className="text-sm text-cyan-300">Prism Shard (HP)</span>
          </div>

          {/* Hue Wheel */}
          <div className="flex flex-col items-center gap-2">
            <div className="w-24 h-24 border-2 border-purple-400 rounded-full flex items-center justify-center">
              <span className="text-xs">Hue Core</span>
            </div>
            <div className="flex gap-2">
              <div className="w-10 h-10 border border-green-400 rounded-full"></div>
              <div className="w-10 h-10 border border-red-400 rounded-full"></div>
              <div className="w-10 h-10 border border-blue-400 rounded-full"></div>
            </div>
            <div className="w-32 h-2 bg-gray-700 rounded">
              <div className="w-2/3 h-full bg-gradient-to-r from-green-400 to-blue-400 rounded"></div>
            </div>
          </div>

          {/* Quick Items */}
          <div className="flex flex-col gap-2">
            <div className="w-12 h-12 border border-yellow-400 rounded-full"></div>
            <div className="w-12 h-12 border border-pink-400 rounded-full"></div>
            <div className="w-12 h-12 border border-brown-400 rounded-full"></div>
          </div>
        </div>
      </section>

      {/* Dialogue Screen */}
      <section className="border border-gray-700 rounded-2xl p-4 shadow-lg bg-gray-800/70">
        <h2 className="text-xl font-bold mb-2">Dialogue Screen</h2>
        <div className="p-4 border border-purple-400 rounded-lg mb-4">
          <p className="italic text-gray-200">NPC: "You do not belong, Prismwalker."</p>
        </div>

        <div className="flex flex-col gap-2">
          <button className="p-2 rounded bg-gray-700 hover:bg-gray-600">Neutral: "I seek only to pass."</button>
          <button className="p-2 rounded border border-green-400 text-green-300 hover:bg-green-900/40">
            Verdant Option: "The Grove weeps. I’ve come to listen."
          </button>
          <button className="p-2 rounded border border-blue-400 text-blue-300 hover:bg-blue-900/40">
            Cobalt Option: "Memory stirs here. Show me what was forgotten."
          </button>
          <button className="p-2 rounded border border-brown-400 text-amber-200 hover:bg-amber-900/40">
            Earthen Option: "Decay is truth. Let me touch what remains."
          </button>
        </div>
      </section>
    </div>
  );
}
```

---

-->
