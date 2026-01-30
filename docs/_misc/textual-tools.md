
# Tooling & Info

## Info to Check

### What “front-matter” is (and why i would want it)
Front-matter is a small block of metadata at the top of a content file (usually Markdown).  
It’s typically written in **YAML** between `---` lines.

Tools like 
[Obsidian](https://obsidian.md/), 
[MkDocs](https://www.mkdocs.org/), 
[Docusaurus](https://docusaurus.io/), 
[Jekyll](), 
[Notion importers](), 
etc., 
read this block to **index, sort, filter, cross-link, and build lists**,  
while the rich, lore-y body of the page stays human-friendly.

Think of it as:
  - front-matter = database fields
  - body = prose, quotes, lists, and longform lore.

Benefits:
- Consistent **indexes** (e.g., “all High-threat desert constructs”).
- **Stable IDs** for cross-links and future automation.
- **Search facets** (by hue, region, creature type, themes).
- **Pipelines/linting** (we can validate YAML; free our writers to focus on lore).

---

## Templates & Stuff

> [!NOTE]  
> This is just to regroup things frequently used in my markdown files...

---

## Links "to" and "back to" other md files

*"Click to See More About This"*
```markdown
> [See more focused doc on current subject ►](./path-to-other-doc.md)
```

*"Click to Go Back"*
```markdown
<!-- Placed at the top -->

<div align="right">

[◄ Go back to where you came from](path-to-previous-or-main-doc.md)

</div>
```

---

## Emojis

- [emoji-cheat-sheet (for github)](https://github.com/ikatyang/emoji-cheat-sheet/blob/master/README.md)

---
