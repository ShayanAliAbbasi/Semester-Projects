using UnityEngine;

public class BulletController : MonoBehaviour
{
    public int damage = 1;
    public float velx = 50.0f;

    private Rigidbody2D rb;

    void Start()
    {
        rb = gameObject.AddComponent<Rigidbody2D>();
        rb.gravityScale = 0.0f;
    }

    void FixedUpdate()
    {
        rb.velocity = new Vector2(velx * Time.deltaTime, 0.0f);
    }

    private void OnTriggerEnter2D(Collider2D collision)
     {
        if (transform.tag == "Player_Bullet" && collision.transform.tag == "Enemy")
        {
            collision.gameObject.GetComponent<EnemyController>().DamageEnemy(damage);
            Destroy(gameObject);
        }
        else if (transform.tag == "Enemy_Bullet" && collision.transform.tag == "Player")
        { 
            collision.gameObject.GetComponent<PlayerController>().DamagePlayer(damage);
            Destroy(gameObject);
        }

        if (collision.tag == "Boundary")
            Destroy(gameObject);
    }
}
