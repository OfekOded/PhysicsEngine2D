#include <iostream>
#include <thread> // בשביל השהייה קטנה בצפייה
#include <chrono>

#include "physics/World.h"
#include "physics/RigidBody.h"
#include "physics/shapes/CircleShape.h"

int main() {
    // 1. יצירת העולם (ללא כבידה כרגע, כדי לבדוק התנגשות נטו)
    World world(Vector2(0, 0));

    // 2. יצירת שני כדורים
    // כדור א': מיקום (0,0), רדיוס 1, מסה 1. זז ימינה.
    auto shapeA = std::make_unique<CircleShape>(1.0f);
    RigidBody* bodyA = new RigidBody(1.0f, std::move(shapeA), 0.0f, 0.0f, 1.0f);
    bodyA->setPosition(Vector2(0, 0));
    bodyA->setVelocity(Vector2(5, 0)); // טס ימינה

    // כדור ב': מיקום (10,0), רדיוס 1, מסה 1. זז שמאלה.
    auto shapeB = std::make_unique<CircleShape>(1.0f);
    RigidBody* bodyB = new RigidBody(1.0f, std::move(shapeB), 0.0f, 0.0f, 1.0f);
    bodyB->setPosition(Vector2(10, 0));
    bodyB->setVelocity(Vector2(-5, 0)); // טס שמאלה

    // הוספה לעולם
    world.addBody(bodyA);
    world.addBody(bodyB);

    // 3. לולאת הסימולציה
    float dt = 0.016f; // מדמה 60 FPS

    std::cout << "Simulation Start! Balls moving towards each other...\n";
    std::cout << "----------------------------------------------------\n";

    for (int i = 0; i < 100; ++i) {
        world.step(dt);

        // הדפסה פשוטה של המיקומים
        printf("Frame %d: BallA X=%.2f | BallB X=%.2f\n",
            i, bodyA->getPosition().x, bodyB->getPosition().x);

        // בדיקה ידנית - מתי הם אמורים להתנגש?
        // הרדיוסים הם 1 ו-1, אז ההתנגשות תקרה כשהמרחק < 2.
        // בערך בפריים 50-60 תראה שהם מחליפים כיוון.
    }

    return 0;
}