using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ballMovement : MonoBehaviour
{
    //starting variables 
    Rigidbody2D rigidbody2D;
    Vector2 ballVelocity;
    float accelerationX = 1;
    int accelerationY = 0;

    // Start is called before the first frame update
    void Start()
    {
        rigidbody2D = this.gameObject.GetComponent<Rigidbody2D>();
        ballVelocity = rigidbody2D.velocity;
        //this.gameObject.GetComponent<Rigidbody2D>().velocity = new Vector2(1, 1);
        ballVelocity = new Vector2(2, 0);
    }

    // Update is called once per frame
    void Update()
    {
        ballVelocity = new Vector2(ballVelocity.x * accelerationX, ballVelocity.y * accelerationY);
        this.gameObject.GetComponent<Rigidbody2D>().velocity = ballVelocity;
    }
}

