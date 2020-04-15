using System.Collections;
using UnityEngine;

public class EnemyController : MonoBehaviour
{
    public int hitDamage = 1;
    public int cityDamage = 1000;

    public bool canShoot = true;
    public bool explodes = false;

    public float velx = -50.0f;
    public float fireRate = 1.0f;

    public GameObject bullet;
    public Vector3 bulletOffset;

    public int maxHealth = 1;
    private int curHealth;

    private Rigidbody2D rb;

    void Start()
    {
        curHealth = maxHealth;

        rb = GetComponent<Rigidbody2D>();

        if (canShoot)
            StartCoroutine(Shoot());
    }

    void Update()
    {
        Move();
    }

    private IEnumerator Shoot()
    {
        Instantiate(bullet, transform.position + bulletOffset, transform.rotation);

        AudioManager.instance.Play("Enemy_Shoot", Random.Range(.25f, .35f), 0.8f);

        yield return new WaitForSeconds(fireRate);

        StartCoroutine(Shoot());
    }

    private void Move()
    {
        rb.velocity = new Vector2(velx * Time.deltaTime, 0.0f);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (!GameManager.instance.GameOver())
        {

            if (collision.gameObject.name == "Player")
            {
                collision.gameObject.GetComponent<PlayerController>().DamagePlayer(hitDamage);

                if (explodes)
                {
                    velx = 0.0f;
                    StartCoroutine(Die());
                }
            }

            if (collision.gameObject.name == "Player_Bullet")
            {
                curHealth -= collision.gameObject.GetComponent<BulletController>().damage;
            }
        }

        if (collision.gameObject.name == "Left_Boundary")
        {
            ScoreManager.instance.Deduct(cityDamage);
            Destroy(gameObject);
        }
    }

    public void DamageEnemy(int damage)
    {
        curHealth -= damage;

        if (curHealth <= 0)
            StartCoroutine(Die());
    }
    public IEnumerator Die()
    {
        AudioManager.instance.Play("Explosion", 1f, 1f);  
        GetComponent<Animator>().Play("Explosion");

        GetComponent<BoxCollider2D>().enabled = false;

        ScoreManager.instance.Add(cityDamage);

        yield return new WaitForSeconds(0.8f);

        Destroy(gameObject);
    }
}
