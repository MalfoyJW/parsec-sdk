using ParsecUnity;
using UnityEngine;

class PlayerMovement : MonoBehaviour
{
    private bool automatic = false;
    public float speed = 5.0f;
    public int player = 1;

    private void Start()
    {
    }

    private void Update()
    {
        if (ParsecInput.GetKey(player, KeyCode.LeftArrow))
        {
            transform.Translate(new Vector3(-speed * Time.deltaTime, 0, 0));
        }
        if (ParsecInput.GetKey(player, KeyCode.RightArrow))
        {
            transform.Translate(new Vector3(speed * Time.deltaTime, 0, 0));
        }
        if (ParsecInput.GetKey(player, KeyCode.UpArrow))
        {
            transform.Translate(new Vector3(0, speed * Time.deltaTime, 0));
        }
        if (ParsecInput.GetKey(player, KeyCode.DownArrow))
        {
            transform.Translate(new Vector3(0, -speed * Time.deltaTime, 0));
        }
        if (ParsecInput.GetKey(player, KeyCode.Space))
        {
            automatic = !automatic;
        }
        if (automatic)
        {
            Vector3 position = this.transform.position;
            position.x -= 0.5f;
            if (position.x <= -13.5)
            {
                position.x = 13.5f;
            }
            this.transform.position = position;
        }
    }
}