using UnityEngine;

public class Parallex : MonoBehaviour
{
    private Transform cameraPos;

    private float spriteWidth;
    private float startPosX;

    public float parallexCoef = 0.0f;

    void Start()
    {
        cameraPos = Camera.main.transform;
        
        startPosX = transform.position.x;
        spriteWidth = GetComponent<SpriteRenderer>().bounds.size.x;
    }

    void Update()
    {
        float distToMoveInX = cameraPos.position.x * parallexCoef;
        float cameraRelativePos = cameraPos.position.x * (1.0f - parallexCoef);

        Vector3 dest = new Vector3(startPosX + distToMoveInX, transform.position.y, transform.position.z);

        transform.position = dest;

        if (cameraRelativePos > startPosX + spriteWidth)
            startPosX += spriteWidth;
    }
}
