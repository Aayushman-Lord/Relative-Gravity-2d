# 🌌 Relativistic Gravity Simulator (2D)

> Real-time 2D N-Body Gravity Simulator with Relativistic Physics built using **C++** and **Raylib**

---

## 📖 Overview

This project is a **real-time physics simulator** that models gravitational interaction between multiple bodies in a 2D universe.

It includes:

* Newtonian gravity
* Relativistic corrections
* Orbital mechanics
* Collision and merging
* Gravity field visualization

You can simulate:

* Solar systems
* Binary stars
* Black hole systems
* Custom universes

All in real time.

---

## ✨ Features

### Physics Engine

* Real-time N-Body gravity
* Stable orbit simulation
* Momentum conservation
* Density-based merging
* Semi-implicit integration (high stability)

### Relativistic Effects

* Lorentz factor (γ)
* Proper time tracking
* Speed limited to speed of light
* Relativistic inertia correction

### Visualization

* Gravity heatmap field
* Object motion trails
* Smooth rendering
* Interactive camera

### Engine Features

* Fully custom physics engine
* No external physics engines used
* Built completely from scratch

---

## 🧠 Physics Implemented

### Newtonian Gravity

```
F = G m₁ m₂ / r²
```

### Lorentz Factor

```
γ = 1 / √(1 − v² / C²)
```

Used for:

* Time dilation
* Relativistic inertia correction

### Orbital Velocity

```
v = √(GM / r)
```

Ensures stable orbit.

### Density-based Radius

```
r = √(m / (πρ))
```

Used during merging.

---

## 🎮 Controls

| Key | Action            |
| --- | ----------------- |
| W   | Move camera up    |
| S   | Move camera down  |
| A   | Move camera left  |
| D   | Move camera right |

---

## 🛠 Built With

* C++
* Raylib
* Custom physics engine


---

## ✅Compile
Requirements:

- VSCode
- C/C++ Extension (Microsoft)
- Raylib installed

Note:
This project includes a preconfigured .vscode folder.
No manual setup is required.

Steps:

1. Open the project folder in VSCode
2. Press F5
3. The simulator will compile and run automatically


## 🌠 Included Simulation

Includes full solar system:

* Sun
* Mercury
* Venus
* Earth
* Mars
* Jupiter
* Saturn
* Uranus
* Neptune

With stable relativistic orbits.

---

## 🔬 Future Improvements

* Black hole physics
* Schwarzschild radius
* Spacetime curvature grid
* Frame dragging
* GPU acceleration
* 3D version

---

## 🎯 Purpose

Built to explore:

* Gravity simulation
* Special relativity
* Physics engine development
* Orbital mechanics
* Real-time rendering

---

## 📜 License

MIT License

Free to use, modify, and distribute.

---

## ⭐ Support

If you like this project, consider starring the repo!
