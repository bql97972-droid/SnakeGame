# SnakeGame # OpenGL Snake Game Project

> 
> Project Introduction: A 3D Snake game implemented in C++ with OpenGL (GLFW/GLAD). This document records design considerations, pitfalls encountered, implemented solutions, and future iteration directions during development.

## I. Core Underlying Conflict: C++ OOP vs. OpenGL Paradigm

OpenGL is a procedural, data-oriented graphics API; C++ is an object-oriented language. Their underlying philosophies are inherently incompatible.

Initial approach: Forced pure object-oriented encapsulation, split into many classes: `Window`, `Shader`, `Camera`.

- Pros: Instantiate objects directly to quickly create Shader and Camera instances; simple invocation.
- Cons: GPU resources (VBO/VAO/EBO) are tightly coupled with C++ objects. Resource ownership becomes ambiguous and hard to decouple later.

> 
> Reflection: Rendering resources are not suitable for blind OOP wrapping. Rendering logic itself fits better within the main workflow.

## II. Pitfalls & Solutions

### 1. Floating-point Precision Trap

**Problem**: Floating-point numbers are binary approximations stored in memory. Two mathematically equal floats will fail direct `==` equality checks.
This caused logic errors in coordinate checks for food consumption and collision detection in the Snake game.

**Solutions**

1. Option A (adopted in this project): Use integer `int` type for map grid coordinates to avoid floating-point errors at the source.
2. Option B: Use tolerance comparison for floating-point coordinates. Instead of `==`, check whether the absolute difference between two floats is smaller than a tiny threshold.

### 2. GPU Resource Ownership and Lifecycle Management

**Problem**: Excessive object encapsulation in early code made ownership of GPU resources such as VAO/VBO unclear. `glDelete*` could not be invoked correctly to free resources, making lifecycle control difficult.

Two resource release strategies:

1. Write GPU resource cleanup code inside class destructors; resources are freed automatically when the C++ object is destroyed.
2. Implement custom manual release functions and explicitly call them at appropriate moments.

> 
> Core point: Clarify the binding relationship between CPU-side C++ objects and GPU video memory resource lifecycles.

### 3. Confusion Between Compile-time and Runtime Relative Paths

**Problem**: The two path lookup mechanisms are completely independent and easy to mix up:

1. **Compile-time (`#include` headers)**
   - Local `.h` headers in the same directory can be included directly by filename.
   - The compiler searches the current source file directory plus configured additional include directories for headers.
   - Distinguish third-party library headers (GLFW/GLAD) from your custom headers.
2. **Runtime (loading textures, PNG assets, etc.)**
   - Texture/image file loading uses the **program working directory** as the base path, NOT the source code directory.

> 
> Common pitfall: Compilation succeeds, but textures fail to load at runtime — this is almost always caused by incorrect working directory configuration.

### 4. Tight Coupling Between Render Layer and Game Logic Layer

**Problem**: After game logic updates complete, data is read and rendered within the same function. Game logic and rendering code are mixed and highly coupled.

- Drawbacks: Messy code, poor extensibility, harder resource management; ambiguous data ownership — unclear where data is created and destroyed.

> 
> Future optimization idea (not implemented in this project):
> The logic layer has zero awareness of OpenGL. **The render layer passively reads exposed data from the logic layer only**. The logic layer maintains pure game state, with one-way data reading to break tight coupling. This is data-driven rendering.

### 5. Game Frame Rate Tied to Movement Speed

**Problem**: Updating Snake movement per frame causes fluctuating speed when frame rate varies.
**Solution**: Use **deltaTime**, drive game logic by real elapsed time rather than frame count. Guarantees constant movement speed regardless of frame rate.

### 6. Circular Dependencies Between Functions / Classes

**Scenario**: Window creation via `CreateWindow` needs to register callback functions; callbacks in turn need access to the Window instance, creating mutual dependency.

**Solution**: Use `glfwSetWindowUserPointer` to attach the current `this` pointer to the GLFW window handle.
Workflow:

1. Create the window and store the class instance pointer inside the window’s user pointer field in advance.
2. Register callback functions.
3. Inside the callback, retrieve the object pointer with `glfwGetWindowUserPointer` to access class members.

Resolves circular calls that are hard to handle with forward declarations between interdependent functions or classes.

## III. Overall Project Reflection & Future Iteration Directions

1. Do not blindly wrap OpenGL rendering resources with OOP. Differentiate business objects suitable for OOP and data-oriented GPU resources.
2. Core decoupling goal: **Separate logic layer and render layer**. The logic layer maintains game data and imports no graphics APIs. The render layer reads logic-layer data unidirectionally to implement data-driven rendering.
3. Design resource lifecycles upfront before coding: define who creates, owns and destroys each resource.
4. Coordinate system: Grid-based games should prefer integer coordinates to reduce precision bugs from float equality checks.
5. Drive game logic by time; never control object movement using frame count.

