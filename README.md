Cinder-SimpleBox2D
==================

A wrapper to make using Box2D effortless


Effortless setup
======

```C++
// Create a physics world with Earth's gravity
mPhysicsWorld = new World( Vec2f(0, 9.8f) );
// Add a solid ground at the bottom of the window
mPhysicsWorld->addSolidGround(this);
```

Creating dynamic shapes is a snoozefest!
======

```C++
// Add a box at (100,200) position that is 10x20
Box *box = new Box(Vec2f(100, 200), 10, 20);
mPhysicsWorld->addBody(box);
```
