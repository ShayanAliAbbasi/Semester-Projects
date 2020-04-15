using UnityEngine;

public class Boundary : MonoBehaviour
{
    private Transform playerTrans;
    private float offset;

    virtual protected void Start()
    {
        playerTrans = GameObject.Find("Player").transform;

        offset = transform.position.x - playerTrans.position.x;
    }

    virtual protected void Update()
    {
        transform.position = new Vector3(playerTrans.position.x + offset, transform.position.y, transform.position.z);
    }
}