## IV. Remaining Unoptimized Points (Not Refactored in This Version)

- Render layer and game logic layer remain heavily coupled. The next project will practice layered architecture to isolate logic and rendering.
- Global state and data ownership management are immature; reinforce resource lifecycle design in future projects.

## V. Project Overview

- **Project Name**: OpenGL 3D Snake Game
- **Tech Stack**: C++, OpenGL 4.6 (GLFW / GLAD / GLM), Shaders, texture mapping (stb_image)
- **Runtime Environment**: Windows + Visual Studio (x64 Debug)
- **Completion Status**: Core gameplay functional — Snake moves within a 1×1 grid map, eats food to grow, collides with map boundaries, movement controlled by fixed time step.
- **Current Code Structure**
  - `main.cpp`: Window / Camera / Shader / object assembly, main loop, snake rendering
  - `core/world`: `mywindow` (window wrapper), `Shader`, `camera`
  - `data/data`: Vertex data for cubes and floor plane
  - `renderer/object` + `bridge`: Object, VAO/VBO and texture wrappers
  - `renderer/renderer`: `draw_object`, input handling, matrix position calculation, game logic (`snake_game_logic`), food spawning

### Gameplay Parameters

| Item | Value |
| --- | --- |
| Map | 1×1 grid, range [-0.45, 0.45], step size 0.1 (10×10 grid cells) |
| Snake | Starts with 2 segments; grows after eating food |
| Food | Randomly spawned inside map, avoiding snake body |
| Movement | Fixed time step, `stepInterval = 1.0s` → 1 grid per second |
| Food consumption check | `glm::distance(head, food) < 0.001` (tolerance to avoid float error) |
| Boundary | No movement when crossing boundaries; stays in place |

## VI. Design Scheme

### 1. Current Architecture Implementation

The project has three layers but full separation is not achieved: `main` handles assembly and main loop; the `renderer` layer provides drawing, input and position matrices. Game logic currently lives in `snake_game_logic` inside `renderer.cpp` (a free function with 10 parameters, still holding references to Shader, object and GLFWwindow).

### 2. Target Data-Driven Design (Not Implemented)

- The logic layer maintains game state only, no OpenGL dependencies whatsoever.
- Render layer reads exposed data from logic layer unidirectionally — data-driven rendering.

### 3. Movement & Time-Driven Logic

- Movement direction is set by keyboard input (`direction`), polled every frame.
- Accumulate `timeSum` with `deltaTime`. Advance one step only once `timeSum` exceeds `stepInterval`, achieving fixed time step movement decoupled from frame rate.

### 4. Food Consumption & Growth

- Detect eaten food when distance between snake head and food < 0.001.
- On consumption: retain tail segment (grow snake) and respawn food. If no consumption: remove tail and shift snake forward.

### 5. Boundary Rule

If the next position crosses map boundary, the snake does not move and stays blocked.

## VII. Problems (Based on Current Code)

