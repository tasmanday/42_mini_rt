# miniRT

A simple ray tracer built as part of the [42 School]([https://42.fr/en/homepage/](https://www.42adel.org.au/)) curriculum. `miniRT` renders 3D scenes using basic ray tracing techniques, handling spheres, planes, cylinders, lights, and camera perspective.

This project is written in C and uses the **minilibx** graphics library provided by 42.

---

## 🖼️ Features

- Ray-object intersection (spheres, planes, cylinders)
- Phong lighting (ambient, diffuse, specular)
- Shadows
- Basic camera and viewport system
- BMP screenshot saving
- Real-time rendering window with MiniLibX

---

## 📷 Example Output

(Add screenshots here! Drop in a rendered image or two showing off your scene)

---

## 🚀 Getting Started

### Prerequisites

- `gcc`
- `make`
- [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) (provided by 42)
- `Linux`

---

### Building

```bash
git clone https://github.com/tasmanday/minirt.git
cd minirt
make
```

### Running

```bash
./miniRT scenario_file.rt
```
There are a number od test scenarios in the eval_scenarios directory or you can make your own.

---

📄 Scene File Format

`.rt` files describe the scene to render. Here's a simple example:

```
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.6 255,255,255
sp 0,0,20 20 255,0,0
```

Identifiers
| Symbol | Meaning | Notes |
|:--------:|:--------:|:--------:|
| `A` |	Ambient light | Ratio and RGB color |
| `C` | Camera | Position, direction, FOV |
| `L` | Light | Position, brightness, RGB color |
| `sp` | Sphere | Position, diameter, RGB color |
| `pl` | Plane | Position, normal vector, RGB color |
| `cy` | Cylinder | Position, orientation, diameter, height, RGB color |

Each line starts with an identifier followed by parameters like position, color, brightness, etc.
