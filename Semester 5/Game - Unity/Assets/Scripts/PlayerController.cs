using UnityEngine;
using UnityEngine.UI;

public class PlayerController : MonoBehaviour
{
    public float velx = 1.0f;
    public float thursty = 1.0f;
    public float defGravScale;
    public float shootGravScale;

    public int maxHealth = 10;
    public float fireRate = 0.1f;

    public GameObject PlayerBullet;

    private int curHealth;
    private float timeSinceLastFire = 0.0f;

    private Rigidbody2D rb;
    private SpriteRenderer sr;
    private BoxCollider2D bc2D;

    private Camera cam;

    bool thrust = false;
    bool shoot = false;
    bool dead = false;
    bool canShoot = false;
    bool show = true; 

    public Animator playerAnim;
    public Animator engineAnim;

    public Text healthText;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        sr = GetComponent<SpriteRenderer>();
        bc2D = GetComponent<BoxCollider2D>();

        cam = Camera.main;

        curHealth = maxHealth;
        rb.gravityScale = defGravScale;
    }

    void Update()
    {
        if (!dead && !GameManager.instance.GameOver() && GameManager.instance.GameStarted())
        {
            CalculateFireRate();

            ManageInput();
            Shoot();
        }

        if (!dead && GameManager.instance.RestartCityFell())
        {
            Death();
        }

        DisplayHealth();

        if (!GameManager.instance.GameStarted() && show)
        {
            rb.gravityScale = 0.0f;

            if (sr.enabled)
                sr.enabled = false;
            
            if (bc2D.enabled)
                bc2D.enabled = false;

            show = false;
        }
        
        else if (GameManager.instance.GameStarted() && !show)
        {
            rb.gravityScale = defGravScale;

            if (!sr.enabled)
                sr.enabled = true;
            if (!bc2D.enabled)
                bc2D.enabled = true;

            show = true;
        }
    }

    private void FixedUpdate()
    {
        Move();

        if (!dead && !GameManager.instance.GameOver() && GameManager.instance.GameStarted())
            EngineThrust();
    }

    private void LateUpdate()
    {
        ConstrainCameraY();
    }

    private void Move()
    {
        rb.velocity = new Vector2(velx * Time.deltaTime, 0.0f);
    }

    private void EngineThrust()
    {
        if (thrust)
        {
            rb.AddForce(new Vector2(0.0f, thursty * Time.deltaTime));
            engineAnim.Play("Player_Engine_Thrust");
        }
        else
        {
            engineAnim.Play("Player_Engine_Idle");
        }
    }

    private void Shoot()
    {
        if (shoot && canShoot)
        {
            playerAnim.Play("Player_Shoot");
            rb.gravityScale = shootGravScale;

            Vector3 bulletOffset = new Vector3(1.0f, 0.008f, 0.0f);
            
            Instantiate(PlayerBullet, transform.position + bulletOffset, transform.rotation);

            timeSinceLastFire = 0.0f;

            AudioManager.instance.Play("Player_Shoot", 0.3f, 1.5f);
        }

        else if (!shoot)
        {
            rb.gravityScale = defGravScale;
        }
    }

    private void Death()
    {
        Reset();

        dead = true;

        rb.gravityScale = 0.0f;

        playerAnim.Play("Explosion");
        AudioManager.instance.Play("Explosion", 1f, 1f);

        engineAnim.gameObject.GetComponent<SpriteRenderer>().enabled = false;

        GetComponent<BoxCollider2D>().enabled = false;


        GameManager.instance.SetGameOver(true);
        
        if (!GameManager.instance.RestartCityFell())
            GameManager.instance.SetRestartDeath(true);
        
        GameManager.instance.SetSaveScore(true);
        GameManager.instance.SetSaveWave(true);
    }

    private void ManageInput()
    {
        if (Application.platform == RuntimePlatform.Android)
        {
            bool shotFired = false;

            for (int i = 0; i < Input.touchCount; i++)
            {
                if (Input.GetTouch(i).position.x < Screen.width / 2)
                {
                    shoot = true;
                    shotFired = true;
                    break;
                }
            }

            if (!shotFired)
                shoot = false;  
        }

        else if (Input.GetKey(KeyCode.Space)) // For Windows 
        {
            shoot = true;
        }
        else
        {
            shoot = false;
        }
        
        if (Application.platform == RuntimePlatform.Android)
        {
            bool thrustApplied = false;

            for (int i = 0; i < Input.touchCount; i++)
            {
                if (Input.GetTouch(i).position.x > Screen.width / 2)
                {
                    thrust = true;
                    thrustApplied = true;
                    break;
                }
            }

            if (!thrustApplied)
                thrust = false;
        }
        else if (Input.GetKey(KeyCode.UpArrow)) // For Windows 
        {
            thrust = true;
        }
        else
        {
            thrust = false;
        }
    }

    private void ConstrainCameraY()
    {
        cam.transform.position = new Vector3(cam.transform.position.x, 0.0f, cam.transform.position.z);
    }

    public void ResetPosition()
    {
        transform.position = new Vector3(transform.position.x, 0.0f, 0.0f);
    }

    public void DamagePlayer(int damage)
    {
        curHealth -= damage;

        if (curHealth <= 0)
        {
            curHealth = 0;

            Death();
        }
    }

    private void CalculateFireRate()
    {
        timeSinceLastFire += Time.deltaTime;

        if (timeSinceLastFire >= fireRate)
            canShoot = true;
        else
            canShoot = false;
    }

    private void DisplayHealth()
    {
        healthText.text = "";

        for (int i = 0; i < curHealth; i++)
        {
            healthText.text += "– ";
        }
        
        healthText.text += "<color=red>";
        for (int i = curHealth; i < maxHealth; i++)
        {
            healthText.text += "X ";
        }
        healthText.text += "</color>";
    }

    private void Reset()
    {
        thrust = false;
        shoot = false;
        canShoot = false;
    }
}
