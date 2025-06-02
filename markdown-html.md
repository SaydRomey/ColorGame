
# HTML Cheatsheet for GitHub README
> *See code for syntax*

## Headings
<h1>Heading 1</h1>   <!-- Largest -->
<h2>Heading 2</h2>
<h3>Heading 3</h3>
<h4>Heading 4</h4>
<h5>Heading 5</h5>
<h6>Heading 6</h6>   <!-- Smallest -->

## Paragraphs & Line Breaks
<p>This is a paragraph.</p>

<p>This is another paragraph.<br>With a line break.</p>

## Collapsible Content
<details>
  <summary>Click to expand!</summary>
  Hidden text here.
</details>

## Links `(<a>)`
<a href="https://example.com">Visit Example</a>

<a href="https://example.com" target="_blank" rel="noreferrer">Open in New Tab</a>

## Images `(<img>)`
<img src="https://via.placeholder.com/150" alt="Example Image" width="100">

### Adding Clickable Images (Icon with Link)
<a href="https://github.com">
  <img src="https://github.githubassets.com/images/modules/logos_page/GitHub-Mark.png" alt="GitHub" width="40">
</a>

## Lists

### Unordered List `(<ul>)` (Bullets)
<ul>
  <li>Item 1</li>
  <li>Item 2</li>
  <li>Item 3</li>
</ul>

### Ordered List `(<ol>)` (Numbers)
<ol>
  <li>First</li>
  <li>Second</li>
  <li>Third</li>
</ol>

### Description List `(<dl>)`
<dl>
  <dt>Coffee</dt>
  <dd>- black hot drink</dd>
  <dt>Milk</dt>
  <dd>- white cold drink</dd>
</dl>

## Tables `(<table>)`
<table>
  <tr>
    <th>Column 1</th>
    <th>Column 2</th>
  </tr>
  <tr>
    <td>Data 1</td>
    <td>Data 2</td>
  </tr>
</table>

## Centering Content

### Center a heading:
<h3 align="center">Centered Title</h3>

### Center a paragraph:
<p align="center">This text is centered.</p>

### Center images or icons:
<p align="center">
  <img src="https://via.placeholder.com/100" width="50">
</p>

## Horizontal Line `(<hr>)`
<hr>

## Commenting Code `(<!-- -->)`
<!-- This is a comment. It won't be displayed. -->

---

## ASCII Art Centering

### `<pre>`

Why Use `<pre>`?
  - Maintains exact formatting (spaces, new lines, indentation).
  - Keeps ASCII art properly aligned inside a `<div>`.
  - Ensures GitHub README renders ASCII art exactly as written.

### Example Without `<pre>` (Incorrect Formatting)
<div align="center">
██╗███╗   ██╗████████╗ █████╗  ██████╗████████╗
██║████╗  ██║╚══██╔══╝██╔══██╗██╔════╝╚══██╔══╝
██║██╔██╗ ██║   ██║   ███████║██║        ██║   
██║██║╚██╗██║   ██║   ██╔══██║██║        ██║   
██║██║ ╚████║   ██║   ██║  ██║╚██████╗   ██║   
╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝   ╚═╝   
</div>

### Correct Example With `<pre>` (Recommended)
<div align="center">
<pre>
██╗███╗   ██╗████████╗ █████╗  ██████╗████████╗
██║████╗  ██║╚══██╔══╝██╔══██╗██╔════╝╚══██╔══╝
██║██╔██╗ ██║   ██║   ███████║██║        ██║   
██║██║╚██╗██║   ██║   ██╔══██║██║        ██║   
██║██║ ╚████║   ██║   ██║  ██║╚██████╗   ██║   
╚═╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝   ╚═╝   
</pre>
</div>

---

## Basic Formatting Tags
| Tag          | Description                              | Example Usage |
|-------------|----------------------------------|--------------|
| `<div>`     | Defines a block container (**useful for alignment**) | `<div align="center">...</div>` |
| `<p>`       | Creates a paragraph              | `<p>This is a paragraph.</p>` |
| `<br>`      | Adds a line break (new line)     | `Line 1 <br> Line 2` |
| `<b>`       | **Bold text**                     | `<b>Bold Text</b>` |
| `<i>`       | *Italic text*                     | `<i>Italic Text</i>` |
| `<u>`       | _Underlined text_                 | `<u>Underlined</u>` |
| `<s>`       | ~~Strikthrough text~~              | `<s>No longer relevant</s>` |
| `<hr>`      | Creates a horizontal divider     | `<hr>` |

---

## Text Alignment & Structure
| Tag          | Description                              | Example Usage |
|-------------|----------------------------------|--------------|
| `<h1>` - `<h6>` | Headings (h1 = biggest, h6 = smallest) | `<h1>Title</h1>` |
| `<div align="center">` | Centers content inside | `<div align="center"><h1>Title</h1></div>` |
| `<div align="right">` | Aligns content to the right | `<div align="right"><p>Right-aligned</p></div>` |
| `<blockquote>` | Indents a quote block | `<blockquote>Quoted Text</blockquote>` |

---

## Links & Images
| Tag          | Description                              | Example Usage |
|-------------|----------------------------------|--------------|
| `<a href="">` | Creates a clickable link      | `<a href="https://github.com">GitHub</a>` |
| `<img>`      | Displays an image              | `<img src="logo.png" width="100">` |
| `<a>` + `<img>` | Clickable image link | `<a href="https://github.com"><img src="logo.png" width="40"></a>` |

---

> [!NOTE]
> Useful information that users should know, even when skimming content.

> [!TIP]
> Helpful advice for doing things better or more easily.

> [!IMPORTANT]
> Key information users need to know to achieve their goal.

> [!WARNING]
> Urgent info that needs immediate user attention to avoid problems.

> [!CAUTION]
> Advises about risks or negative outcomes of certain actions.

---
