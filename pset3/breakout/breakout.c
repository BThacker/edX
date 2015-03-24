//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// height and width of paddle in pixels
#define PADHEIGHT 15
#define PADWIDTH 80

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // velocity of ball
    double xvelocity = 2.0;
    double yvelocity = 2.0;
    
    waitForClick();
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        
        updateScoreboard(window, label, points);
        move(ball, xvelocity, yvelocity);
        // boucne ball off window bounds checking for edges
        if (getX(ball) + getWidth(ball) >= getWidth(window))
            xvelocity = -xvelocity;
        else if (getX(ball) <= 0)
            xvelocity = -xvelocity;
        else if (getY(ball) + getWidth(ball) >= getHeight(window))
        {
            lives--;
            setLocation(ball, 180, 290);
            setLocation(paddle, 160, 500);
            waitForClick();
        }
        else if (getY(ball) <= 0)
            yvelocity = -yvelocity;
        
        // handle collisions
        GObject detect = detectCollision(window, ball);
        
        if (detect != NULL && (strcmp(getType(detect), "GRect") == 0))
        {
            xvelocity = -xvelocity;
            yvelocity = -yvelocity;
            if (detect != paddle)
            {
                points++;
                removeGWindow(window, detect);
            }
         
        }
        
        GEvent mousemove = getNextEvent(MOUSE_EVENT);
        if (mousemove != NULL)
        {
            if (getEventType(mousemove) == MOUSE_MOVED)
            {
                double x = getX(mousemove) - getWidth(paddle) / 2;
                setLocation(paddle, x, 500);
            }
        }
        pause(10);
        
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // Set grid of bricks
    int ybrick = 50;
    int spacing = 20;
    
    for (int i = 0; i < ROWS; i++)
    {
        int xbrick = 2;
        for (int k = 0; k < COLS; k++)
        {
            GRect bric = newGRect(xbrick, ybrick, 30, 10);
            // here we change the colors based on the row involved via switch on i
            switch(i)
            {
                case 0:
                    setColor(bric, "YELLOW");
                    break;
                case 1:
                    setColor(bric, "RED");
                    break;
                case 2:
                    setColor(bric, "BLUE");
                    break;
                case 3:
                    setColor(bric, "GREEN");
                    break;
                case 4:
                    setColor(bric, "ORANGE");
                    break;
            }
            setFilled(bric, true);
            add(window,bric);
            xbrick += 40;
        }
        ybrick += 20;
    }
    
}
/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(200-20, 290, 20, 20);
    setColor(ball, "GREEN");
    setFilled(ball,true);
    add(window,ball);
    return ball;
}
/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(200 - 40, 500, PADWIDTH,PADHEIGHT);
    setColor(paddle, "000000"); // This sets it to color black 
    setFilled(paddle, true);
    add(window,paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel(" ");
    setFont(label, "SanSerif-50");
    setColor(label, "RED");
    add(window,label);
    setLocation(label, 185, 300);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