1. **Proliferation of global state**: `direction / snakePositions / foodPos / timeSum` are global variables; state ownership unclear.
2. **Logic layer coupled to rendering**: `snake_game_logic` resides in `renderer.cpp`. Its signature still accepts `Shader`, `object`, `GLFWwindow` and directly calls `glfwGetKey`. Logic is not isolated from rendering.
3. **God function with 10 parameters**: Long parameter list in `snake_game_logic` is a code smell, rooted in ungrouped global state.
4. **Missing game-over rules**: Wall collision only blocks movement, no game termination. No self-collision detection. `random_food_position` may enter infinite loop when map is fully filled by snake.
5. **Floating-point precision**: Tolerance check is applied (`glm::distance < 0.001`). The more fundamental fix is integer grid coordinates (see Pitfall #1).

## VIII. Future Iteration Roadmap

1. **Refactor and group state**: Wrap game state and update logic into a `SnakeGame` class. Member variables replace existing globals; methods are `handleInput` / `update` / read-only getters. Remove `Shader` / `object` / `GLFWwindow` parameters from functions.
2. **Decouple implementation**: Logic layer with zero OpenGL dependency. Render layer reads logic state unidirectionally to realize data-driven rendering.
3. **Decouple input**: Logic layer stops calling `glfwGetKey` directly; input states are fed into it externally.
4. **Complete gameplay loop**: Implement wall-death, self-collision death, handling for fully occupied map when spawning food.
5. **Integer grid coordinates**: Use integer grid indices to eliminate floating-point precision errors entirely.

## IX. Build & Operation Guide

- **Build Environment**: Windows + Visual Studio, open `SnakeGame.slnx`, compile and run x64 Debug configuration.
- **Dependencies**: GLFW, GLAD (OpenGL 4.6), GLM, stb_image (texture loading).
- **Controls**: `W / S / A / D` to set snake movement direction (press once to set direction, snake moves automatically afterwards); `ESC` closes window.
- **Critical Runtime Note**: Textures (PNG/JPG) load relative to the **program working directory**. Set working directory to project root (where `res/` resides), otherwise compilation succeeds but textures are missing at runtime.
- **After Launch**: Press one direction key to start movement. Snake advances one grid per second at fixed time step. Eating food adds one segment and regenerates food.

## X. Core Mechanism Principles (Deep Dive)

### 1. Root Cause of Floating-Point Equality Failure: Divergent Calculation Paths

Two floating-point values mathematically identical can have different mantissa bits if computed through different arithmetic paths, causing binary representations to differ at the least significant bit and `==` comparison to return false.

- Snake head coordinate: `-0.35f + 0.1f + 0.1f + 0.1f` (cumulative addition)
- Food coordinate: `-0.45f + i * 0.1f` (formula calculation)
Mathematically equal but binary representations differ (~1e-9). Therefore food consumption check must use tolerance: `glm::distance(head, food) < 0.001`. The more fundamental solution is integer grid indices to remove floating-point error sources.

### 2. Fixed Time Step Accumulator: Subtract Instead of Reset

- `timeSum += deltaTime`. Execute a game step only once `timeSum` reaches `stepInterval`.
- Subtract `stepInterval` from `timeSum` instead of resetting to zero — resetting discards leftover fractional time and causes average speed to drift slower over time. Subtraction preserves residual time and maintains strict average step interval.
- Result: Movement speed decoupled from frame rate, constant regardless of FPS fluctuation.

## XI. Key Decisions & Detours

1. **Input model for movement**: Initial design used `moveState` (hold key to move one cell) → changed to `direction` (set direction on key press, auto-advance afterward). Repeated iteration confirmed the final model: input only sets direction, logic advances on timer.
2. **Food consumption detection**: Original `newHead == foodPos` (float failure) → tried adjacent-grid jump (snake segments desynchronized) → final choice of tolerance check `glm::distance < 0.001`.
3. **Tradeoff of alternatives**: Tested direct `(int)` cast (data loss / grid misalignment), scaling coordinates ×100 (requires geometry and camera rescaling). Both rejected; tolerance check selected for minimal code changes.
4. **Boundary handling**: Wall collision implemented as stationary blocking only, without game-over logic, reserved for later iteration.

## XII. Feature Acceptance Checklist

**Implemented**

- Snake movement in 1×1 grid (WASD to set direction)
- Fixed time step movement (1 cell/second, FPS independent)
- Food consumption and growth + randomized food spawn (tolerance check, avoid snake body)
- Boundary blocking (no movement across map edges)
- Texture rendering (floor / snake / food)

**Unimplemented (Future Iteration)**

- Wall / self-collision game-over detection
- Menu / pause system
- Handling for food spawning when map is fully occupied
- True decoupling of logic and rendering (logic still lives inside `renderer.cpp`)

## XIII. Open Source

- **Dependency List**: GLFW, GLAD, GLM, stb_image.
- **Demo Screenshot**: See Chapter XVI · Runtime Preview.
- **Notice**: This markdown file records development decisions as open-source documentation.

## XIV. Code Quality Improvements

- `snakePositions.insert(begin(), ...)` is O(n). Negligible for short snakes; consider fixed-size array or deque for longer snake bodies.
- Replace `rand()` random source with `<random>` `mt19937` for more uniform distribution.
- Remove global variables and 10-parameter god function by wrapping state in a class (see VII & VIII).
- Centralize hardcoded constants (0.1 step, 0.001 tolerance, mapMin/mapMax) into constant definitions.

## XV. Learning Summary

- First complete graphics mini-game: mastered full pipeline of window, camera, shader, texture and VAO.
- Key takeaways: Never use `==` for float equality (rooted in divergent calculation paths); drive logic by time instead of frame count; separate logic and rendering layers.
- Engineering mindset: Working code ≠ maintainable code. Current engineering score 4/10, but core knowledge gained. Next goal: turn "runnable prototype" into clean architecture.

## XVI. Runtime Preview

2026/10/05
![SnakeGame runtime preview](./SnakeGame.png)

---THANK YOU . LearnOpenGL---