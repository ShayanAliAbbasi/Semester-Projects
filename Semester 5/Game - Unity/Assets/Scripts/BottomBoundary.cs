using UnityEngine;

public class BottomBoundary : Boundary
{
    public int fallDamage = 1;

    protected override void Start()
    {
        base.Start();
    }

    protected override void Update()
    {
        base.Update();
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.name == "Player")
        {
            PlayerController pc = collision.gameObject.GetComponent<PlayerController>();
            
            pc.DamagePlayer(fallDamage);
            pc.ResetPosition();
        }
        
    }
}
