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
#define RADIUS 15

// lives
#define LIVES 3

// Paddle dimensions
#define pWIDTH 100
#define pHEIGHT 20

//brick's coordinates
#define XBRICK 2
#define YBRICK 50

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

    double velocity = drand48();
    double velocityY = 2;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // follow mouse forever
        while (true)
        {
            // check for mouse event
            GEvent cursor = getNextEvent(MOUSE_EVENT);
            
            // if cursor on screen
            if (cursor != NULL)
            {
                // if the cursor was moved
                if (getEventType(cursor) == MOUSE_MOVED)
                {
                    // enure paddle is centered with cursor
                    double x = getX(cursor) - getWidth(paddle) / 2;
                    double y = 550;
                    setLocation(paddle, x, y);
                }
            }
             
             // move ball (up and down and at angles)
        move(ball, velocity, velocityY);
 
        // bounce off right edge of window
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            velocity = -velocity;
        }
 
        // bounce off top edge of window
        else if (getY(ball) <= 0)
        {
            velocityY = -velocityY;
        }
 
        // bounce off left edge of window
        else if (getX(ball) <= 0)
        {
            velocity = -velocity;
        }
 
        // if ball hits bottom of window - lose life, re-position, keep track of lives 
        else if (getY(ball) + getHeight(ball) >= getHeight(window))
        {   
            lives = lives - 1;
            waitForClick();
            setLocation(ball, 190, 290);
            setLocation(paddle,150, 500);
        } 
 
        // ball to bounce off paddle
        GObject object = detectCollision (window, ball);
 
        if (object == paddle)
        {
            velocityY = -velocityY;
        }
 
        // if ball hits brick, brick disappears, scoreboard updated
        if (object != NULL)
        {
            // if object (brick) hit (not the paddle or scoreboard)
            if (strcmp(getType(object), "GRect") == 0 && object != paddle && object != label)
            {
                removeGWindow(window, object);
                velocityY = -velocityY;
                points = points + 1;
                updateScoreboard (window, label, points);
            }
        }
        
        // linger before moving again
        pause(10); 
        }
       
        // initial velocity
        double velocity = 2.0;
    
        // bounce forever
        while (true)
        {
            // move circle along x-axis
            move(ball, velocity, 0);
    
            // bounce off right edge of window
            if (getX(ball) + getWidth(ball) >= getWidth(window))
            {
                velocity = -velocity;
            }

            // bounce off left edge of window
            else if (getX(ball) <= 0)
            {
                velocity = -velocity;
            }

            // linger before moving again
            pause(10);
        }
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
   // TODO
    
    int i;
    int j;
    int y;
    
    int x = -38;
 
    // 10 Columns
    for (i = 0; i < COLS; i++)
    { 
        // ROW * COL represent grid dimensions, create bricks (iterate) over columns
        x+=40;
        y = 40;
        GRect brick = newGRect(x, y, 36, 10);
        add (window, brick);
 
        // set color for initial row of 10 Columns
        setColor(brick, "RED");
        setFilled(brick, true);
 
        // create a row of bricks under each col in row (5 rows)   
        for (j = 0; j < ROWS - 1; j++)
        {
            y+=12;
            GRect brick = newGRect(x, y, 36, 10);
            add (window, brick);
 
            // change colors for each row
            if (j == 0)
            {
                setColor(brick, "ORANGE");
                setFilled(brick, true);
            }
 
            if (j == 1)
            {
                setColor(brick, "YELLOW");
                setFilled(brick, true);
            }
 
            if (j == 2)
            {
                setColor(brick, "GREEN");
                setFilled(brick, true);
            }
 
            if (j == 3)
            {
                setColor(brick, "CYAN");
                setFilled(brick, true);
            } 
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    
    GOval ball = newGOval (190, 290, 20, 20);
 
    add(window, ball);
 
    setColor(ball, "BLACK");
    setFilled(ball, true);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // TODO
    // instantiate paddle, centered bottom middle
    GRect paddle = newGRect (150, 550, pWIDTH, pHEIGHT);
 
    // add paddle to window
    add(window, paddle);
 
    // colored and filled
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    // instantiate scoreboard, value is a number (a char*)
    GLabel label = newGLabel (" ");
 
    // add scoreboard to window
    add (window, label);
 
    // location of scoreboard
    setLocation(label, 100, 100);
 
    // font/size of scoreboard
    setFont(label, "Arial-20");
 
    return label;
    
    //return NULL;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // refresh label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // Place label at the center of the window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/*
 * Detects whether ball has collided with some object in window
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // check for collisions
    GObject object;

    // check for ball collision top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for ball collision top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for ball collision bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for ball collision bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
